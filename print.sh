#! /bin/sh

FOLDERS = $(ls)
INT_I = 5
while read folder1; do
cd "$folder1"
#cat * > "assign$I.txt"
done <<< "$FOLDERS"

