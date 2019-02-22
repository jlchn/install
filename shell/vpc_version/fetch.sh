cd script

touch ../$1
echo '' > ../$1
find * -prune -type d | while IFS= read -r d; do 
    grep  "vpc_version" $d/version_info.yml | awk -F ":" -v d=$d -v v=$3 -v OFS=":" '{print d,$2}' >> ../$1
    grep  "conversion_version" $d/version_info.yml | awk -F ":" -v d=$d"-conversion" -v v=$2 -v OFS=":" '{print d,$2}' >> ../$1
done
