---
title: ceph usage
tags: []
---


## general information

- [general information](https://docs.amazonaws.cn/cli/latest/userguide/cli-chap-welcome.html)


## aws cli v2 install

- see [user guide for v2](https://docs.aws.amazon.com/cli/latest/userguide/getting-started-install.html)
- [python api](https://pypi.org/project/awscliv2/)

## basic usage for v2

- see [集群用户手册_awscli进阶](http://sdoc.pjlab.org.cn:10099/docs/Petrel-OSS/02-Petrel-OSS%E8%BF%9B%E9%98%B6%E8%AF%B4%E6%98%8E/01-awscli%E8%BF%9B%E9%98%B6.html)

```bash
# 自动创建桶中的存储位置
aws s3 cp file_name s3://bucket-name/path-name/file_name1
# 复制对象
aws s3 cp <LocalPath> <S3Uri> | <S3Uri> <LocalPath> | <S3Uri> <S3Uri> [--options]

LocalPath -- 本地文件/文件夹的路径；
S3Uri -- Petrel-OSS的桶路径，格式为s3://bucket-name/(file-name)；
可选参数(--options)：
--recursive：使命令处理特定目录或前缀中的所有文件或对象；（注意，如果是文件夹-文件夹的cp，必须带该参数，不然报错403）
--include <value>：使命令处理符合特定样式的文件或对象；
--exclude <value>：使命令忽略符合特定样式的文件或对象；
--no-sign-request：匿名访问。需要设置相应的桶策略以支持匿名访问；
--no-follow-symlinks：不上传软连接。默认是上传的。



```



## aws

```bash
(base) [zhonghansen@SH-IDCA1404-10-140-54-88 nwchem]$ aws s3 ls --endpoint-url=10.140.2.204  
  
Bad value for --endpoint-url "10.140.2.204": scheme is missing.  Must be of the form http://<hostname>/ or https://<hostname>/  
(base) [zhonghansen@SH-IDCA1404-10-140-54-88 nwchem]$ aws s3 ls --endpoint-url=http://10.140.2.204  
2022-11-02 15:27:57 vxc-dataset  
(base) [zhonghansen@SH-IDCA1404-10-140-54-88 nwchem]$ aws s3 --endpoint-url=10.140.2.204 ls s3://vxc-dataset  
  
Bad value for --endpoint-url "10.140.2.204": scheme is missing.  Must be of the form http://<hostname>/ or https://<hostname>/  
(base) [zhonghansen@SH-IDCA1404-10-140-54-88 nwchem]$ aws s3 --endpoint-url=http://10.140.2.204 ls s3://vxc-dataset  
2022-11-02 16:48:55 2032362325 Mathematica_13.1.0_LINUX_CN.sh  
(base) [zhonghansen@SH-IDCA1404-10-140-54-88 nwchem]$ aws s3 --endpoint-url=http://10.140.2.204 cp s3://vxc-dataset/Mathematica_13.1.0_LINUX_CN.sh Mathematica_13.1.0_LINUX_CN.sh  
download: s3://vxc-dataset/Mathematica_13.1.0_LINUX_CN.sh to ./Mathematica_13.1.0_LINUX_CN.sh  
(base) [zhonghansen@SH-IDCA1404-10-140-54-88 nwchem]$ s  
bash: s: command not found...  
(base) [zhonghansen@SH-IDCA1404-10-140-54-88 nwchem]$ ls  
Mathematica_13.1.0_LINUX_CN.sh  n2.nw  
(base) [zhonghansen@SH-IDCA1404-10-140-54-88 nwchem]$
```

```bash
aws s3 ls --endpoint-url=http://10.140.2.204

aws s3 --endpoint-url=http://10.140.2.204 cp s3://vxc-dataset/Mathematica_13.1.0_LINUX_CN.sh Mathematica_13.1.0_LINUX_CN.sh

```


## 