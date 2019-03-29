### buffer and cache

A buffer is a temporary location to store data for a particular application and this data is not used by any other application. This is similar to bandwidth concept. When you try to send burst of data through network, if your network card is capable of sending less data, it will keep these huge amounts of data in buffer so that it can send data constantly in lesser speeds. In other hand Cache is a memory location to store frequently used data for faster access. Other difference between a buffer and a cache is that cache can be used multiple times where as buffer is used single time

Linux always tries to use RAM to speed up future disk operations by using available memory for buffers (file system metadata) and cache (pages with actual contents of files or block devices).

### free command
```
free 
             total       used                   free                       shared    buffers     cached
Mem:      32947952       11060492(total-used)   21887460(total-free)       2328     210216    2137780
-/+ buffers/cache:       8712496 (actual-used)  24235456(actual-free)
Swap:            0          0          0

```

32947952 (= total-used + total-free): total physical RAM

11060492 (= actual-used + buffers + cached ): total used RAM, including buffers and cached data size as well.

21887460 (= actual-free - buffers - cached): total available RAM for new processes.


the `Mem` line is on os' perspective, os see the buffers and cached are used memory.

the `-/+ buffers/cache` line is on user applications' perspecitve, os will free buffer and cache when there is no enough space for user applications.



