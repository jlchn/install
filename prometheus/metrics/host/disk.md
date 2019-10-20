https://www.robustperception.io/mapping-iostat-to-the-node-exporters-node_disk_-metrics


### IOPS

IOPS (Input/Output Operations Per Second, pronounced i-ops) is a common performance measurement used to benchmark computer storage devices like hard disk drives (HDD), solid state drives (SSD), and storage area networks (SAN).

#### Measuring RW IOPS using fio

```
sudo apt-get install fio
```

create a 4 GB file, and perform 4KB reads and writes using a 75%/25%, with 64 operations running at a time. The 3:1 ratio is a rough approximation of our application.
```
fio --randrepeat=1 --ioengine=libaio --direct=1 --gtod_reduce=1 --name=test --filename=test --bs=4k --iodepth=64 --size=4G --readwrite=randrw --rwmixread=75
```



#### Measuring Read IOPS using fio

```
fio --randrepeat=1 --ioengine=libaio --direct=1 --gtod_reduce=1 --name=test --filename=test --bs=4k --iodepth=64 --size=4G --readwrite=randread
```
#### Measuring Write IOPS using fio

```
fio --randrepeat=1 --ioengine=libaio --direct=1 --gtod_reduce=1 --name=test --filename=test --bs=4k --iodepth=64 --size=4G --readwrite=randwrite

```

### Disk latency

 IOPS is a meaningless figure unless tied to an average latency and a certain request size (how much data is processed with the I/O).

Latency is how fast a single I/O-request is handled.

In a disk drive, read latency is the time required for the controller to find the proper data blocks and place the heads over those blocks (including the time needed to spin the disk platters) to begin the transfer process.

This is a special supermarket, where customers (I/Os) are served by cashiers (disk) at an average speed of 10ms. If you divide one second with 10ms, we understand that this cashier can handle 100 customers per second. But only one at a time, in succession.

It is clear that although the cashier can handle 100 customers per second, he cannot handle them at the same time! So when a customer arrives at the register, and within those 10ms handling time, a second customer arrives, that customer must wait. Once the waiting customer is handled by the cashier, handling of that customer still takes just 10ms, but the overal processing time was maybe 15ms or worst case (two customers arriving at the same time) even 20ms.

This example also illustrates that waiting in line increases the latency for a particular I/O to be handled. So if you increase the Read I/O queue, you will notice that the average latency will increase. Longer queues will mean higher latency, but also more IOPS!!!


```
sudo apt-get install ioping
ioping -c 10 .

4 KiB <<< . (ext4 /dev/sda2): request=1 time=104.8 ms (warmup)
4 KiB <<< . (ext4 /dev/sda2): request=2 time=1.31 s
4 KiB <<< . (ext4 /dev/sda2): request=3 time=5.48 ms
4 KiB <<< . (ext4 /dev/sda2): request=4 time=1.31 s
4 KiB <<< . (ext4 /dev/sda2): request=5 time=458.0 ms
4 KiB <<< . (ext4 /dev/sda2): request=6 time=774.3 ms
4 KiB <<< . (ext4 /dev/sda2): request=7 time=375.3 ms
4 KiB <<< . (ext4 /dev/sda2): request=8 time=174.3 ms
4 KiB <<< . (ext4 /dev/sda2): request=9 time=1.57 s (slow)
4 KiB <<< . (ext4 /dev/sda2): request=10 time=522.3 ms

--- . (ext4 /dev/sda2) ioping statistics ---
9 requests completed in 6.50 s, 36 KiB read, 1 iops, 5.54 KiB/s
generated 10 requests in 10.7 s, 40 KiB, 0 iops, 3.73 KiB/s
min/avg/max/mdev = 5.48 ms / 722.4 ms / 1.57 s / 522.7 ms


```

references

https://louwrentius.com/understanding-iops-latency-and-storage-performance.html

https://theithollow.com/2013/11/18/disk-latency-concepts/

### throughput

throughput is the `maximum` rate of production or the `maximum` rate at which something can be processed.

### Steps to troubleshooting IO issues

https://bencane.com/2012/08/06/troubleshooting-high-io-wait-in-linux/

### How to solve IO issues

https://scoutapm.com/blog/understanding-disk-i-o-when-should-you-be-worried?utm_source=weibolife.appspot.com

## iostat
