# netstat

## show connected sockets

- Recv-Q: receive queue in bytes
- Send-Q: sent queue in bytes

```bash

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
netstat -nat|awk  '{print $6}'|sort|uniq -c|sort -rn # sumarize the status of sockets

61 ESTABLISHED
39 LISTEN
9 LAST_ACK
3 TIME_WAIT
3 CLOSE_WAIT

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

```bash
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

# ifconfig 

```bash
ifconfig # show active interfaces
ifconfig -a # show all interfaces
ifconfig vethe6d8da9  # show specific interface
ifconfig vethe6d8da9 down # disable an interface
ifconfig vethe6d8da9 up # enable an interface
ifconfig vethe6d8da9 192.168.2.2 # set an ip for this interface
ifconfig vethe6d8da9 netmask 255.255.255.0 # change the network mask for this intercace
ifconfig vethe6d8da9 promisc # enable promiscuous mode to drop the packet if the packet doesn't belong to itself. In promiscuous mode, the card accepts all the packets which flows through the network card. 
ifconfig vethe6d8da9 -promisc # disable promiscuous mode
```

# ip

refer to [cheatsheet provided by Red Hat](./rh_ip_command_cheatsheet_1214_jcs_print.pdf).

# arp tool

# dns tool
## traceroute

## nslookup

# ping 

## ping commands

## disable ping replies

disable temprarly

```bash
echo "1" >  /proc/sys/net/ipv4/icmp_echo_ignore_all
```

disable permanently

```bash
vim  /etc/sysctl.conf 
net.ipv4.icmp_echo_ignore_all = 1 # add to /etc/sysctl.conf 
sysctl -p # enforce this setting immediately
```

# tcpdump

## useful commands
``` bash
tcpdump -D # list of network interfaces available on the system
1.docker_gwbridge [Up, Running]
2.eno1 [Up, Running]
3.veth6795cc2 [Up, Running]

tcpdump -i eth1 # capture packets from a particular interface

tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
listening on eno1, link-type EN10MB (Ethernet), capture size 262144 bytes
18:51:20.262828 IP 47.246.1.46.https > jlchn.14600: Flags [P.], seq 2761970843:2761971846, ack 780016356, win 223, length 1003
18:51:20.262871 IP jlchn.14600 > 47.246.1.46.https: Flags [.], ack 1003, win 202, length 0
18:51:20.264933 IP jlchn.45244 > dns-sha.workslan.domain: 10314+ [1au] PTR? 21.143.26.172.in-addr.arpa. (55)
18:51:20.265430 IP dns-sha.workslan.domain > jlchn.45244: 10314 NXDomain* 0/1/1 (108)
18:51:20.265546 IP jlchn.45244 > dns-sha.workslan.domain: 10314+ PTR? 21.143.26.172.in-addr.arpa. (44)
18:51:20.266012 IP dns-sha.workslan.domain > jlchn.45244: 10314 NXDomain* 0/1/0 (97)
18:51:20.266864 IP jlchn.51190 > dns-sha.workslan.domain: 5368+ [1au] PTR? 46.1.246.47.in-addr.arpa. (53)
18:51:22.246446 IP jlchn.55491 > 172.26.144.33.domain: 51434+ [1au] PTR? 1.131.26.172.in-addr.arpa. (54)
18:51:22.256772 IP 172.26.143.106.59460 > 239.255.255.250.1900: UDP, length 172
18:51:22.525097 IP jlchn.60427 > 172.26.144.33.domain: 52263+ [1au] PTR? 33.144.26.172.in-addr.arpa. (55)
18:51:22.592502 IP 172.26.144.33.domain > jlchn.60427: 52263 NXDomain 0/1/1 (108)
18:51:22.592666 IP jlchn.60427 > 172.26.144.33.domain: 52263+ PTR? 33.144.26.172.in-addr.arpa. (44)
18:51:22.661533 IP 172.26.144.33.domain > jlchn.60427: 52263 NXDomain 0/1/0 (97)

sudo tcpdump -i eno1 -c 5 # capture packets from a particular interface with limitted number
tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
listening on eno1, link-type EN10MB (Ethernet), capture size 262144 bytes
18:52:35.931328 IP 172.26.143.117.59820 > 239.255.255.250.1900: UDP, length 174
18:52:35.935230 IP jlchn.19687 > 172.26.144.33.domain: 11476+ [1au] PTR? 117.143.26.172.in-addr.arpa. (56)
18:52:36.002526 IP 172.26.144.33.domain > jlchn.19687: 11476 NXDomain 0/1/1 (109)
18:52:36.002651 IP jlchn.19687 > 172.26.144.33.domain: 11476+ PTR? 117.143.26.172.in-addr.arpa. (45)
18:52:36.053118 IP 172.26.143.87.netbios-ns > 172.26.143.255.netbios-ns: NBT UDP PACKET(137): QUERY; REQUEST; BROADCAST
5 packets captured
24 packets received by filter
13 packets dropped by kernel

sudo tcpdump -i eno1 -c 5 -n # use IP instead of hostname
sudo tcpdump -i eno1 -c 5 -n -tttt # display using readable time format
sudo tcpdump -i eno1 -c 5 -XX # display captured packets in HEX and ASCII format
sudo tcpdump -i eno1 -n -tttt tcp # capture specific protocol packages, available values are: tcp, udp, ip, ip6, arp, rarp etc.. 
sudo tcpdump -i eth0 port 8080 # capture packages to specific port
sudo tcpdump -i eno1 -n -tttt host 54.246.102.127 and tcp # capture TCP packets from or to particular IP
sudo tcpdump -i eno1 -n -tttt src 54.246.102.127 and tcp # capture TCP packets from particular IP
sudo tcpdump -i eno1 -n -tttt tcp and port 8443 and dst 54.246.102.127 # capture packets to particular destination IP and Port
sudo tcpdump -i eno1 -n -tttt tcp and port 8443 and net 54.0.0.0/8 # capture TCP packets from or to particular network
sudo tcpdump -i eno1 -n -tttt tcp and port 8443 and dst net 54.0.0.0/8 >0 # capture TCP packets to specific network based on package size
sudo tcpdump  -i eno1 -n -tttt tcp and src 10.0.0.5 and dst port 8080 # capture TCP packets from 10.0.0.5(of any ports) to any destination of ports 8080
sudo tcpdump -i eno1 -c 5 -w output.pcap # save captured packets in file
sudo tcpdump -r /tmp/output.pcap  # save captured packets in file
```

# lsof 

- please refer to [list open files](./list-open-files.md)

