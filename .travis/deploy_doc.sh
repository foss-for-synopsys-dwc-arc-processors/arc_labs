#!/bin/sh

REPO_NAME=${REPO_NAME:="github.com/foss-for-synopsys-dwc-arc-processors/arc_labs.git"}
REPO_LINK="https://""${GH_TOKEN}""@""${REPO_NAME}"

die()
{
    echo " *** ERROR: " $*
    exit 1
}

set -x

# Make documentation
echo 'Generating documentation ...'
# cd ../doc/documents/example || die
# ln -s ../../../example example || die
# Generate xml by doxygen
# cd ../..
cd ../doc
# mkdir -p build/doxygen/xml || die
# make doxygen &> build_doxygen.log || die
# Generate by sphinx
make html &> build_html.log || die "build doc failed"

echo 'Push generated documentation to gh-pages branch...'

# Only commit changes when it is not a pull request
# tar doc
tar czf doc.tar.gz build || die "Failed to archieve document into tar"

git fetch origin || die
git branch -a || die
mkdir gh-pages || die
cd gh-pages || die
git init . || die
git remote add origin ${REPO_LINK} || die
git fetch origin -t || die
git checkout -b gh-pages origin/gh-pages || die
if [ ! -e doc ] ; then
    mkdir doc
fi
cd doc || die
rm -rf build
cp ../../doc.tar.gz . || die
tar xzf doc.tar.gz || die
rm -rf doc.tar.gz || die

git add --all || die
# git commit -s -a -m "Update gh-pages branch, Travis build: $TRAVIS_BUILD_NUMBER, commit: "
git commit -s -a -m "doc: Push updated generated sphinx documentation of commit ${TRAVIS_COMMIT}" || die
if [ $? -eq 0 ] ; then
    echo 'Push changes to gh-pages branch.'
    git push ${REPO_LINK} gh-pages:gh-pages > /dev/null 2>&1 || die
else
    echo 'No update in gh-pages branch, no need to push changes!'
fi

exit 0
