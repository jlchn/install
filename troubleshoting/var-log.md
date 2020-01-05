
###  /var/log/syslog

Used in Debian-based systems, it is mainly used to store informational and non-critical system messages.

This is the first log file that the we should check if something goes wrong.

### /var/log/auth.log

All authentication related events, for example: investigate failed login attempts or brute-force attacks.

### /var/log/boot.log

The system initialization script, /etc/init.d/bootmisc.sh, sends all bootup messages to this log file.

Use this file to investigate issues related to improper shutdown, unplanned reboots or booting failures.

### /var/log/dmesg

When the system boots up, it prints messages on the screen.

These messages are also in kernel ring buffer, which contains information related to hardware devices and their drivers.

As the kernel detects physical hardware devices associated with the server during the booting process, it captures the device status, hardware errors and other generic messages.

Whenever the new message comes the old message gets overwritten.

```shell

dmesg | head -n 50

[    0.000000] microcode: microcode updated early to revision 0x27, date = 2019-02-26
[    0.000000] Linux version 4.15.0-66-generic (buildd@lgw01-amd64-044) (gcc version 7.4.0 (Ubuntu 7.4.0-1ubuntu1~18.04.1)) #75-Ubuntu SMP Tue Oct 1 05:24:09 UTC 2019 (Ubuntu 4.15.0-66.75-generic 4.15.18)
[    0.000000] Command line: BOOT_IMAGE=/boot/vmlinuz-4.15.0-66-generic root=UUID=0333fb8f-94d0-4702-bca6-215c27a66acf ro quiet splash vt.handoff=1
[    0.000000] KERNEL supported cpus:
[    0.000000]   Intel GenuineIntel
[    0.000000]   AMD AuthenticAMD
[    0.000000]   Centaur CentaurHauls
[    0.000000] x86/fpu: Supporting XSAVE feature 0x001: 'x87 floating point registers'
[    0.000000] x86/fpu: Supporting XSAVE feature 0x002: 'SSE registers'
[    0.000000] x86/fpu: Supporting XSAVE feature 0x004: 'AVX registers'
[    0.000000] x86/fpu: xstate_offset[2]:  576, xstate_sizes[2]:  256
[    0.000000] x86/fpu: Enabled xstate features 0x7, context size is 832 bytes, using 'standard' format.
[    0.000000] e820: BIOS-provided physical RAM map:
[    0.000000] BIOS-e820: [mem 0x0000000000000000-0x0000000000057fff] usable
[    0.000000] BIOS-e820: [mem 0x0000000000058000-0x0000000000058fff] reserved
[    0.000000] BIOS-e820: [mem 0x0000000000059000-0x000000000009cfff] usable
[    0.000000] BIOS-e820: [mem 0x000000000009d000-0x000000000009efff] reserved
[    0.000000] BIOS-e820: [mem 0x000000000009f000-0x000000000009ffff] usable
[    0.000000] BIOS-e820: [mem 0x0000000000100000-0x00000000d1825fff] usable
[    0.000000] BIOS-e820: [mem 0x00000000d1826000-0x00000000d182cfff] ACPI NVS
[    0.000000] BIOS-e820: [mem 0x00000000d182d000-0x00000000d1c62fff] usable
[    0.000000] BIOS-e820: [mem 0x00000000d1c63000-0x00000000d20f7fff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000d20f8000-0x00000000d7ee9fff] usable
[    0.000000] BIOS-e820: [mem 0x00000000d7eea000-0x00000000d7ffffff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000d8000000-0x00000000d875efff] usable
[    0.000000] BIOS-e820: [mem 0x00000000d875f000-0x00000000d87fffff] type 20
[    0.000000] BIOS-e820: [mem 0x00000000d8800000-0x00000000d8fadfff] usable
[    0.000000] BIOS-e820: [mem 0x00000000d8fae000-0x00000000d8ffffff] ACPI data
[    0.000000] BIOS-e820: [mem 0x00000000d9000000-0x00000000da71bfff] usable
[    0.000000] BIOS-e820: [mem 0x00000000da71c000-0x00000000da7fffff] ACPI NVS
[    0.000000] BIOS-e820: [mem 0x00000000da800000-0x00000000dbe20fff] usable
[    0.000000] BIOS-e820: [mem 0x00000000dbe21000-0x00000000dbffffff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000dd000000-0x00000000df1fffff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000f8000000-0x00000000fbffffff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000fec00000-0x00000000fec00fff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000fed00000-0x00000000fed03fff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000fed1c000-0x00000000fed1ffff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000fee00000-0x00000000fee00fff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000ff000000-0x00000000ffffffff] reserved
[    0.000000] BIOS-e820: [mem 0x0000000100000000-0x000000041edfffff] usable
[    0.000000] NX (Execute Disable) protection: active
[    0.000000] efi: EFI v2.31 by American Megatrends
[    0.000000] efi:  ACPI=0xd8fed000  ACPI 2.0=0xd8fed000  SMBIOS=0xf0000 
[    0.000000] secureboot: Secure boot could not be determined (mode 0)
[    0.000000] SMBIOS 2.7 present.
[    0.000000] DMI: Dell Inc. OptiPlex 9020/03CPWF, BIOS A15 11/08/2015
[    0.000000] e820: update [mem 0x00000000-0x00000fff] usable ==> reserved
[    0.000000] e820: remove [mem 0x000a0000-0x000fffff] usable
[    0.000000] e820: last_pfn = 0x41ee00 max_arch_pfn = 0x400000000
[    0.000000] MTRR default type: uncachable

dmesg | grep Memory # view memory 
dmesg | grep eth0 # view interface status
dmesg -c # clear the ring buffer
```




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


