## WP package downloads
- Download at https://wordpress.org/
    - Alternatively, https://cn.wordpress.org/, for the built-in Chinese language package
- Extract to a proper directory.
    - For me, `~/wordpress-5.9/`
        - File depth check: `~/wordpress-5.9/wp-admin/install.php`
  
## Softwares
- `mysql`
    - `sudo apt-get install mysql mysql-server`
    - Setup a database for wordpress
        - Process omitted in this passage
        - Remember the username, databasename, password
    - notice that password follows `-p` strictly
        - `mysql -u [username] -p[passwd] [-h [ip]] [databasename]`
        - `[ip]`=`127.0.0.1`or`localhost`
```bash
# an example
nqhq@AL1server:~$ sudo mysql
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 10
Server version: 8.0.27-0ubuntu0.20.04.1 (Ubuntu)

Copyright (c) 2000, 2021, Oracle and/or its affiliates.

Oracle is a registered trademark of Oracle Corporation and/or its
affiliates. Other names may be trademarks of their respective
owners.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql> ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'root@mysql';
Query OK, 0 rows affected (0.01 sec)

mysql> FLUSH PRIVILEGES;
Query OK, 0 rows affected (0.00 sec)

mysql> CREATE DATABASE wordpress;
Query OK, 1 row affected (0.02 sec)

nqhq@AL1server:~$ mysql -u root -p[your_own_password] -h 127.0.0.1

mysql> show databases;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| mysql              |
| performance_schema |
| sys                |
| wordpress          |
+--------------------+
5 rows in set (0.06 sec)

mysql> exit
Bye

% to delete database, use
mysql> drop database wordpress;
```
  
- `nginx`
    - `sudo apt-get install nginx`
    - Test if it is installed: `nginx -v`
    - Start nginx service `service nginx start`, or `restart`
  
- `php` series
    - `sudo apt-get install php7.4 php7.4-mysql php7.4-fpm`
    - Start php service `sudo service php7.4-fpm start`, or `restart`
  

## Configurations
- `cd /etc/nginx/sites-available/`
    - `touch [your_name_for_wp_proxy]` (for me, `wp_config`)
        - (better with other names... I don't know its usage no until installation finished.)
    - config file contents
        - The only restriction on choosing Port is potential conflictions with existing services.
```
server {
	listen [port, I suggest 80];
	server_name [ip or domain, for default use _];
	root "[path_to_wordpress_directory]";
	index index.html index.php;

	location ~ \.php$ {
		include snippets/fastcgi-php.conf;

		# With php-fpm (or other unix sockets):
		fastcgi_pass unix:/var/run/php/php7.4-fpm.sock;
		# With php-cgi (or other tcp sockets):
		# fastcgi_pass 127.0.0.1:9000;
	}

	location / {
			try_files $uri $uri/ =404;
	}
}
```
- example
```
server {
	listen 80;
	server_name _;

	root "/home/nqhq/wordpress-5.9/";
	index index.html index.php;

	location ~ \.php$ {
		include snippets/fastcgi-php.conf;

		# With php-fpm (or other unix sockets):
		fastcgi_pass unix:/var/run/php/php7.4-fpm.sock;
		# With php-cgi (or other tcp sockets):
		# fastcgi_pass 127.0.0.1:9000;
	}

	location / {
		try_files $uri $uri/ =404;
	}
}
```
- Soft link to the twin folder
	- `ln -s wp-install-temp /etc/nginx/sites-available/sites-enabled/`
- Remove `default` setting (if there is)
	- `rm /etc/nginx/sites-available/sites-enabled/default`
- Restart `nginx` and `php` service
	- `sudo service nginx restart`
	- `sudo service php7.4-fpm restart`
- Check if services running properly
- `sudo service --status-all`
- Pay attention to `mysql`, `php7.4-fpm`
  

## Installation
- open `/wordpress-5.9/` in browser
    - `localhost:[port]`. (For me, 80, or leave blank)
- Installation guidance should appear as expected.
    - Just follow it.
  
## Install Plugins
- Need FTP credentials when installing plugins
    - see: https://www.wpcom.cn/tutorial/101.html
    - `cat /etc/nginx/nginx.conf | grep user`
        - for me: `www-data`
    - `sudo chown -R www-data:www-data ~/wordpress-5.9/`
    - Then no need for FTP credentials.
    - And `chmod -R 777 [path-to-wp]` (not sure if necessary)
  
## Acknowledgements

Thanks [ZZXin](http://home.pramsin.site/) for his generous and timely help.




