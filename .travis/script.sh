#!/bin/sh

die() {
    echo " *** ERROR: " $*
    exit 1
}

#set -x

[ "$TRAVIS_OS_NAME" != "linux" ] || {
    git checkout -- . || die
    cd .travis || die

    if [ "$TOOLCHAIN" == "sphinx" ] ; then
        bash deploy_doc.sh || die
    fi

}
