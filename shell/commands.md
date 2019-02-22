
### show ports and process that owns them

```
sudo lsof -i
sudo netstat -lptu
sudo netstat -tulpn
```
### get result of a command
```
result=$(pwd)
result=`pwd`
```

### get exit code of a command
```
grep "^$username" $PASSWD_FILE > /dev/null ; result=$?; echo $result;
```

### add timestamp to filename
```
REMOTE_FILE="/tmp/$(date "+%Y%m%d%H%M%S").sh"
```
kill by port
```
sudo kill -9 $(sudo lsof -t -i:9001)
```

### history
```
history #history list
!998 #repeat n-th command
!ps #repeat the last command that has been executed starting with 'ps'  
```

### grep
```
grep 'warning\|error\|critical' /var/log/messages #find appearances in a file
grep -w 'warning\|error\|critical' /var/log/messages #find words in a file
grep -r '172.26.131.131' . find recursively
```

### tee
used to store and view(at the same time) the output of any other command

example
```
ls | tee file1 #write to stdout, as well as a file
ls | tee -a file2 # append to file
ls | tee file1 | sed 's/old/new/' #write to stdout, and also pass to a command
ls | tee file1 file2 file3 #write the output to multiple files 
```

### tar
```
tar -cvf backup.tar /home/jenkins #create a tar
tar -tvf backup.tar #view tar contains
```
### compare two folders
```
diff -arq folder1 folder2
git diff --no-index dir1/ dir2/
```

### rsync
#### pull
```
rsync -rave "ssh -i ${WORK_TERMINAL_PEM}" ubuntu@${WORK_TERMINAL_IP}:"${BASE_DIR}/${REMOTE_PATH}" ${LOCAL_PATH}rsync -rave "ssh -i ${WORK_TERMINAL_PEM}" ubuntu@${WORK_TERMINAL_IP}:"${BASE_DIR}/${REMOTE_PATH}" ${LOCAL_PATH}
```

#### push
```
rsync -rave  "ssh -i /home/jiangli/Documents/AWS/pem/hue-operation-tool-work-terminal.pem" di.py ubuntu@13.112.122.215:"/tmp/abc.test"
```
#### delete mode
--delete

### zip with password
zip --password (password) file.zip files

### if else
```
if [ "$PASSWORD" == "$VALID_PASSWORD" ]; then
echo "You have access!"
else
echo "ACCESS DENIED!"
fi
```

### case

```
case "${REMOTE_FILE_TYPE}" in

   "py") ssh -i ${WORK_TERMINAL_PEM}  ubuntu@${WORK_TERMINAL_IP} "py ${REMOTE_FILE} ${REMOTE_FILE_PARAMETERS}"
   ;;

   "yml" | "yaml") ssh -i ${WORK_TERMINAL_PEM}  ubuntu@${WORK_TERMINAL_IP} "ansible-playbook ${SCRIPT_ROOT_DIR}/${REMOTE_FILE} -i ${SCRIPT_ROOT_DIR}/inventory ${REMOTE_FILE_PARAMETERS}"
   ;;

   *) ssh -i ${WORK_TERMINAL_PEM}  ubuntu@${WORK_TERMINAL_IP} "bash ${REMOTE_FILE} ${REMOTE_FILE_PARAMETERS}"
   ;;

esac
```