

## apt

- `sudo apt-get install mysql`

  

## first login

  

```bash

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

  

nqhq@AL1server:~$ mysql -u root -proot@mysql -h 127.0.0.1

  

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

  

# to delete database, use

mysql> drop database wordpress;

  
  

```

  

- notice that password follows `-p` strictly

    - `mysql -u [username] -p[passwd] [-h [ip]] [databasename]`

    - `[ip]`=`127.0.0.1`or`localhost`