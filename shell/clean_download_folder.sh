#!/bin/bash

timestamp=$(date +%Y%m%d_%H%M%S)
path="/home/jiangli/Downloads"
log=$path/folder_clean.log

find $path  -type f -mtime +7 -print -delete >> $log
find $path  -type d -empty -print -delete >> $log
echo "Clean Finished at: $(date +%Y%m%d_%H%M)" >> $log
