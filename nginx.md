
# Install Nginx

### ubuntu

```

sudo apt-get update

sudo apt-get install nginx

```
### https configuration

```
sudo mkdir /etc/nginx/ssl

sudo openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/nginx/ssl/nginx.key -out /etc/nginx/ssl/nginx.crt

sudo vim /etc/nginx/sites-available/default

```

paste all contents below in to `/etc/nginx/sites-available/default`

```

server {

        server_name demo.com localhost;

        client_max_body_size 2000M;

        listen 443 ssl;

        ssl_certificate /etc/nginx/ssl/nginx.crt;

        ssl_certificate_key /etc/nginx/ssl/nginx.key;

        gzip  on;

        gzip_http_version 1.1;

        gzip_vary on;

        gzip_comp_level 6;

        gzip_proxied any;

        gzip_types text/plain text/html text/css application/json application/x-javascript text/xml application/xml application/xml+rss text/javascript application/javascript text/x-js;

        gzip_buffers 16 8k;

        gzip_disable "MSIE [1-6]\.(?!.*SV1)";



       location / {

                proxy_pass http://172.26.131.134:9440/;

                proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;

                proxy_set_header X-Request-URI $request_uri;

         }

       location /app1/ {

                proxy_pass http://localhost:9444/;

                proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;

                proxy_set_header X-Request-URI $request_uri;

       }

       location /app2/ {

                proxy_pass http://localhost:2017/;

                proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;

                proxy_set_header X-Request-URI $request_uri;

       }

}

```


### Resart Nginx and Check Configuration

```

sudo service nginx restart

```

visit https://localhost to see if the configuration applicable.