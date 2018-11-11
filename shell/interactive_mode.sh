#! /bin/bash
set -e

function usage()
{
echo "-v -f -h";
}
interactive=
filename=~/system_page.html

while [ "$1" != "" ]; do
    case $1 in
        -f | --file )           shift
                                filename=$1
                                ;;
        -v)                     set -x
                                ;;
        -h | --help )           usage
                                exit
                                ;;
        -i )                    interactive=1
                                ;;
    esac
    shift
done


if [ "$interactive" = "1" ]; then

    response=

    echo -n "Enter name of output file [$filename] > "
    read response
    if [ -n "$response" ]; then
        filename=$response
    fi

    if [ -f $filename ]; then
        echo -n "Output file exists. Overwrite? (y/n) > "
        read response
        if [ "$response" != "y" ]; then
            echo "Exiting program."
            exit 1
        fi
    fi
fi


echo $filename
