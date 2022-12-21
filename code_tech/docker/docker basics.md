---
title: docker basics
tags: [Linux/docker]
---

## quick setup

- This setup a PyTorch container
```bash
# init container, port_inside corresponds to ssh port
docker run -it -v [path2container]:/work -w /work --name [containername] --gpus all --ipc=host --ulimit memlock=-1 --ulimit stack=67108864 -p [port_outside]:[port_inside] nvcr.io/nvidia/pytorch:22.11-py3

# create user [with root]
useradd -d [homepath] -m [username] -s /bin/bash
passwd louzekun  # just set passwd

# add user to sudoers
vim /etc/sudoers
# add after: # User privilege specification
## [username] ALL=(ALL) NOPASSWD: ALL
# save file

# (re)install openssh-server and restart service
apt-get remove openssh-server
apt-get install openssh-server
vim /etc/ssh/sshd_config
# uncomment the below 2 settings
## Port 22  # this should corresponds to [port_inside] above
## PasswordAuthentication yes
# restart the service
sudo service ssh --full-restart
```
- then could connect externally
	- port is `[port_outside]`
	- ip is the host's ip


- copy docker env variables to container
```bash
OLDIFS=$IFS  
IFS=  
export $(sudo xargs -0 -L1 -a /proc/1/environ)  
IFS=$OLDIFS  
export HOME=/home/zhonghansen
```











