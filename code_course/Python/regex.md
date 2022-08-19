
## Python `regex` module


- `re`模块常数
```python
re.I, re.IGNORECASE  # 忽略大小写
re.M, re.MULTILINE  # 多行模式
re.X, re.VERBOSE  # 详细模式, 忽略空格和#注释
re.S, re.DOTALL  # .匹配所有字符, 包括换行符 (元字符也参与匹配)
re.L, re.LOCALE  # 在正则表达式中使用本地特定的字符集
re.U, re.UNICODE  # 在正则表达式中使用Unicode字符集
```

- `re`模块方法
```Python
re.findall(pattern, string[, flags=0])  # 查找所有匹配, 返回列表 (组->二级列表)
re.search(pattern, string[, flags=0])  # 查找第一个匹配, 返回Match对象, 否则None
re.match(pattern, string[, flags=0])  # 查找字符串的开始, 返回Match对象, 否则None
re.split(pattern, string[, maxsplit=0, flags=0])  # 按匹配分割字符串, 返回列表
re.sub(pattern, repl, string[, count=0, flags=0])  # 替换字符串, 返回字符串
re.subn(pattern, repl, string[, count=0, flags=0])  # 替换字符串, 返回字符串和替换次数
re.escape(string)  # 转义正则表达式字符, 除了\w

"""examples"""
s = 'aaa   bb  c d e fff '
re.split(r'\s+', s)  # ['aaa', 'bb', 'c', 'd', 'e', 'fff', '']
re.split(r'\s+', s.strip())  # ['aaa', 'bb', 'c', 'd', 'e', 'fff']
re.sub(r'\s+', ' ', s.strip())  # 'aaa bb c d e fff'
s.split()  # ['aaa', 'bb', 'c', 'd', 'e', 'fff']
```

- `regexp`正则表达式模块方法
```python
regex.match(pattern[, pos[, endpos]])  # 查找字符串的开始, 返回Match对象, 否则None
regex.search(pattern[, pos[, endpos]])  # 查找第一个匹配, 返回Match对象, 否则None
regex.findall(pattern[, pos[, endpos]])  # 查找所有匹配, 返回列表 (组->二级列表)
regex.split(pattern[, maxsplit[, pos[, endpos]]])  # 按匹配分割字符串, 返回列表
regex.sub(pattern, repl, string[, count[, pos[, endpos]]])  # 替换字符串, 返回字符串
regex.subn(pattern, repl, string[, count[, pos[, endpos]]])  # 替换字符串, 返回字符串和替换次数
```

- `match`对象
```Python
Match.group()  # 匹配的字符串
Match.group(0)  # 匹配的字符串
Match.group(1)  # 第一组匹配的字符串
Match.groups()  # 匹配的所有组的字符串
Match.groupdict()  # 匹配的所有组的字符串, 并以字典形式返回
Match.start()  # 匹配的起始位置
Match.end()  # 匹配的结束位置
Match.span()  # 匹配的起始位置和结束位置
```

```Python
regex = re.compile(r'(?P<a1>\d{1,3})-(?P<a2>\d{2,3})-(?P<a3>\d{4})')
match = regex.search("23-123-2314")
match.group(), match.group(0), match.group(1), match.group(2)
# ('23-123-2314', '23-123-2314', '23', '123')
match.groups()  # ('23', '123', '2314')
match.groupdict()  # {'a1': '23', 'a2': '123', 'a3': '2314'}
```




