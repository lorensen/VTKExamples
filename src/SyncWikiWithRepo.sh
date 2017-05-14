#!/bin/bash
#
# SyncWikiWithRepo - synchronize the wiki examples with the
#                    vtk examples repo
#
# Make sure the wiki is up
echo "Synchronizing the wikiexamples repository with the repository."
HOST=www.kitware.com
REPO=https://gitlab.kitware.com/lorensen/VTKExamples
echo "0) Can we access the wiki?"
ping -c 1 $HOST &> /dev/null
if test "${?}" != 0
  then
  echo "VTKExamples: $HOST is not accessible. Try again later" | mail -s "SyncWikiWithRepo failed" bill.lorensen@gmail.com
  exit 1
fi

echo "1) Pull updates from master repositories"
git pull
(cd wiki; git pull)
if ( test -d Tarballs ); then
  (cd Tarballs; git checkout .)
  (cd Tarballs; git pull origin master)
fi

echo "2) Remove all files from local wiki repository"
(cd wiki; find . -name \*md -exec rm {} \;)

echo "3) Scrape the repo"
./Admin/ScrapeRepo . ./wiki ${REPO}

echo "3.1) Check for a successful scrape"
pushd wiki
count=$((`find . -name \*.md | wc -l`))
popd
expected=800
if test $count -lt $expected; then
   echo VTKExamples/Admin/ScrapeRepo failed
   echo VTKExamples: Expected at least $expected md files but only found $count md | mail -s "SyncWikiWithRepo failed" bill.lorensen@gmail.com
   git checkout .
   exit 1
fi

echo "4) Process modified files"
(cd wiki; git commit -m "SYNC: Files modified on wiki." `git status | grep modified: | cut -d":" -f2,2`)

echo "5) Process new files"
(cd wiki; find . "(" -name \*.md ")" -exec git add {} \;)
(cd wiki; git commit -m "SYNC: Files added to wiki.")

echo "6) Process deleted files"
(cd wiki; git rm `git status | grep deleted: | cut -d":" -f2,2`)
(cd wiki; git commit -m "SYNC: Files deleted (or moved) from wiki.")

echo "7) Update tarballs and push to tarball repo"
if ( test -d Tarballs ); then
(cd Tarballs; git add *tar)
(cd Tarballs; git commit -m "SYNC: Tarballs modified")
(cd Tarballs; git push)
fi

echo "8) Push the changes"
(cd wiki; git push)

