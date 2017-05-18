#!/bin/bash
#
# SyncWikiWithRepo - synchronize the wiki examples with the
#                    vtk examples repo
#
# Make sure the wiki is up
echo "Synchronizing the wikiexamples repository with the repository."
HOST=www.kitware.com
REPO=https://github.com/lorensen/VTKExamples
echo "0) Can we access the wiki?"
ping -c 1 $HOST &> /dev/null
if test "${?}" != 0
  then
  echo "VTKExamples: $HOST is not accessible. Try again later" | mail -s "SyncWikiWithRepo failed" bill.lorensen@gmail.com
  exit 1
fi

echo "1) Pull updates from master repositories"
git pull
if ( test -d Tarballs ); then
  (cd Tarballs; git checkout .)
  (cd Tarballs; git pull origin master)
fi

echo "3) Scrape the repo"
src/Admin/ScrapeRepo  src docs ${REPO}

echo "3.1) Check for a successful scrape"
pushd docs
count=$((`find . -name \*.md | wc -l`))
popd
expected=800
if test $count -lt $expected; then
   echo VTKExamples/Admin/ScrapeRepo failed
   echo VTKExamples: Expected at least $expected md files but only found $count md | mail -s "SyncWikiWithRepo failed" bill.lorensen@gmail.com
   git checkout .
   exit 1
fi

echo "3.2) Update the html pages"
mkdocs build

echo "4) Process modified files"
git commit -m "SYNC: Files modified on wiki." `git status | grep modified: | cut -d":" -f2,2`

echo "5) Process new files"
find . "(" -name \*.html ")" -exec git add {} \;
git commit -m "SYNC: Files added to wiki."

echo "6) Process deleted files"
git rm `git status | grep deleted: | cut -d":" -f2,2`
git commit -m "SYNC: Files deleted (or moved) from wiki."

echo "7) Update tarballs and push to tarball repo"
if ( test -d Tarballs ); then
(cd Tarballs; git add *tar)
(cd Tarballs; git commit -m "SYNC: Tarballs modified")
(cd Tarballs; git push)
fi

echo "8) Push the changes"
git push
