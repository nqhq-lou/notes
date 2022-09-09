---
title: pandas concatenate
tags: [python/module/pandas]
---


## 关系型连接

### 连接的基本概念
- 使用merge连接`df1.merge(df2, on=..., how=...)`
- `on` col的组合对象, 或者称为键
- `how` 组合方式
![[pandas_concat_fig1.png|600]]
- 如果出现相同的`on`对应的col, 按照外积的方式进行merge
![[pandas_concat_fig2.png|600]]

 
### 值连接
- 第一张图的左连接见代码, 用Name列连接
```python
df1 = pd.DataFrame({'Name':['San Zhang','Si Li'], 'Age':[20,30]})
df2 = pd.DataFrame({'Name':['Si Li','Wu Wang'], 'Gender':['F','M']})
df1.merge(df2, on='Name', how='left')
```
- 如果两个表中想要连接的列不具备相同的列名，可以通过`left_on`和`right_on`指定
```python
df1 = pd.DataFrame({'df1_name':['San Zhang','Si Li'], 'Age':[20,30]})
df2 = pd.DataFrame({'df2_name':['Si Li','Wu Wang'], 'Gender':['F','M']})
df1.merge(df2, left_on='df1_name', right_on='df2_name', how='outer')
```
- 合并的数据出现重复, 使用`suffixes`进行区分
	- 重复的列将会加入后缀进行区分, 出现同一位置对应多个数值
```python
df1 = pd.DataFrame({'Name':['San Zhang'],'Grade':[70],'rank':[2]})
df2 = pd.DataFrame({'Name':['San Zhang'],'Grade':[80],'rank':[1]})
df1.merge(df2, on='Name', how='left', suffixes=['_Chinese','_Math'])
>> 
        Name Grade_Chinese rank_Chinese Grade_Math rank_Math
0  San Zhang            70            2         80         1
```
- `on`指定多列, 可以避免自动进行外积
```python
# 来自两个班级的同名人, 和合并其余的信息
df1 = pd.DataFrame({'Name':['San Zhang', 'San Zhang'],
                    'Age':[20, 21],
                    'Class':['one', 'two']})
df2 = pd.DataFrame({'Name':['San Zhang', 'San Zhang'],
                    'Gender':['F', 'M'],
                    'Class':['two', 'one']})
df1.merge(df2, on=['Name', 'Class'], how='left') # 同时指定名称和班级, 防止因重复出现外积合并
```


### 索引连接
- 函数`join`, 自动将索引纳入`on`键, 此外`on`选项用来传入其他用于合并的键
	- 能够支持多级索引的merge
- 除了必须的`on`和`how`之外，可以对重复的列指定左右后缀`lsuffix`和`rsuffix`。其中，`on`参数指索引名，单层索引时省略参数表示按照当前索引连接
```python
df1 = pd.DataFrame({'Grade':[70,100]},
				   index=pd.Series(['San Zhang','Si Li'],
				   name='Name'))
df2 = pd.DataFrame({'Grade':[80,90]},
				   index=pd.Series(['San Zhang','Si Li'],
				   name='Name'))
df1.join(df2, how='left', lsuffix='_Chinese', rsuffix='_Math')
>> 
          Grade_Chinese Grade_Math
Name
San Zhang            70         80
Si Li               100         90
```




## 方向连接

### concat
- 并不关心合并中的键, 只是希望把表拼起来
- 参数 `axis` 拼接方向,  `join` 连接形式, `keys` 新表中指示来自于哪一张旧表的名字
```python
df1 = pd.DataFrame({'Name':['San Zhang','Si Li'], 'Age':[20,30]})
df2 = pd.DataFrame({'Name':['Wu Wang'], 'Age':[40]})
pd.concat([df1, df2])  # 纵向拼接

df2 = pd.DataFrame({'Grade':[80, 90]})
df3 = pd.DataFrame({'Gender':['M', 'F']})
pd.concat([df1, df2, df3], axis=1)  # 横向拼接
```
- 虽然`concat`是合并函数, 但是仍然按照索引进行合并
	- `join`参数指定inner或者outer, 合并重复的索引 / 保留非重复索引
```python
df2 = pd.DataFrame({'Name':['Wu Wang'], 'Gender':['M']})
pd.concat([df1, df2], join="outer")  # 保留所有索引
df2 = pd.DataFrame({'Grade':[80, 90]}, index=[1, 2])
pd.concat([df1, df2], 1)  # 横向合并, 注意index, 所以有三行
pd.concat([df1, df2], axis=1, join='inner')  # 因为index, 所以只有一行
```

- 因此, 需要多个表直接方向合并, 特别是横向合并, 可以先使用`reset_index`恢复默认的正数索引, 再进行合并
- `keys`用来标记来源的表
```python
df1 = pd.DataFrame({'Name':['San Zhang','Si Li'], 'Age':[20,21]})
df2 = pd.DataFrame({'Name':['Wu Wang'],'Age':[21]})
pd.concat([df1, df2], keys=['one', 'two'])
```
![[pandas_concat_fig3.png]]

### 序列和表的合并




**0909: 嘤嘤嘤没写完, 之后两天补上**



## 类连接操作

### 比较



### 组合









## Ex



### Ex1