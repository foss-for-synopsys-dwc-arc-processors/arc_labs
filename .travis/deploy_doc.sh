#!/bin/sh

REPO_NAME=${REPO_NAME:="github.com/foss-for-synopsys-dwc-arc-processors/arc_labs.git"}
REPO_LINK="https://""${GH_TOKEN}""@""${REPO_NAME}"

die()
{
    echo " *** ERROR: " $*
    exit 1
}

#set -x

# Make documentation
echo 'Generating documentation ...'
cd ../doc
# Generate by sphinx
echo 'Generating html documentation ...'
make html &> build_html.log || die "build doc failed"
# Check if this is a pull request
if [ "$TRAVIS_PULL_REQUEST" != "false" ] ; then
    echo "Don't push built docs to gh-pages for pull request "
    exit 0
fi

# Check if this is master branch
# Only push doc changes to gh-pages when this is master branch
if [ "$TRAVIS_BRANCH" != "master" ] ; then
    echo "Don't push built docs to gh-pages for non master branch "
    exit 0
fi

# Generate latex pdf only on non-pull request master branch
# this is time costing including creating the documentation
echo 'Generating pdf documentation ...'
make latex || die "Build Latex failing"
make latexpdf || die "Build latex pdf failing in phase 1"
make latexpdf || die "Build latex pdf failing in phase 2"
find build/latex -type f -not -name "*.pdf" -delete || die "No latex pdf generated"

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
git commit -s -a -m "doc: Push updated generated sphinx documentation of commit ${TRAVIS_COMMIT}" || die
if [ $? -eq 0 ] ; then
    echo 'Push changes to gh-pages branch.'
    git push ${REPO_LINK} gh-pages:gh-pages > /dev/null 2>&1 || die
else
    echo 'No update in gh-pages branch, no need to push changes!'
fi

exit 0
