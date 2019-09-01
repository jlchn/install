
### simulate CPU intensive process

Pay attention to the High usr time and low iowait time.

```
# make one CPU 100% buzy
stress --cpu 1 --timeout 600

# monitor cpu load
watch -d uptime

# report the cpu usage every 5 seconds
mpstat -P ALL 5
Linux 4.15.0-46-generic (jiangli) 	03/28/2019 	_x86_64_	(4 CPU)

03:46:55 PM  CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
03:47:00 PM  all   28.26    0.00    1.10    0.15    0.00    0.15    0.00    0.00    0.00   70.34
03:47:00 PM    0  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
03:47:00 PM    1    3.83    0.00    1.21    0.20    0.00    0.20    0.00    0.00    0.00   94.56
03:47:00 PM    2    3.60    0.00    1.80    0.60    0.00    0.00    0.00    0.00    0.00   94.00
03:47:00 PM    3    5.78    0.00    1.39    0.00    0.00    0.00    0.00    0.00    0.00   92.83

03:47:00 PM  CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
03:47:05 PM  all   29.78    0.00    1.63    0.25    0.00    0.20    0.00    0.00    0.00   68.15
03:47:05 PM    0   99.80    0.00    0.20    0.00    0.00    0.00    0.00    0.00    0.00    0.00
03:47:05 PM    1    5.72    0.00    1.78    0.00    0.00    0.59    0.00    0.00    0.00   91.91
03:47:05 PM    2    8.11    0.00    2.90    0.97    0.00    0.39    0.00    0.00    0.00   87.64
03:47:05 PM    3    6.55    0.00    1.59    0.00    0.00    0.00    0.00    0.00    0.00   91.87

# use pidstat to find which process takes the most cpu
pidstat -u 5 2           
Linux 4.15.0-46-generic (jiangli) 	03/28/2019 	_x86_64_	(4 CPU)

04:25:32 PM   UID       PID    %usr %system  %guest   %wait    %CPU   CPU  Command
04:25:37 PM  1000      7477  100.00    0.00    0.00    0.00  100.00     3  stress
......
04:25:37 PM  1000     29732    0.20    0.00    0.00    0.40    0.20     1  chrome
......


04:25:37 PM   UID       PID    %usr %system  %guest   %wait    %CPU   CPU  Command
04:25:42 PM  1000      7477  100.00    0.00    0.00    0.00  100.00     3  stress
......
04:25:42 PM  1000      8803    0.00    0.20    0.00    0.00    0.20     1  pidstat
......

```

### simulate IO intensive processes

Pay attention to the High iowait time and low usr time.

```
# create 3000 io workers
stress -i 3000 --timeout 1000

watch -d uptime       
17:34:52 up  7:14,  1 user,  load average: 2749.90, 1181.71, 467.39

mpstat -P ALL 5

05:35:27 PM  CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
05:35:32 PM  all    3.53    0.00   38.08   40.92    0.00    0.60    0.00    0.00    0.00   16.87
05:35:32 PM    0    3.58    0.00   39.96   38.17    0.00    0.20    0.00    0.00    0.00   18.09
05:35:32 PM    1    3.54    0.00   38.78   41.73    0.00    0.00    0.00    0.00    0.00   15.94
05:35:32 PM    2    3.41    0.00   35.07   42.89    0.00    2.61    0.00    0.00    0.00   16.03
05:35:32 PM    3    3.59    0.00   38.25   40.64    0.00    0.00    0.00    0.00    0.00   17.53

# check which one consumes lots of cpu time by checking iowait
pidstat -u 5
......
05:33:43 PM  1000     31767    0.00    0.20    0.00    8.20    0.20     1  stress
05:33:43 PM  1000     31780    0.00    0.20    0.00    6.60    0.20     1  stress
05:33:43 PM  1000     31786    0.00    0.20    0.00    6.80    0.20     2  stress
05:33:43 PM  1000     31792    0.00    0.20    0.00    7.80    0.20     1  stress
05:33:43 PM  1000     31794    0.00    0.20    0.00    7.40    0.20     1  stress
05:33:43 PM  1000     31802    0.00    0.20    0.00    6.60    0.20     3  stress
05:33:43 PM  1000     31806    0.00    0.20    0.00    8.40    0.20     0  stress
05:33:43 PM  1000     31828    0.00    0.20    0.00    7.40    0.20     0  stress
05:33:43 PM  1000     31829    0.00    0.20    0.00    6.60    0.20     1  stress
05:33:43 PM  1000     31833    0.00    0.20    0.00    7.00    0.20     0  stress
....


