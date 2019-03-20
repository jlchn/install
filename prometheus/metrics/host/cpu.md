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

references: https://www.opsdash.com/blog/cpu-usage-linux.html

