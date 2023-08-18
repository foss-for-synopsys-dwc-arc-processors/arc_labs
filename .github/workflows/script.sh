#!/bin/sh -eux

readonly _DIR="$(readlink -e $(dirname $(readlink -e $0)))"

die() {
    echo " *** ERROR: " $*
    exit 1
}

prepare_env() {
    out_dir="${_DIR}/out"
    logs_dir="${_DIR}/logs"
    test_log="$logs_dir/test.log"

    mkdir -p $logs_dir $out_dir
    : >$test_log

    TOOLCHAIN_CACHE_FOLDER=".cache/toolchain"

    [ "${TRAVIS}" == "true" || "${GITHUB_ACTIONS}" == "true" ] && {
        if [ "${TOOLCHAIN}" == "gnu" ] ; then
            python scripts/.ci/toolchain.py -v $TOOLCHAIN_VER -c $TOOLCHAIN_CACHE_FOLDER  || die
            if [ -d $TOOLCHAIN_CACHE_FOLDER ] ; then
                if [ -d $TOOLCHAIN_CACHE_FOLDER/$TOOLCHAIN_VER ] ; then
                    ARC_DEV_TOOL_ROOT="${TOOLCHAIN_CACHE_FOLDER}/${TOOLCHAIN_VER}"
                fi
            fi
        else
            die "Toolchain ${TOOLCHAIN} not supported in travis ci"
        fi
    }

    if [ -d $ARC_DEV_TOOL_ROOT ] ; then
        REAL_ARC_DEV_ROOT=$(readlink -f ${ARC_DEV_TOOL_ROOT})
		export ARC_GNU_ROOT=${REAL_ARC_DEV_ROOT}
		export PATH=${REAL_ARC_DEV_ROOT}/bin:${PATH}
        arc-elf32-gcc -v || die "ARC GNU toolchain is not installed correctly"
    else
        die "The toolchain path ${ARC_DEV_TOOL_ROOT} does not exist "
    fi
    git checkout -- . || die

    echo "Using ${TOOLCHAIN}-${TOOLCHAIN_VER}" || die
    . apply_embARC_patch.sh
}

run_test() {
    local target_flags=""
    if [[ ${BD_VER:-} ]]; then
        target_flags="$target_flags --platform-version $BD_VER"
    fi
    export PYTHONUNBUFFERED=1
    {
        hostname
        python ./scripts/test.py --platform $BOARD --testcase-root arc_labs/labs --toolchain $TOOLCHAIN $target_flags --build-only --report-dir $logs_dir -v -v || true
    } 2>&1 | tee -a $test_log
}

parse_logs() {
    # get rid of MAC \r and change it to UNIX \n
    sed -i 's/\r/\n/g' $test_log

    METRICS=$(cat $test_log | grep "test configurations passed" | sed -n 's/^.* \([0-9]\+\) of.*, \([0-9]\+\).*failed, \([0-9]\+\).*in \([0-9]\+\).*$/\1 \2 \3 \4/p')
    if ! ([ ${#METRICS[@]} -eq 4 ] && [ ${METRICS[1]} == "0" ]); then
        exit 1
    fi 
}

main() {
    mkdir embarc_osp/arc_labs
    cp -r labs embarc_osp/arc_labs
    pushd embarc_osp
    prepare_env
    run_test
    # parse_logs
    popd
}

main