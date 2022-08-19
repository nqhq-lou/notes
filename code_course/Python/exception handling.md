---
title: python trouble shooting
tags: [python/exception]
---

## exceptions

```Python
SyntaxError  # 语法错误
NameError  # 变量未定义
TypeError  # 变量类型错误
ZeroDivisionError  # 除数为0
IndexError  # 索引超出范围
KeyError  # 字典中没有这个键
ValueError  # 传递给函数的参数类型不正确, e.g. int(',!!')
AttributeError  # 对象没有这个属性
IOError  # 输入输出错误, e.g. 读写不存在的文件
RuntimeError  # 运行时错误
AssertionError  # 断言错误
```

### raise exception explicitly

```python
raise Exception[args, traceback]
```
- `args`: tuple
- 
- `traceback`: traceback object

### exception traceback

```Python
import sys
  
try:
    assert 1 == 2, "1 is not equal to 2!"
except:
    errors = sys.exc_info()
    print(errors)  # 返回为tuple
    # (<class 'AssertionError'>, AssertionError('1 is not equal to 2!'), <traceback object at 0x00000221A03CB6C0>)
```


## common strategy

```python
# try statement
try:
	statement
# for one kind of error
except name1 as err:
	statement
# for several kinds of error
except (name2, name3) as err:
	statement
# doesn't belong to err above
except:
	print(sys.exc_info()[0])  # pring the exception type
# if no exception
else:
	statement
# whatever if there is any exception
finally:
	statement
```

