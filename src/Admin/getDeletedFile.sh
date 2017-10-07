#!/bin/bash
#
# Given a file, find that file in a git repository, even if it has been deleted
#
if [ "$#" -ne 1 ]; then
    echo "Usage: getDeletedFile.sh file"
    return
fi
FILE=$1
REPO=`git remote get-url origin`
echo "Looking for " $FILE " in repo " $REPO
FULLNAME=`git log  --diff-filter=D --summary | grep delete | grep /$FILE\$ | cut -d" " -f5,5 | head -1`
#
# Does the file exist now or in the past
if [ -z $FULLNAME ]; then
    echo "Cannot find " $FILE
    exit
fi
#
# Find the hash for the file
SHA=`git log -2 -- $FULLNAME | grep ^commit | tail -1 | cut -d" " -f2,2`
echo "SHA " $SHA
#
# report the date the file was last seen
echo "Last seen on " `git show -s --format=%ci $SHA^`
#
# save the file in the current directory
echo "Saving as " `basename $FULLNAME`
git show $SHA:$FULLNAME > `basename $FULLNAME`

#
# Report the URL that points to the file
PRE=`echo $REPO | sed -e 's/\.git//'`
echo "Original at:"
echo $PRE"/blob/"$SHA"/"$FULLNAME

