We are using `lsof` to get all open files on a linux server.

### 1.list files opened by all active processes

```shell
$ sudo lsof 

COMMAND     PID   TID             USER   FD      TYPE             DEVICE   SIZE/OFF       NODE NAME
systemd       1                   root  cwd       DIR                8,2       4096          2 /
systemd       1                   root  rtd       DIR                8,2       4096          2 /
systemd       1                   root  txt       REG                8,2    1595792    3408245 /lib/systemd/systemd
systemd       1                   root  mem       REG                8,2    1700792    3412613 /lib/x86_64-linux-gnu/libm-2.27.so
```

- **FD** 
  - stands for `file descriptor`, it is a number that uniquely identifies an open file in a computer's operating system. More detail about file descriptors can be found [here](https://www.computerhope.com/jargon/f/file-descriptor.htm)
  - typical values
    - **cwd** -> current working directory
    - **txt** -> text file
    - **mem** -> memory mapped file
    - **mmap** -> memory mapped device
    - **DEL** -> ?
    - **actual number** -> represent the actual file descriptor number.
      - 100r -> the file whoes file descriptor number is 100 was open in read mode
      - 100w -> the file whoes file descriptor number is 100 was open in write mode
      -> 100u -> the file whoes file descriptor number is 100 was open in read and write mode
- **TYPE**
  - **REG** –> regular file
  - **DIR** –> directory
  - **FIFO**
  - **CHR** –> character special file
  
 
 ### 2.list all open files by a pid
  
  ```shell
$ sudo lsof -p 20        

COMMAND   PID USER   FD      TYPE DEVICE SIZE/OFF NODE NAME
watchdog/  20 root  cwd       DIR    8,2     4096    2 /
watchdog/  20 root  rtd       DIR    8,2     4096    2 /
watchdog/  20 root  txt   unknown                      /proc/20/exe

  ```

### 3.list all open files filtered by process name(start with)
  
  ```shell
$ sudo lsof -c docker -c java | head -n 10 
COMMAND    PID    USER   FD      TYPE             DEVICE   SIZE/OFF       NODE NAME
dockerd   2363    root  cwd       DIR                8,2       4096          2 /
dockerd   2363    root  rtd       DIR                8,2       4096          2 /
dockerd   2363    root  txt       REG                8,2   81123064   29099375 /usr/bin/dockerd-ce
dockerd   2363    root  mem       REG                8,2     101168    3412689 /lib/x86_64-linux-gnu/libresolv-2.27.so
dockerd   2363    root  mem       REG                8,2      26936    3412638 /lib/x86_64-linux-gnu/libnss_dns-2.27.so
java      3050 jenkins  cwd       DIR                8,2       4096          2 /
java      3050 jenkins  rtd       DIR                8,2       4096          2 /
java      3050 jenkins  txt       REG                8,2       7734    5118829 /usr/lib/jvm/java-8-oracle/jre/bin/java
java      3050 jenkins  DEL       REG                8,2               3278891 /tmp/jna--1712433994/jna6199828470526279850.tmp

  ```
 
 ### 4.list all open files filtered by a user name
  
  ```shell
$ sudo lsof -u jlchn | head -n 10
COMMAND     PID    USER   FD      TYPE             DEVICE   SIZE/OFF       NODE NAME
chrome     1662 jlchn  cwd       DIR                0,4          0      56368 /proc/5856/fdinfo
chrome     1662 jlchn  rtd       DIR                0,4          0      56368 /proc/5856/fdinfo
chrome     1662 jlchn  txt       REG                8,2  138262040     266323 /opt/google/chrome/chrome
chrome     1662 jlchn  mem       REG                8,2   18748872     919154 /usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc
chrome     1662 jlchn  DEL       REG               0,24                   182 /dev/shm/.com.google.Chrome.v34KmA
chrome     1662 jlchn  mem       REG                8,2    7745408     918595 /usr/share/fonts/truetype/noto/NotoColorEmoji.ttf
chrome     1662 jlchn  mem       REG                8,2     313436     917650 /usr/share/fonts/truetype/liberation2/LiberationMono-Regular.ttf
chrome     1662 jlchn  DEL       REG               0,24                   183 /dev/shm/.com.google.Chrome.nZp35g
chrome     1662 jlchn  DEL       REG               0,24                   162 /dev/shm/.com.google.Chrome.msQWap


  ```
  
 ### 5.list processes who opening a specific file
