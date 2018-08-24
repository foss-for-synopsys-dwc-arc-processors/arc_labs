#!/bin/sh

die() {
    echo " *** ERROR: " $*
    exit 1
}

#set -x


[ "$TRAVIS_OS_NAME" != "linux" ] || {
    if [ "$STATUS" != "" ] && [ "$NAME" != "" ] ; then
        bash -c "$STATUS" pending "Local $NAME testing is in progress" || \
        die "Not able to post status to github, did you set EMBARC_BOT variable in travis ci setting page"
    fi
    sudo apt-get update || die
    #sudo apt-get install lib32z1 || die
    #sudo apt-get install dos2unix || die
    #sudo apt-get install doxygen || die

    if [ "$TRAVIS_PULL_REQUEST" == "false" ] && [ "$TRAVIS_BRANCH" == "master" ] ; then
        # only install texlive on non pull request master branch
        sudo apt-get install texlive-full || die
    fi
    pip install --upgrade pip || die
    pip install git+https://github.com/sphinx-doc/sphinx || die
    pip install breathe || die
    pip install recommonmark || die
    pip install sphinx_rtd_theme || die
}
