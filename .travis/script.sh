#!/bin/sh

die() {
    echo " *** ERROR: " $*
    exit 1
}

set -x

[ $TRAVIS_OS_NAME != linux ] || {
    bash -c "$STATUS" pending "Local $NAME is in progress" || die
    git checkout -- . || die
    cd .travis || die

    if [ $TOOLCHAIN == sphinx ] ; then
        bash deploy_doc.sh || die
    fi

}