You can list only the processes which opened a specific file, by providing the filename as arguments.

``` shell
$ sudo lsof /var/lib/docker/volumes/metadata.db

COMMAND  PID USER   FD   TYPE DEVICE SIZE/OFF    NODE NAME
dockerd 2363 root  mem-W  REG    8,2   131072 5242890 /var/lib/docker/volumes/metadata.db
dockerd 2363 root    9uW  REG    8,2   131072 5242890 /var/lib/docker/volumes/metadata.db

```

 ### 6.list processes who opening a specific file
You can list only the processes which opened a specific file, by providing the filename as arguments.

``` shell
$ sudo lsof /var/lib/docker/volumes/metadata.db

COMMAND  PID USER   FD   TYPE DEVICE SIZE/OFF    NODE NAME
dockerd 2363 root  mem-W  REG    8,2   131072 5242890 /var/lib/docker/volumes/metadata.db
dockerd 2363 root    9uW  REG    8,2   131072 5242890 /var/lib/docker/volumes/metadata.db

```

 ### 7.list all processes who opening files under a specific directorys

``` shell
$ sudo lsof +d /var/log/
COMMAND   PID   USER   FD   TYPE DEVICE SIZE/OFF    NODE NAME
rsyslogd 1347 syslog    7w   REG    8,2   258590 3280106 /var/log/syslog
rsyslogd 1347 syslog    8w   REG    8,2    65301 3280953 /var/log/auth.log
rsyslogd 1347 syslog    9w   REG    8,2    11902 3280824 /var/log/kern.log
ruby     4848   root   14r   REG    8,2      144 3280222 /var/log/test.log.2.current
ruby     4848   root   16r   REG    8,2        0 3280347 /var/log/test.log.3.current

```
### 8.list all processes who opening files under a specific directorys recursively

``` shell
$ sudo lsof +D /var/log/ | head -n 15

COMMAND     PID     USER   FD   TYPE DEVICE SIZE/OFF     NODE NAME
systemd-j   272     root  mem    REG    8,2 16777216  3670288 /var/log/journal/309a90a672af474f9d7457da13c6f0ea/user-1000.journal
systemd-j   272     root  mem    REG    8,2 16777216  3670420 /var/log/journal/309a90a672af474f9d7457da13c6f0ea/system.journal
systemd-j   272     root   29u   REG    8,2 16777216  3670420 /var/log/journal/309a90a672af474f9d7457da13c6f0ea/system.journal
systemd-j   272     root  102u   REG    8,2 16777216  3670288 /var/log/journal/309a90a672af474f9d7457da13c6f0ea/user-1000.journal
kesl_laun  1207     root    1w   REG    8,2   452053 11017222 /var/log/kaspersky/kesl/kesl_launcher.log
kesl_laun  1207     root    2w   REG    8,2   452053 11017222 /var/log/kaspersky/kesl/kesl_launcher.log
rsyslogd   1347   syslog    7w   REG    8,2   258590  3280106 /var/log/syslog
rsyslogd   1347   syslog    8w   REG    8,2    65598  3280953 /var/log/auth.log
rsyslogd   1347   syslog    9w   REG    8,2    11902  3280824 /var/log/kern.log
unattende  1876     root    3w   REG    8,2        0  3289894 /var/log/unattended-upgrades/unattended-upgrades-shutdown.log
postgres   2103 postgres    1w   REG    8,2        0 11016619 /var/log/postgresql/postgresql-9.4-main.log
postgres   2103 postgres    2w   REG    8,2        0 11016619 /var/log/postgresql/postgresql-9.4-main.log
postgres   2103 postgres    4w   REG    8,2        0 11016619 /var/log/postgresql/postgresql-9.4-main.log
postgres   2129 postgres    1w   REG    8,2        0 11016618 /var/log/postgresql/postgresql-11-main.log

```

### 9.list processes which are using a specific mount point

this is usually very helpful when dealing with "Device or Resource Busy" error. 

```shell
$ sudo lsof +D /var # or
$ sudo lsof /var
```
### 10.only list process id

```shell
$ lsof -t +D /var
$ sudo kill -9 `lsof -t +D /var` # kill processes which cause "Device or Resource Busy" error. 
```

