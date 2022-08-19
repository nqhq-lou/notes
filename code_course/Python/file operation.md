---
title: python file operation
tags: [python/file_op]
---


## `os` module

- `os.popen("shell command")`
	- `os.popen("shell command").read()` 返回一个字符串
	- `os.popen("shell command").readlines()` 返回列表

```Python
os.chdir("path")
os.mkdir("dirname"[, mode=0o777])  # 八进制
os.makedirs("pathto/dirname"[, mode=0o777])  # 创建多级目录
os.rmdir("dirname")  # 删除空目录
os.removedirs("pathto/dirname")  # 删除多级目录
os.rename("oldname", "newname")  # 重命名
os.listdir("path")  # 返回目录下所有文件和目录名
os.walk("path")  # 返回目录下所有文件和目录名, 包括子目录
os.sep  # 当前操作系统的路径分隔符
```
  
- `walk()`例子
```Python
import os
path = "path/to/dir"
if not os.path.isdir(path):
    exit()
list_dirs = os.walk(path)
for root, dirs, files in list_dirs:
    for d in dirs:
        print(os.path.join(root, d))
    for f in files:
        print(os.path.join(root, f))
```
  
- `shutil`: shell utility
```Python
shutil.copyfile("oldname", "newname")  # 复制文件
shutil.copytree("oldname", "newname")  # 复制目录
```




## 文件对象
- `open(filename, mode='r', buffering=-1, encoding=None)`
	- mode 读写模式
		- `r`读, `w`写, `a`追加, `b`二进制模式, `+`读写模式
		    - `a`: 若文件不存在则创建文件, 否则文件指针到文件尾, 只能写
		    - `a+`: 若文件不存在则创建文件, 否则文件指针到文件尾, 可读写
		- 默认为`r`
	- buffering 缓存大小
		- 0 -> 不缓存, 大于0 -> 指定缓冲区大小, 小于0 -> 系统默认大小
		- 默认为-1
	- encoding 编码格式
		- 默认为系统默认编码
		- e.g. `'UTF-8'`
  
- 文件对象属性
```Python
f.closed  # 关闭为True, 未关闭为False
f.encoding  # 编码格式
f.mode  # 读写模式
f.name  # 文件名
```
  
- 文件对象方法
```Python
f.read(size=-1)  # 读取文件内容, 返回字符串
f.readline()  # 读取一行, 返回字符串 (包含最后的换行符)
f.readlines()  # 读取所有行, 返回列表 (每个包含最后的换行符)
  
f.write(str)  # 写入字符串
f.writelines(list[str])  # 写入字符串列表
  
f.flush()  # 将缓冲区内容写入文件, 不关闭文件
f.close()  # 将缓冲区内容写入文件, 关闭文件, 释放文件对象
f.tell()  # 返回文件指针位置
f.truncate(size=None)  # 删除从指针位置到文件尾的内容. 如果指定size, 则在size处截断
f.seek(offset[, whence=0])  # 改变文件指针位置(相对于whence)
# whence: 0->从头开始, 1->从当前位置开始, 2->从文件尾开始
f.isatty()  # 是否是一个终端设备
```



## context management `with`

- 一种方便简单资源控制的方法
```Python
with context_expr [as obj, context_expr2 [as obj2, ...]]:
    with_block
```

```Python
with open(filename, 'r') as handler:
    lines = handler.readlines()
print(lines)
```

- 同时处理多个文件
```Python
with open(fname1, 'r') as fr, open(fname2, 'w') as fw:
    for line in fr:  # fr.readlines()
        fw.write(line)
    # fw.write(fr.read())
```


## file op examples

- `print(str, file=sys.stdout)`
```Python
with open("sample.txt", 'w') as f:
    print("Hello world!", file=f)  # 结尾会换行的
    print("Python", file=f)
```
  
- 读取文件, 显示所有行
```Python
with open("sample.txt", 'r') as f:
    while True:
        line = f.readline()
        if line == "":  # 最后一行了
            break
        print(line, end='')
        # print(line.strip())
    # print(f.read())  # 直接输出就没问题
```



## binary file pickling

```Python
with open("pickle_dump.pkl", 'wb') as f:
    try:
        pickle.dump(4, f)  # 后续有多少对象
        pickle.dump([[1,2,3],[3,4,5],[4,5,6]], f)
        pickle.dump("good name!!!", f)
        pickle.dump({"a": 1, "b":2}, f)
        pickle.dump(4231.125342, f)
    except:
        print("error when writing")
  
with open("pickle_dump.pkl", 'rb') as f:
    n = pickle.load(f)  # 读入对象数量, 对应上面的4
    for i in range(n):  # EOFError: Ran out of input
        x = pickle.load(f)
        print(x)
```

