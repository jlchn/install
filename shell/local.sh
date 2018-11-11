#! /bin/bash

set -x
set -e

f1(){
local xxx=1
echo $xxx;
echo "all variables in a function are global like in js, set it with local to make them local variables"
echo "local can only be used in a function"
}


f1
