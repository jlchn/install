### login

login as postgres
```
sudo su - postgres
psql
```

login as normal user

```
psql -h localhost  -U user_name db_name
```

### list all database

```
\l
```

### use database

```
\c db_name
```

### find slow sqls

```
select total_time/calls as per_call_ms , calls, rows, query
from pg_stat_statements 
order by total_time/calls desc ;
```

check here for detail: https://www.postgresql.org/docs/9.3/pgstatstatements.html

### reset statistics

```
select pg_stat_statements_reset() # run as super user
```
