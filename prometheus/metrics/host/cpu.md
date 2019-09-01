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

Steal time is the percentage of time a virtual CPU waits for a real CPU while the hypervisor is servicing another virtual processor.

When running in a virtualized environment, the hypervisor may “steal” cycles that are meant for your CPUs and give them to another

AWS EC2 may have big steal time if you use Burstable Performance Instances.

T2 instances are for workloads that don’t use the full CPU often or consistently, but occasionally need to burst.

https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/burstable-performance-instances.html

http://mamchenkov.net/wordpress/2015/12/12/cpu-steal-time-now-on-amazon-ec2/

#### nice

Times when CPU is running below-normal priority tasks.

#### irq and softirq

CPU is verving the interrupt requests.

#### guest and guest nice
the percentage of time spent by the CPU or CPUs to run a virtual processor. These numbers are already included in user and nice.

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

```
mpstat
Linux 4.15.0-46-generic (jiangli) 	03/20/2019 	_x86_64_	(4 CPU)

03:00:17 PM  CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
03:00:17 PM  all    4.50    0.01    1.79    0.73    0.00    0.07    0.00    0.00    0.00   92.91

# print the usage of the first CPU
mpstat -P 0

Linux 4.15.0-46-generic (jiangli) 	03/28/2019 	_x86_64_	(4 CPU)

03:27:22 PM  CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
03:27:22 PM    0   11.13    0.04    2.53    1.69    0.00    0.19    0.00    0.00    0.00   84.43

# print the usage of ALL CPU
mpstat -P ALL
Linux 4.15.0-46-generic (jiangli) 	03/28/2019 	_x86_64_	(4 CPU)

03:29:00 PM  CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
03:29:00 PM  all   11.11    0.04    2.58    2.01    0.00    0.15    0.00    0.00    0.00   84.12
03:29:00 PM    0   11.13    0.04    2.53    1.68    0.00    0.19    0.00    0.00    0.00   84.43
03:29:00 PM    1   10.92    0.04    2.60    1.53    0.00    0.14    0.00    0.00    0.00   84.77
03:29:00 PM    2   11.21    0.03    2.58    2.97    0.00    0.13    0.00    0.00    0.00   83.07
03:29:00 PM    3   11.18    0.04    2.59    1.85    0.00    0.13    0.00    0.00    0.00   84.20

# show 4 reports about CPU utilization with 3 seconds intervals
mpstat 3 4   
Linux 4.15.0-46-generic (jiangli) 	03/28/2019 	_x86_64_	(4 CPU)

03:30:39 PM  CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
03:30:42 PM  all    6.59    0.00    2.28    0.00    0.00    0.17    0.00    0.00    0.00   90.96
03:30:45 PM  all    9.48    0.00    2.28    0.51    0.00    0.08    0.00    0.00    0.00   87.65
03:30:48 PM  all   15.14    0.00    3.57    0.00    0.00    0.34    0.00    0.00    0.00   80.95
03:30:51 PM  all   14.18    0.00    3.07    2.13    0.00    0.09    0.00    0.00    0.00   80.53
Average:     all   11.33    0.00    2.80    0.66    0.00    0.17    0.00    0.00    0.00   85.04

```


### Metrics defined on top of Prometheus

cpu usage : how many CPU times used in a second
```
sum (irate (node_cpu{job="node-exporter",mode=~"user|system",instance=~"$instance:9100"}[5m]) ) without(mode)
```

### CPU load

#### Concept

the number of processes being executed by the CPU or in waiting state. 

#### the average load

the average CPU load calculated over a given period of time of 1, 5 and 15 minutes.

the average load technically is the average numbers of processes in the kernel execution queue tagged as running/runable or uninterruptable. refers [here](https://stackoverflow.com/questions/223644/what-is-an-uninterruptable-process) for what is uninteruptable processes.

if the average load is high, it indicates the CPU is under a high presure.

#### Ways to check the average load

##### uptime

by command `uptime` we can see the CPU load

```
03:29:16 up  2:48,  2 users,  load average: 1.00, 0.58, 2.10
```
it tells:

- load average over the last 1 minute is 1
- load average over the last 5 minutes is 0.58
- load average over the last 15 minutes is 2.10

##### top 

```
$top
top - 06:49:11 up 13 min,  2 users,  load average: 0.00, 0.08, 0.10
Tasks:  94 total,   1 running,  53 sleeping,   0 stopped,   0 zombie
%Cpu(s):  0.0 us,  0.3 sy,  0.0 ni, 99.7 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
KiB Mem :  1009112 total,   446788 free,   144968 used,   417356 buff/cache
KiB Swap:  2017276 total,  2017276 free,        0 used.   713368 avail Mem
```

#### the average load and CPU core numbers


On multi-processor/multi-cores system, the load is related to the number of processor cores. 

```
03:29:16 up  2:48,  2 users,  load average: 1.00, 0.58, 2.10
```

on a single processor system, it tells:

- load average over the last 1 minute is 1, the CPU is under 100% utilization during the last minute, no processes are waiting for CPU.
- load average over the last 5 minutes is 0.58, the CPU is 58% busy during the last 5 minutes, no processes are waiting for CPU.
- load average over the last 15 minutes is 2.10, the CPU is 100% busy during the last 15 minutes, 1.1 processes(average value) are waiting for CPU in the queue.

on a double processor/core system, it tells:

- load average over the last 1 minute is 1, the CPU is under 50%(100%/2) utilization during the last minute, no processes are waiting for CPU.
- load average over the last 5 minutes is 0.58, the CPU is 29%(58%/2) busy during the last 5 minutes, no processes are waiting for CPU.
- load average over the last 15 minutes is 2.10, the CPU is 100%(210%/2 > 100%) busy during the last 15 minutes, 0.1 processes(average value) are waiting for CPU in the queue.


#### CPU average load vs CPU utilization

The average load is not identical to CPU utilization.

CPU utilization tells how much time a CPU was running over a period time, for example, 50% utilization means a CPU spent 50% time running on some tasks, and 50% stys idle.

The average load indicates the average numbers of processes in running/ruanable and uninteruptable states. Which means it includes the processes running on CPU, waiting in the queue for CPU and waiting for I/O.

CPU intensive tasks will make CPU in a high utilization mode, and it will also posibly make a high CPU load. 

IO intensive tasks will not make CPU in a high utilization mode, but it will make CPU in high load

refers [here](https://github.com/jlchn/notes/blob/master/monitoring/performance_simulation.md) to check how to simulate CPU intensive tasks and IO intensive tasks.

references: https://scoutapp.com/blog/understanding-load-averages

