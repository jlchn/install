
send(){
  STATUSCODE=$(curl -X POST -d @diff -f  --write-out %{http_code} $1)

  if test $STATUSCODE -ne 200; then
    return 1
  fi
  return 0; # true
}
if  send https://requestb.in/v2itf2v2  &&  send https://requestb.in/v2itf2v2 
 then exit 0
 else exit 1
 fi
