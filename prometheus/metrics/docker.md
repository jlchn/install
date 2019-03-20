
### The total CPU time taken by docker since started  
```
 container_cpu_usage_seconds_total{image!="", name=~".+"}
```
### The average CPU time taken per second in the last 1 minute by docker 
```
 rate (container_cpu_usage_seconds_total{image!="", name=~".+"}[1m])
```
### Docker memory utilization(GB)

```
 container_memory_usage_bytes{name=~".+"} /1000/1000/1000
```
### Docker disk utilization (MB)

```
 (container_fs_usage_bytes{name!=""})/1000/1000
```

### Bytes transmitted over the network by the container per second in the last minute

```
 rate(container_network_transmit_bytes_total[1m])
```
### Bytes received over the network by the container per second in the last minute
