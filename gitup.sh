#!/bin/bash

currentDate=`date +%s`

git add .
git commit -m "$1:: $currentDate"
git push -u origin master
echo gitupdated at $currentDate
