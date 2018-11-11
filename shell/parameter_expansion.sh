#! /bin/bash


filename=${1:-~/tmp/test.txt}

echo $filename

filetype=${2:?filetype should be provided!}
