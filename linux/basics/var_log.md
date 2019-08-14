
###  /var/log/syslog

Used in Debian-based systems, it is mainly used to store informational and non-critical system messages.

This is the first log file that the we should check if something goes wrong.

### /var/log/auth.log

All authentication related events, for example: investigate failed login attempts or brute-force attacks.

### /var/log/boot.log

The system initialization script, /etc/init.d/bootmisc.sh, sends all bootup messages to this log file.

Use this file to investigate issues related to improper shutdown, unplanned reboots or booting failures.

### /var/log/dmesg

It contains information related to hardware devices and their drivers.

As the kernel detects physical hardware devices associated with the server during the booting process, it captures the device status, hardware errors and other generic messages.

### /var/log/kern.log

It contains logs output by the kernel.
 
### /var/log/faillog

Failed login attempts.

### /var/log/cron

 records all information including successful execution and error messages of crontab.
 

### /var/log/alternatives.log

logs to record the results of command `update-alternatives`.

```
update-alternatives 2019-03-25 19:08:40: link group editor updated to point to /usr/bin/vim.tiny
```

 #### update-alternatives

it is used to set or allow users to choose the default programs they want to use.

For example, if the text editors `vim` and `nano` are both installed on the system, the alternatives system will set the name /usr/bin/editor  to  refer  to
`/usr/bin/nano` by default. The users can override this and cause it to refer to `/usr/bin/vim.tiny` instead.


```
sudo  update-alternatives --config editor
[sudo] password for XXXXXX: 
There are 5 choices for the alternative editor (providing /usr/bin/editor).

  Selection    Path                Priority   Status
------------------------------------------------------------
* 0            /bin/nano            40        auto mode
  1            /bin/ed             -100       manual mode
  2            /bin/nano            40        manual mode
  3            /usr/bin/code        0         manual mode
  4            /usr/bin/vim.basic   30        manual mode
  5            /usr/bin/vim.tiny    15        manual mode

Press <enter> to keep the current choice[*], or type selection number: 5

```


