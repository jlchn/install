#! /bin/bash

set -x
set -e

TITLE="System Information for $HOSTNAME"
RIGHT_NOW=$(date +%Y%m%d.%H%M)
TIME_STAMP="Updated on $RIGHT_NOW by $USER"

echo $TITLE
ECHO $TIME_STAMP
