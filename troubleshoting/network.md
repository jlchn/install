# netstat

## show connected sockets

- Recv-Q: receive queue in bytes
- Send-Q: sent queue in bytes

```shell

netstat # without showing LISTENING state sockets
netstat -a # show both listening and non-listening(for TCP this means established connections) sockets.
netstat -at # show both listening and non-listening sockets of TCP 
netstat -au # show both listening and non-listening sockets of UDP
netstat -ax # show both listening and non-listening sockets of UNIX Domain 
netstat -lt # shot tcp sockets in listening states
netstat -a --inet # show only internet connections


Active Internet connections (servers and established)
Proto Recv-Q Send-Q Local Address           Foreign Address         State
tcp        0      0 0.0.0.0:sunrpc          0.0.0.0:*               LISTEN
tcp        0      0 0.0.0.0:http            0.0.0.0:*               LISTEN
tcp        0      0 localhost:domain        0.0.0.0:*               LISTEN
tcp        0      0 0.0.0.0:ssh             0.0.0.0:*               LISTEN
tcp        0      0 192.168.0.107:ssh       realip.test:58106       ESTABLISHED
udp        0      0 localhost:domain        0.0.0.0:*
udp        0      0 192.168.0.107:bootpc    0.0.0.0:*
udp        0      0 0.0.0.0:sunrpc          0.0.0.0:*
udp        0      0 0.0.0.0:678             0.0.0.0:*

netstat -p --inet # list process with pid and program name displayed 

Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name    
tcp        0      0 jlchn:20436           sb-in-f188.1e100.n:5228 ESTABLISHED 5835/chrome         
tcp        0      0 eureka-1:55200          eureka-1:32997          ESTABLISHED -                   
tcp        0      0 jlchn:27684           123.58.182.252:https    ESTABLISHED 5835/chrome         
tcp        0      0 jlchn:10898           ec2-13-115-86-198:https ESTABLISHED 5835/chrome         
tcp        0      0 eureka-1:32997          eureka-1:55230          ESTABLISHED -                   
tcp        0      0 eureka-1:32997          eureka-1:55200          ESTABLISHED -                   
tcp        0      0 jlchn:16708           server-13-35-21-1:https ESTABLISHED 5835/chrome         
tcp        0      0 eureka-1:19357          eureka-1:51764          ESTABLISHED -                   
tcp        0      0 eureka-1:55202          eureka-1:32997          ESTABLISHED -                   
tcp        0      0 jlchn:42940           lb-140-82-114-26-:https ESTABLISHED 5835/chrome         
tcp        0      0 jlchn:58882           ec2-54-246-109-35:https ESTABLISHED 5835/chrome         
tcp        0      0 eureka-1:51760          eureka-1:19357          ESTABLISHED -                   
tcp        0      0 jlchn:23470           223.252.199.69:https    ESTABLISHED 5835/chrome 

netstat -np --inet # display ip instead of hostname

Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name    
tcp        0      0 172.26.143.21:20436     74.125.130.188:5228     ESTABLISHED 5835/chrome         
tcp        0      0 127.0.0.1:55200         127.0.0.1:32997         ESTABLISHED -                   
tcp        0      0 172.26.143.21:27684     123.58.182.252:443      ESTABLISHED 5835/chrome         
tcp        0      1 172.26.143.21:54874     13.35.55.125:443        SYN_SENT    5835/chrome         
tcp        0      0 172.26.143.21:10898     13.115.86.198:443       ESTABLISHED 5835/chrome         
tcp        0      0 127.0.0.1:32997         127.0.0.1:55230         ESTABLISHED -                   
tcp        0      0 172.26.143.21:43372     140.82.114.26:443       ESTABLISHED 5835/chrome         
tcp        0      0 172.26.143.21:30188     74.125.130.100:443      ESTABLISHED 5835/chrome         
tcp        0      0 172.26.143.21:57198     122.14.229.64:443       ESTABLISHED 5835/chrome         
tcp        0      0 172.26.143.21:52690     140.82.114.25:443       ESTABLISHED 5835/chrome         
tcp        0      0 172.26.143.21:17276     52.84.229.159:443       ESTABLISHED 5835/chrome      

netstat -an | grep ':8080' # which process is using a particular port
netstat -apn | grep 'java' # display specific process related sockets
netstat -np --net -c # display repeatly

```

## show network interfaces

```
netstat -ni # -n -> show numeric address instead of names

Kernel Interface table
Iface      MTU    RX-OK RX-ERR RX-DRP RX-OVR    TX-OK TX-ERR TX-DRP TX-OVR Flg
docker0   1500        0      0      0 0             0      0      0      0 BMU
enp0s3    1500   113777      0      0 0         79996      0      0      0 BMRU
lo       65536      152      0      0 0           152      0      0      0 LRU
```

## show route table

```
netstat -nr

Kernel IP routing table
Destination     Gateway         Genmask         Flags   MSS Window  irtt Iface
0.0.0.0         192.168.0.1     0.0.0.0         UG        0 0          0 enp0s3
172.17.0.0      0.0.0.0         255.255.0.0     U         0 0          0 docker0
192.168.0.0     0.0.0.0         255.255.255.0   U         0 0          0 enp0s3
192.168.0.1     0.0.0.0         255.255.255.255 UH        0 0          0 enp0s3
```

## show statistics of each protocol

```shell
netstat -st # statistics of TCP
netstat -su # statistics of UDP

IcmpMsg:
    InType3: 6755
    InType8: 1
    OutType0: 1
    OutType3: 312
Udp:
    1198056 packets received
    296 packets to unknown port received
    0 packet receive errors
    245174 packets sent
    0 receive buffer errors
    0 send buffer errors
    IgnoredMulti: 33015
UdpLite:
IpExt:
    InMcastPkts: 129447
    OutMcastPkts: 66929
    InBcastPkts: 98101
    OutBcastPkts: 6489
    InOctets: 2396500419
    OutOctets: 858590909
    InMcastOctets: 10990008
    OutMcastOctets: 9992799
    InBcastOctets: 9837849
    OutBcastOctets: 1401973
    InNoECTPkts: 2308622


```

# traceroute

# nslookup

# ping 

# tcpdump


##  list of network interfaces available on the system
``` bash
tcpdump -D
# 1.docker_gwbridge [Up, Running]
# 2.eno1 [Up, Running]
# 3.veth6795cc2 [Up, Running]

```


## tcpdump references

https://danielmiessler.com/study/tcpdump/

https://hackertarget.com/tcpdump-examples/


# lsof 

- please refer to [list open files](./list-open-files.md)

