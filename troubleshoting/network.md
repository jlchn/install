# netstat

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

https://www.robustperception.io/how-much-of-the-time-is-my-network-usage-over-a-certain-amount

## show active Internet connections

- Recv-Q: receive queue in bytes
- Send-Q: sent queue in bytes


```
netstat -a --inet

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

