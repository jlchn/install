
### identifier in mysql: 
database table column index alias

### login
```
mysql [-h 10.132.141.2] -u root -p
```

### useful sqls
```
use db_name;
 
create table t1
(
 id int not null primary key,
 name char(50) not null
);

show tables;

describe t1;

insert into t1(id ,name) values(1,'name1'),(2,'name2');
# limits
select * from t1 limit 1,3;
```

### execute sql script from document
```
mysql -u root -p db_name < /var/sql.sql
```
