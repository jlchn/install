
# diff  -w -B -i  previous current | grep "^>" | awk -F ">" '{print $2","}' > diff
diff  -w -B -i  previous current | grep "^>" | awk -F ">" '{print $2}' |awk -F ":" '{print $1"="$2"&"}'| xargs echo  | tr -d '[:space:]'> diff
