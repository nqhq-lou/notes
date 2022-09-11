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
- 追加序列到行末或者列末, 使用`append`和`assign`方法
- `append`用于添加新行, 原先Series的`name`作为新行的index
```python
s = pd.Series(['Wu Wang', 21], index = df1.columns)
df1.append(s, ignore_index=True)  # 新行的index是顺序的2
s = pd.Series(['Wu Wang', 21], index = df1.columns, name=4)
df1.append(s, ignore_index=False)  # 新行的index是4
```
- `assign`用来添加新的列, 返回修改过之后的临时副本, 并不会改动原来的表
	- 可以直接添加数值, 也可以根据函数添加列
- 而`df['new_col']=...`的形式可以等价地添加新列, 但是会修改原表
```python
s = pd.Series([80,90])
df1.assign(Grade=s)  # 新的列名称为Grade
df1.assign(Grade=lambda x: x.Age*10 - 5)  # 也可以根据函数进行添加列
```



## 类连接操作

- 目的在于对两个表进行联合操作

### 比较
- `compare`比较两个表或者序列的不同之处
	- `keep_shape`是否完整显示所有元素情况
```python
df1 = pd.DataFrame({'Name':['San Zhang', 'Si Li', 'Wu Wang'],
                    'Age':[20, 21 ,21],
                    'Class':['one', 'two', 'three']})
df2 = pd.DataFrame({'Name':['San Zhang', 'Li Si', 'Wu Wang'],
                    'Age':[20, 21 ,21],
                    'Class':['one', 'two', 'Three']})
df1.compare(df2)
>> 
   Name       Class
   self other  self other
1 Si Li Li Si   NaN   NaN
2   NaN   NaN three Three
# 因为第0行没有数值, 所以没有第0行的显示
# 第一二行分别有不一样的地方, 所以进行了比较

df1.compare(df2, keep_shape=True)
>> 
   Name         Age       Class
   self  other self other  self other
0   NaN    NaN  NaN   NaN   NaN   NaN
1 Si Li  Li Si  NaN   NaN   NaN   NaN
2   NaN    NaN  NaN   NaN three Three
```


### 组合
- `combine`函数让两张表按照一定的规则进行组合, 在进行规则比较时会自动进行列索引的对齐
- 对于传入的函数而言, 每一次操作中输入的参数是来自两个表的同名`Series`, 依次传入的列是两个表列名的并集
	- 例如下面这个例子会依次传入`A,B,C,D`四组序列, 每组为左右表的两个序列
	- 进行`A`列比较的时候, `s2`指代的就是一个全空的序列, 因为它在被调用的表中并不存在
	- 并且来自第一个表的序列索引会被`reindex`成两个索引的并集
	- `overwrite=False` 保留被调用表中未出现在传入参数表中的列, 而不是设置为NaN
```python
def choose_min(s1, s2):  # 会一列一列传入这个函数中
    # s2 = s2.reindex_like(s1)  # 这一步不是必须的
    # print(s1.index, s1.name, s1.to_list())  # 可以看出来对两个表都进行了扩充
    # print(s2.index, s2.name, s2.to_list())
    res = s1.where(s1<s2, s2)
    res = res.mask(s1.isna()) # isna表示是否为缺失值，返回布尔序列
    return res

df1 = pd.DataFrame({'A':[1,2], 'B':[3,4], 'C':[5,6]})
df2 = pd.DataFrame({'B':[5,6], 'C':[7,8], 'D':[9,10]}, index=[1,2])
df1.combine(df2, choose_min)
>> 
    A   B   C   D
0 NaN NaN NaN NaN
1 NaN 4.0 6.0 NaN
2 NaN NaN NaN NaN

df1.combine(df2, choose_min, overwrite=False)  # 保留被调用表中未出现传入参数的列
>> 
    A   B   C   D
0 1.0 NaN NaN NaN
1 2.0 4.0 6.0 NaN
2 NaN NaN NaN NaN
```


