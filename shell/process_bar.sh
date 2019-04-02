

i=0
p=''
while [ $i -lt 40 ]
do
	sleep 1
	p="$p#"
	v=$(($i * 100 / 39))
	#echo -ne "\r$v%"
	printf "\r[%s]%d%%"  $p $v
	i=$(($i + 1))       
done

printf '\n'
