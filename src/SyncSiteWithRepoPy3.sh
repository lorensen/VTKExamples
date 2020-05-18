#!/bin/bash
#
# This is a currently untested Python 3 version of SyncSiteWithRepo.sh
#
# SyncSiteWithRepoPy3 - synchronize the examples site with the
#                    examples repo
#
if [ $# -lt 2 ]
  then
  echo "Usage: SyncSiteWithRepoPy3 REPO_URL VTK_SOURCE_DIR"
  echo "e.g  : ./src/SyncSiteWithRepoPy3.sh https::/github.com/<github_username>/VTKExamples /home/<username>/Development/Kitware/src/VTK/"
  echo "Note  : This is run from the top-level VTKExamples directory."
  echo "e.g  : /home/<username>/Development/Kitware/src/VTKExamples/"
  exit 1
fi
REPO=$1
VTK_SOURCE_DIR=$2
# Make sure the repo site is up
echo "Synchronizing the VTKExamples site with the repository."
# HOST=www.github.com
# echo "0) Can we access the repo?"
# ping -c 1 $HOST &> /dev/null
# if test "${?}" != 0
#   then
#   echo "VTKExamples: $HOST is not accessible. Try again later"
#   exit 1
# fi

echo "1) Pull updates from master repositories"
git pull
if ( test -d src/Tarballs ); then
  (cd src/Tarballs; git checkout .)
  (cd src/Tarballs; git pull origin master)
  (cd src/Tarballs; rm *.tar)
fi

echo "2) Create coverage files"
(cd src/Admin; python ./VTKClassesUsedInExamples.py -a ..; python ./VTKClassesUsedInExamples.py -a -u ..)

echo "3) Scrape the repo"
rm -rf docs/*
rm -rf site/*
src/Admin/ScrapeRepoPy3.py  src docs ${REPO} ${VTK_SOURCE_DIR}

echo "4) Check for a successful scrape"
pushd docs
count=$((`find . -name \*.md | wc -l`))
popd
expected=800
if test $count -lt $expected; then
   echo VTKExamples/Admin/ScrapeRepo failed
   echo VTKExamples: Expected at least $expected md files but only found $count md
   git checkout .
   exit 1
fi

echo "5) Update the html pages"
mkdir docs/stylesheets
cp src/stylesheets/extra.css docs/stylesheets/extra.css
mkdocs build

echo "6) Copy sitemap.xml"
cp src/Admin/sitemap.xml site/sitemap.xml
rm site/mkdocs/search_index.json

echo "6.1 Modify highlight color"
(cd site/assets/stylesheets; sed -i -e 's/background-color:rgba(255,235,59,\.5)/background-color:rgba(240,240,240,.8)/g' application-*.css)

echo "7) Minify Html"
(cd site; find . -name index.html -exec htmlmin {} {} \;)

echo "8) Process modified files"
git commit -m "SYNC: Files modified in the repo." `git status | grep modified: | cut -d":" -f2,2`

echo "8.1) Process new files"
find . "(" -name \*.html ")" -exec git add {} \;
(cd site; git add assets)
git commit -m "SYNC: Files added to the repo."

echo "8.2) Process deleted files"
git rm `git status | grep deleted: | cut -d":" -f2,2`
git commit -m "SYNC: Files deleted (or moved) from the repo."

echo "9) Update tarballs and push to tarball repo"
if ( test -d src/Tarballs ); then
(cd src/Tarballs; git add *tar)
(cd src/Tarballs; git commit -m "SYNC: Tarballs modified")
(cd src/Tarballs; git push)
fi

echo "10) Push the changes"
git push