## HW

### Ex1
```python
# 生成日期
date = pd.date_range('20200412', '20201116').to_series()
date = date.dt.month.astype('string').str.zfill(2) +'-'+ date.dt.day.astype('string').str.zfill(2) +'-'+ '2020'
date = date.tolist()
# 获得List[pandas.DataFrame]
df_list = [
	pd.read_csv(f'../data/us_report/{d}.csv').loc[
		lambda x: x['Province_State']=='New York',
		['Confirmed', 'Deaths', 'Recovered', 'Active']
	] for d in date]
# 进行拼接
df = pd.concat(df_list)  # 拼接
df.index = date  # 之后指定index
df.head()
```

### Ex2

```python
import pandas
import numpy
  
def join(df1:pandas.DataFrame, df2:pandas.DataFrame, how:str):
    """假设两列表无公共列, 实现left right inner outer的拼接"""
  
    def _left():
        df1_temp = df1.copy().sort_index()
        df2_temp = df2.copy().loc[index["common"]]
        df2_nan = pandas.DataFrame([[numpy.nan]*len(df2_temp.columns)]*len(index["left"]), index=index["left"], columns=df2_temp.columns)
        df2_temp = pandas.concat([df2_temp, df2_nan], axis=0).sort_index()
        return pandas.concat([df1_temp, df2_temp], axis=1)
  
    def _right():
        df2_temp = df2.copy().sort_index()
        df1_temp = df1.copy().loc[index["common"]]
        df1_nan = pandas.DataFrame([[numpy.nan]*len(df1_temp.columns)]*len(index["right"]), index=index["right"], columns=df1_temp.columns)
        df1_temp = pandas.concat([df1_temp, df1_nan], axis=0).sort_index()
        return pandas.concat([df1_temp, df2_temp], axis=1)
  
    def _inner():
        df2_temp = df2.copy().loc[index["common"]]
        df1_temp = df1.copy().loc[index["common"]]
        return pandas.concat([df1_temp, df2_temp], axis=1)
  
    def _outer():
        df1_temp = df1.copy()
        df1_nan = pandas.DataFrame([[numpy.nan]*len(df1_temp.columns)]*len(index["right"]), index=index["right"], columns=df1_temp.columns)
        df1_temp = pandas.concat([df1_temp, df1_nan], axis=0).sort_index()
        df2_temp = df2.copy()
        df2_nan = pandas.DataFrame([[numpy.nan]*len(df2_temp.columns)]*len(index["left"]), index=index["left"], columns=df2_temp.columns)
        df2_temp = pandas.concat([df2_temp, df2_nan], axis=0).sort_index()
        return pandas.concat([df1_temp, df2_temp], axis=1)
  
    index = {"left": df1.index.difference(df2.index),  # only left
             "common": df1.index.intersection(df2.index),  # common intersection
             "right": df2.index.difference(df1.index)}  # only right
    if how == "left":
        return _left()
    elif how == "right":
        return _right()
    elif how == "inner":
        return _inner()
    elif how == "outer":
        return _outer()
    else:
        raise Exception(f"how must be either left, right, inner, outer, not {how}")

df1 = pd.DataFrame({'Age':[20, 21], 'rank':[1, 2]}, index=[0,1])
df2 = pd.DataFrame({'Gender':['F', 'M'], 'Class':['two', 'one']}, index=[1,2])
  
print(join(df1, df2, how="left"))
print(join(df1, df2, how="right"))
print(join(df1, df2, how="inner"))
print(join(df1, df2, how="outer"))

>> 
  Age rank Gender Class
0  20    1    NaN   NaN
1  21    2      F   two
   Age rank Gender Class
1 21.0  2.0      F   two
2  NaN  NaN      M   one
  Age rank Gender Class
1  21    2     F    two
   Age rank Gender Class
0 20.0  1.0    NaN   NaN
1 21.0  2.0      F   two
2  NaN  NaN      M   one
```



