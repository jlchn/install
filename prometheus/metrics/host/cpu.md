### Components of CPU Usage

#### system

The CPU is running in the kernel mode(code). 

This includes running the device drivers and kernel modules.

#### user

The CPU is running code in the user-mode. 

If an application tries to read from disk or write to network, it actually goes to sleep while the kernel performs the work in the kernel-mode.

#### iowait

iowait is the percentage of time the CPU is idle AND there is at least one I/O in progress.

#### idle

when there is really nothing the kernel can do, Technically, when the runnable queue is empty and there are no I/O operations going on, the CPU usage is marked as idle

reference: https://blog.pregos.info/wp-content/uploads/2010/09/iowait.txt

#### steal

When running in a virtualized environment, the hypervisor may “steal” cycles that are meant for your CPUs and give them to another

#### nice

Times when CPU is running below-normal priority tasks.

#### irq and softirq

CPU is verving the interrupt requests.

#### guest and guest nice
he process (a hypervisor) is running a virtual CPU. These numbers are already included in user and nice.

### Get the Raw Values

The CPU usage values are maintained by the kernel, in memory. These values are exposed via the proc filesystem, as the /proc/stat file:

```

> cat /proc/stat
cpu  1240396 2401 497450 26253173 205831 0 17980 0 0 0
cpu0 307985 378 123242 6587553 33006 0 6374 0 0 0
cpu1 308408 498 126681 6578973 32312 0 4550 0 0 0
cpu2 313704 881 123368 6514881 98136 0 4148 0 0 0
cpu3 310297 644 124158 6571765 42375 0 2907 0 0 0
intr 132876057 8 0 0 0 0 0 0 0 1 4 0 0 0 0 0 0 29 0 0 0 0 0 0 35 0 0 0 0 1404769 366740 637513 1779274 28 484 172 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
ctxt 347747552
btime 1552991893
processes 154214
procs_running 1
procs_blocked 0
```
The line with the first field as cpu, shows the actual values of each counter, in this order: user, nice, system, idle, iowait, irq, softirq, steal, guest and guest_nice. These are totalled up numbers for all the CPUs. The remaining lines show the numbers for invidual CPUs

### Tools to monitor CPU usage

#### top

```
top - 14:40:07 up 20:01,  1 user,  load average: 0.54, 0.78, 0.81
Tasks: 383 total,   1 running, 334 sleeping,   0 stopped,   0 zombie
%Cpu(s):  6.4 us,  2.8 sy,  0.0 ni, 90.8 id,  0.1 wa,  0.0 hi,  0.0 si,  0.0 st
KiB Mem : 16331892 total,   473092 free, 12287444 used,  3571356 buff/cache
KiB Swap:  2097148 total,  2078960 free,    18188 used.  2638016 avail Mem 

```
user 6.4%, system: 2.8%, nice: 0, idle: 90.8%, iowait: 0.1%, irq: 0, softirq: 0, steal: 0 

press `1` to usage of each CPU

```
top - 14:44:56 up 20:06,  1 user,  load average: 0.83, 0.72, 0.77
Tasks: 385 total,   1 running, 335 sleeping,   0 stopped,   0 zombie
%Cpu0  :  7.9 us,  5.6 sy,  0.0 ni, 86.6 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
%Cpu1  :  9.4 us,  4.9 sy,  0.0 ni, 85.7 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
%Cpu2  :  7.7 us,  4.0 sy,  0.0 ni, 88.0 id,  0.3 wa,  0.0 hi,  0.0 si,  0.0 st
%Cpu3  :  8.2 us,  4.6 sy,  0.0 ni, 86.5 id,  0.3 wa,  0.0 hi,  0.3 si,  0.0 st
KiB Mem : 16331892 total,   401720 free, 12328740 used,  3601432 buff/cache
KiB Swap:  2097148 total,  2078960 free,    18188 used.  2596240 avail Mem
```
reference: https://superuser.com/questions/575202/understanding-top-command-in-unix/575330#575330

#### vmstat
```
> vmstat
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 6  0  22528 316056 444644 2943224    0    0    19    29   26   56  4  2 93  1  0
 
```
#### mpstat
https://www.tecmint.com/sysstat-commands-to-monitor-linux/

```
mpstat
Linux 4.15.0-46-generic (jiangli) 	03/20/2019 	_x86_64_	(4 CPU)

03:00:17 PM  CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
03:00:17 PM  all    4.50    0.01    1.79    0.73    0.00    0.07    0.00    0.00    0.00   92.91
```





