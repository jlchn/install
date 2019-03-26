
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
