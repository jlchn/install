
### self signed certificate

```
openssl req -x509 -newkey rsa:4096 -nodes -keyout key-no-pasword.pem -out cert.pem -days 365
```

### cannot ssh to localhost

sudo apt-get install openssh-server