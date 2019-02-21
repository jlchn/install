#!bin/sh

echo "process port is $1";

sudo kill -9 $(sudo lsof -t -i:$1)