#! /bin/bash

filepath="2019-01-17.0.log"

DAU=`cat ${filepath} | grep -vE "websocket"|awk -F '\t' '{print $6}'|grep -vwE "USER_NAME:null"|sort|uniq|wc -l`
DA=`cat ${filepath} |grep -vE "websocket" | wc -l`
TOP10AU=`cat ${filepath} |grep -vE "websocket"|awk -F '\t' '{print $6}'|grep -vwE "USER_NAME:null"|sort|uniq -c |sort -nr|head -n 10`

echo $DAU
echo $DA
echo $TOP10AU
