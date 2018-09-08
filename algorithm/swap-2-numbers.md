swap 2 number without using temp variable.md

1. overflow risk

``` java

int a =20, b=10;

a=a+b;

b=a-b;

a=a-b;

```

2. overflow riks

``` java

int a =20, b=10;

a=a*b;

b=a/b;

a=a/b;

```

3. right way

``` java

int a =20, b=10;

a=a^b;

b=a^b;

a=a^b;

```