### 11. list network related opening files(all network connections)

```shell
$ sudo lsof -i 

sudo lsof -i 
COMMAND     PID            USER   FD   TYPE  DEVICE SIZE/OFF NODE NAME
systemd-r   842 systemd-resolve   12u  IPv4   20688      0t0  UDP localhost:domain 
systemd-r   842 systemd-resolve   13u  IPv4   20689      0t0  TCP localhost:domain (LISTEN)
avahi-dae  1054           avahi   12u  IPv4   22334      0t0  UDP *:mdns 
avahi-dae  1054           avahi   13u  IPv6   22335      0t0  UDP *:mdns 
avahi-dae  1054           avahi   14u  IPv4   22336      0t0  UDP *:13400 
avahi-dae  1054           avahi   15u  IPv6   22337      0t0  UDP *:59117 
Main       1496        www-data    5u  IPv4   30918      0t0  TCP *:8084 (LISTEN)
sshd       2061            root    3u  IPv4   68430      0t0  TCP *:ssh (LISTEN)
sshd       2061            root    4u  IPv6   68432      0t0  TCP *:ssh (LISTEN)
postgres   2103        postgres    6u  IPv6   30949      0t0  TCP ip6-localhost:5433 (LISTEN)
postgres   2103        postgres    7u  IPv4   30950      0t0  TCP eureka-1:5433 (LISTEN)
postgres   2103        postgres   11u  IPv6   32054      0t0  UDP ip6-localhost:20778->ip6-localhost:20778 
postgres   2129        postgres    6u  IPv6   27636      0t0  TCP ip6-localhost:postgresql (LISTEN)
postgres   2129        postgres    7u  IPv4   27637      0t0  TCP eureka-1:postgresql (LISTEN)

```

### 12. list network related opening files(all network connections)

```shell
$ sudo lsof -i #  use '-i 4' or '-i 6' to list only IPV4 or IPV6 respectively

sudo lsof -i 
COMMAND     PID            USER   FD   TYPE  DEVICE SIZE/OFF NODE NAME
systemd-r   842 systemd-resolve   12u  IPv4   20688      0t0  UDP localhost:domain 
systemd-r   842 systemd-resolve   13u  IPv4   20689      0t0  TCP localhost:domain (LISTEN)
avahi-dae  1054           avahi   12u  IPv4   22334      0t0  UDP *:mdns 
avahi-dae  1054           avahi   13u  IPv6   22335      0t0  UDP *:mdns 
avahi-dae  1054           avahi   14u  IPv4   22336      0t0  UDP *:13400 
avahi-dae  1054           avahi   15u  IPv6   22337      0t0  UDP *:59117 
Main       1496        www-data    5u  IPv4   30918      0t0  TCP *:8084 (LISTEN)
sshd       2061            root    3u  IPv4   68430      0t0  TCP *:ssh (LISTEN)
sshd       2061            root    4u  IPv6   68432      0t0  TCP *:ssh (LISTEN)
postgres   2103        postgres    6u  IPv6   30949      0t0  TCP ip6-localhost:5433 (LISTEN)
postgres   2103        postgres    7u  IPv4   30950      0t0  TCP eureka-1:5433 (LISTEN)
postgres   2103        postgres   11u  IPv6   32054      0t0  UDP ip6-localhost:20778->ip6-localhost:20778 
postgres   2129        postgres    6u  IPv6   27636      0t0  TCP ip6-localhost:postgresql (LISTEN)
postgres   2129        postgres    7u  IPv4   27637      0t0  TCP eureka-1:postgresql (LISTEN)

```

### 13.list all network connections filtered by a specific process

```shell
$ sudo lsof -i -p 12456
$ sudo lsof -i -c java
```

### 14.list process which is listening on a specific port
```shell
$ sudo lsof -i :8080
```
### 15. list connections with remote server address

```shell
$ sudo lsof -i @172.26.143.255 # 172.26.143.255 is a remote server
COMMAND  PID USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
nmbd    2364 root   18u  IPv4  34696      0t0  UDP 172.26.143.255:netbios-ns 
nmbd    2364 root   20u  IPv4  34698      0t0  UDP 172.26.143.255:netbios-dgm
```

### 16.list repeatly after n intervals

```shell
$ sudo lsof -i :8080 -r 3 # refresh the list every 3 seconds
```

