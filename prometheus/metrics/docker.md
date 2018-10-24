
### Docker CPU utilization (x%)

> sum (rate (container_cpu_usage_seconds_total{image!="", name=~".+"}[3m])) by (name) * 100

### Docker memory utilization(GB)

> container_memory_usage_bytes{name=~".+"} /1000/1000/1000

### Docker disk utilization (MB)

> (container_fs_usage_bytes{name!=""})/1000/1000

