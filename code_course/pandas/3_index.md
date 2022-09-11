---
title: pandas index
tags: [python/module/pandas, data_processing]
---


```python
import pandas as pd

# 导入数据集
df = pd.read_csv('../data/learn_pandas.csv', usecols = ['School', 'Grade', 'Name', 'Gender', 'Weight', 'Transfer'])
```

## indexer

- index可以重复!

### DataFrame column index
- 通过`[colname]`实现, 可以是单个str, 也可以是多个colname组成的list
- 如果colname中没有空格, 那么可以直接用`.colname`进行列索引
```python
df['Name']  # Series
df.Name  # Series
df[['Gender', 'Name']]  # DataFrame
```



### Series row index

#### Series indexed by string
- 单个值返回scalar, 多个值返回Series
- 可以进行slice, 因为index是有序 (前提是index唯一, 或者index为有序排列)
	- 切片包含右端点
```python
s = pd.Series([1,2,3,4,5,6], index=['a', 'b', 'a', 'a', 'a', 'c'])

s['a']
>> 
a    1
a    3
a    4
a    5
dtyep: int64

s['b']
>> 
2

s[['c', 'b']]
>> 
c    6
b    2
dtype: 64

s['c': 'b': -2]  # 需要注意索引的方向是正确的
>> 
b    2
a    4
c    6
dtype: int64

s.sort_index()['a': 'b']
```

#### Series indexed by int
- 如果不指定索引, 那么就会自动生成从0开始的整数索引
- 可以使用`[int]`或者`[list[int]]`进行索引
	- 切片, 对应的是**索引位置**的值
```python
s = pd.Series(['a', 'b', 'c', 'd', 'e', 'f'], index=[1, 3, 1, 2, 5, 4])
s[1]
>> 
1    a
1    c
dtype: object

s[[2,3]]
>> 
2    d
3    b
dtype: object

s[1:-1:2]  # 这个就是按位置的切片, 而不是关于index的索引
>> 
3    b
2    d
dtype: object
```

- **请不要把index设置为浮点数或者混合类型**, 否则可能会有奇怪的报错


### `loc` indexer (element-based)
- 一般形式: `.loc[*[, *]]`, 第一个为行, 第二个为列
- `*`有五种合法内容, 单个元素, 元素列表, 元素切片, 布尔列表, 函数
```python
df_demo = df.set_index('Name')  # 设置'Name'列为index
df_demo.head()
```
| Name           | School                        | Grade     | Gender | Weight | Transfer |
|:-------------- |:----------------------------- |:--------- |:------ | ------:|:-------- |
| Gaopeng Yang   | Shanghai Jiao Tong University | Freshman  | Female |     46 | N        |
| Changqiang You | Peking University             | Freshman  | Male   |     70 | N        |
| Mei Sun        | Shanghai Jiao Tong University | Senior    | Male   |     89 | N        |
| Xiaojuan Sun   | Fudan University              | Sophomore | Female |     41 | N        |
| Gaojuan You    | Fudan University              | Sophomore | Male   |     74 | N        |

- 单个元素, 直接取出对应行或列
	- 如果元素在index中重复, 则结果为DataFrame, 否则为Series
```python
df_demo.loc['Qiang Sun']  # 不唯一的名字, 作为索引出现过多次
df_demo.loc['Quan Zhao']  # 唯一的名字
df_demo.loc['Qiang Sun', 'School']  # 返回Series
df_demo.loc['Quan Zhao', 'School'] # 返回单个元素
```

- 元素列表
```python
df_demo.loc[['Qiang Sun','Quan Zhao'], ['School','Gender']]
```

- 切片
```python
df_demo.loc['Gaojuan You':'Gaoqiang Qian', 'School':'Gender':2]

df_loc_slice_demo = df_demo.copy()
df_loc_slice_demo.index = range(df_demo.shape[0],0,-1)  # index为 ..., 2, 1, 0
df_loc_slice_demo.loc[5:3]  # 有结果, 因为index就是反着来的, 相当于 [5:3:1]
df_loc_slice_demo.loc[3:5] # 没有返回，说明不是整数位置切片
df_loc_slice_demo.loc[3:5:-1] # 有结果, 因为写上了-1
```

- bool列表
	- true会被选中, false会被删除
- 对于符合条件, 可以使用bool运算实现
```python
df_demo.loc[df_demo.Weight>70].head()  # 选出体重大于70的行
df_demo.loc[df_demo.Grade.isin(['Freshman', 'Senior'])].head()  # 选出字符串限制下的行

condition_1_1 = df_demo.School == 'Fudan University'
condition_1_2 = df_demo.Grade == 'Senior'
condition_1_3 = df_demo.Weight > 70
condition_1 = condition_1_1 & condition_1_2 & condition_1_3  # 第一个组合条件
condition_2_1 = df_demo.School == 'Peking University'
condition_2_2 = df_demo.Grade == 'Senior'
condition_2_3 = df_demo.Weight > 80
condition_2 = condition_2_1 & (~condition_2_2) & condition_2_3  # 第二个组合条件
df_demo.loc[condition_1 | condition_2]  # 返回DataFrame
```

- 函数
```python
df_demo.loc[lambda x:'Quan Zhao', lambda x:'Gender']  # 选择行列, 有返回结果

df_demo.loc[lambda x: slice('Gaojuan You', 'Gaoqiang Qian')]  # 选择多行slice, 注意包装

def condition(x):
    condition_1_1 = x.School == 'Fudan University'
    condition_1_2 = x.Grade == 'Senior'
    condition_1_3 = x.Weight > 70
    condition_1 = condition_1_1 & condition_1_2 & condition_1_3
    condition_2_1 = x.School == 'Peking University'
    condition_2_2 = x.Grade == 'Senior'
    condition_2_3 = x.Weight > 80
    condition_2 = condition_2_1 & (~condition_2_2) & condition_2_3
    result = condition_1 | condition_2
df_demo.loc[condition]  # 有返回结果
```

- `Series`的`.loc()`与DataFrame完全一致

- `.select_dtypes(include=scalar|sequence, exclude=scalar|sequence)`方法
	- 类型包括: `number, object, datetime, timedelta, category, datetimetz`
	- 详见docstring

- **不要使用链式表达式**, 不然难以分清楚复制的具体情况
	- 将会报错: `SettingWithCopyWarning`
	- 应当使用`.copy()`方法


### `iloc` indexer (position based)
- `iloc` -> integer location
- 一般形式: `.iloc[*[, *]]`, 第一个为行, 第二个为列
- `*`有五种合法内容: 整数, 整数列表, 整数切片, bool列表, 函数

```python
df_demo.iloc[1, 1]  # 第一行第一列
df_demo.iloc[[0, 1], [0, 1]]  # 前两行前两列
df_demo.iloc[1:4, 2:4]  # 切片不包含结束端点
df_demo.iloc[lambda x: slice(1, 4)] # 传入切片为返回值的函数, 不包含结束端点
df_demo.iloc[(df_demo.Weight>80).values]  # 布尔的.value, 实际上是np.ndarray
```

- Series也可以iloc
```python
df_demo.School.iloc[1]  # 返回scalar
df_demo.School.iloc[1:5:2]  # 不包括结束的index 5
```



### `query` method
- 用字符串的方式传达查询表达式
	- 注意写多行查询的格式
	- 可以使用`or, and, or, in, not in`逻辑词
	- `==` <=> `in`, `!=` <=> `not in`, 
- 引用外部变量, 使用@
```python
df.query('((School == "Fudan University")&'
         ' (Grade == "Senior")&'
         ' (Weight > 70))|'
         '((School == "Peking University")&'
         ' (Grade != "Senior")&'
         ' (Weight > 80))')

df.query('''((School == "Fudan University")&(Grade == "Senior")&(Weight > 70)) |'''
         '''((School == "Peking University")&(Grade != "Senior")&(Weight > 80))''')

df.query('Weight > Weight.mean()')  # 大于平均值的情况
df.query('(Grade not in ["Freshman", "Sophomore"]) and (Gender == "Male")')  # 逻辑词

low, high =70, 80  # 引用外部变量
df.query('(Weight >= @low) & (Weight <= @high)')
df.query(f'(Weight >= {low}) & (Weight <= {high})')  # f-string 相同效果
```


### random sampler
- 基于`.sample()`方法
	- `n`抽样数量, `axis`抽样方向, `frac`抽样比例
	- `replace`是否放回
	- `weights`每个样本概率
```python
df_sample = pd.DataFrame({'id': list('abcde'), 'value': [1, 2, 3, 4, 90]})
df_sample.sample(3, replace = True, weights = df_sample.value)  # 最后一个肯定抽的多
```



## 多级索引

### 多级索引&表的结构
```python
np.random.seed(0)
multi_index = pd.MultiIndex.from_product([list('ABCD'), df.Gender.unique()], names=('School', 'Gender'))
multi_column = pd.MultiIndex.from_product([['Height', 'Weight'], df.Grade.unique()], names=('Indicator', 'Grade'))
df_multi = pd.DataFrame(
						np.c_[(np.random.randn(8,4)*5 + 163).tolist(),
							(np.random.randn(8,4)*5 + 65).tolist()],
                        index = multi_index, columns = multi_column).round(1)

df_multi
```
|                 |   ('Height', 'Freshman') |   ('Height', 'Senior') |   ('Height', 'Sophomore') |   ('Height', 'Junior') |   ('Weight', 'Freshman') |   ('Weight', 'Senior') |   ('Weight', 'Sophomore') |   ('Weight', 'Junior') |
|:----------------|-------------------------:|-----------------------:|--------------------------:|-----------------------:|-------------------------:|-----------------------:|--------------------------:|-----------------------:|
| ('A', 'Female') |                    171.8 |                  165   |                     167.9 |                  174.2 |                     60.6 |                   55.1 |                      63.3 |                   65.8 |
| ('A', 'Male')   |                    172.3 |                  158.1 |                     167.8 |                  162.2 |                     71.2 |                   71   |                      63.1 |                   63.5 |
| ('B', 'Female') |                    162.5 |                  165.1 |                     163.7 |                  170.3 |                     59.8 |                   57.9 |                      56.5 |                   74.8 |
| ('B', 'Male')   |                    166.8 |                  163.6 |                     165.2 |                  164.7 |                     62.5 |                   62.8 |                      58.7 |                   68.9 |
| ('C', 'Female') |                    170.5 |                  162   |                     164.6 |                  158.7 |                     56.9 |                   63.9 |                      60.5 |                   66.9 |
| ('C', 'Male')   |                    150.2 |                  166.3 |                     167.3 |                  159.3 |                     62.4 |                   59.1 |                      64.9 |                   67.1 |
| ('D', 'Female') |                    174.3 |                  155.7 |                     163.2 |                  162.1 |                     65.3 |                   66.5 |                      61.8 |                   63.2 |
| ('D', 'Male')   |                    170.7 |                  170.3 |                     163.8 |                  164.9 |                     61.6 |                   63.2 |                      60.9 |                   56.4 |
![[pandas_index_table1.png]]
- 多层表中, 表的col和index将会分层
	- 注意, 此时col和index已经不是scalar, 而是tuple
	- 外层连续出现相同的值时，第一次之后出现的会被隐藏显示，使结果的可读性增强
	- 如果想得到某一层的索引, 则需要使用`.index.get_level_values()`
```python
df_multi.index.names
>> FrozenList(['School', 'Gender'])
df_multi.columns.names
>> FrozenList(['Indicator', 'Grade'])
df_multi.index.values
>> array([('A', 'Female'), ('A', 'Male'), ('B', 'Female'), ('B', 'Male'),
>> 	   ('C', 'Female'), ('C', 'Male'), ('D', 'Female'), ('D', 'Male')], dtype=object)
df_multi.columns.values
>> array([('Height', 'Freshman'), ('Height', 'Senior'),
>>        ('Height', 'Sophomore'), ('Height', 'Junior'), 
>>        ('Weight', 'Freshman'), ('Weight', 'Senior'),
>>        ('Weight', 'Sophomore'), ('Weight', 'Junior')], dtype=object)

# 得到某一层的索引
df_multi.index.get_level_values(0)
>> Index(['A', 'A', 'B', 'B', 'C', 'C', 'D', 'D'], dtype='object', name='School')
df_multi.columns.get_level_values(0)
>> Index(['Height', 'Height', 'Height', 'Height', 'Weight', 'Weight', 'Weight', 'Weight'],
>> 	  dtype='object', name='Indicator')
```


### 多级索引的`loc`索引器
```python
df_multi = df.set_index(['School', 'Grade'])  # index包含两个部分
df_multi.head()
```
![[pandas_index_table2.png]]

- 首先进行索引排序, 避免发生性能警告(`pandas.errors.PerformanceWarning`)
- 与单层表的loc不同, 多层表的loc以tuple传入
```python
df_sorted.loc[('Fudan University', 'Junior')].head()  # 单个index
df_sorted.loc[[('Fudan University', 'Senior'),
			   ('Shanghai Jiao Tong University', 'Freshman')]].head()  # 多个

df_sorted.loc[df_sorted.Weight > 70].head() # 布尔列表也是可用的
df_sorted.loc[lambda x:('Fudan University','Junior')].head()  # 函数用于loc
df_multi.loc[('Fudan University', 'Senior'):].head()  # 报错, 仍然需要单独开头的index才能slice
df_sorted.loc[('Fudan University', 'Senior'):].head()  # sorted, 因为index已经sorted过了
df_unique = df.drop_duplicates(subset=['School','Grade']).set_index(['School', 'Grade'])  # drop
df_unique.sort_index().loc[('Fudan University', 'Senior'):]  # 新生成的表最好都sort一下

# 特殊用法: 自动outer, col需要带上: !
# 选择fudan和peking的二三年级学生
res = df_multi.loc[(['Peking University', 'Fudan University'], ['Sophomore', 'Junior']), :]
```


### IndexSlice对象
- 能够对每层进行切片, 也能将切片和布尔列表混用
- 两种形式: `.loc[idx[*,*]]`, `.loc[idx[*,*], idx[*,*]]`

```python
# 构造索引不重复的DataFrame
np.random.seed(0)

L1,L2 = ['A','B','C'],['a','b','c']
mul_index1 = pd.MultiIndex.from_product([L1,L2],names=('Upper', 'Lower'))
L3,L4 = ['D','E','F'],['d','e','f']
mul_index2 = pd.MultiIndex.from_product([L3,L4],names=('Big', 'Small'))
df_ex = pd.DataFrame(np.random.randint(-9,10,(9,9)), index=mul_index1, columns=mul_index2)
```
![[pandas_index_table3.png]]
```python
# 定义对象
idx = pd.IndexSlice

# loc[idx[*, *]] type
df_ex.loc[idx['C':, ('D', 'f'):]]  # 前一个是行, 后一个是列, 列用的是元组表示某一个确定的列
df_ex.loc[idx[:'A', lambda x:x.sum()>0]] # 列和大于0

# loc[idx[*, *], idx[*, *]] type
df_ex.loc[idx[:'A', 'b':], idx['E':, 'e':]]  # 同时进行slice
df_ex.loc[idx[:'A', lambda x: 'b'], idx['E':, 'e':]]  # 不支持使用函数: KeyError
```


### 多级索引的构造
- 除了使用`set_index`
- 常用的有`from_tuples, from_arrays, from_product`三种方法
- 它们都是`pd.MultiIndex`对象下的函数

```python
my_tuple = [('a','cat'),('a','dog'),('b','cat'),('b','dog')]
pd.MultiIndex.from_tuples(my_tuple, names=['First','Second'])  # 从元组进行构造
>> MultiIndex([('a', 'cat'), ('a', 'dog'), ('b', 'cat'), ('b', 'dog')], names=['First', 'Second'])

my_array = [list('aabb'), ['cat', 'dog']*2]
pd.MultiIndex.from_arrays(my_array, names=['First','Second'])  # zip两个array的对应元素进行构造
>> MultiIndex([('a', 'cat'), ('a', 'dog'), ('b', 'cat'), ('b', 'dog')], names=['First', 'Second'])

my_list1, my_list2 = ['a','b'], ['cat','dog']
pd.MultiIndex.from_product([my_list1, my_list2], names=['First','Second'])  # 使用outer外积进行构造
>> MultiIndex([('a', 'cat'), ('a', 'dog'), ('b', 'cat'), ('b', 'dog')], names=['First', 'Second'])
```


## 索引的常用方法

### 索引层的交换和删除
- 目的为交换索引的层的先后顺序
	- 可以通过两个方法进行修改, 见下
```python
np.random.seed(0)
L1,L2,L3 = ['A','B'],['a','b'],['alpha','beta']
mul_index1 = pd.MultiIndex.from_product([L1,L2,L3], names=('Upper', 'Lower','Extra'))
L4,L5,L6 = ['C','D'],['c','d'],['cat','dog']
mul_index2 = pd.MultiIndex.from_product([L4,L5,L6], names=('Big', 'Small', 'Other'))
df_ex = pd.DataFrame(np.random.randint(-9,10,(8,8)), index=mul_index1,  columns=mul_index2)

df_ex.swaplevel(0,2,axis=1)  # 列索引的第一层和第三层交换

df_ex.reorder_levels([2,0,1],axis=0).head() # 列表数字指代原来索引中的层

df_ex.droplevel(1,axis=1)  # 删除了列索引中Small对应的索引

df_ex.droplevel([0,1],axis=0)  # 删除了行索引中Upper和Lower对应的索引
```


### 索引属性的修改
- 通过字典修改索引的名称(修改axis)
- 通过字典和指定层, 修改具体的索引(修改index)
- trick: 通过迭代器, 进行axis的替换
```python
df_ex.rename_axis(index={'Upper':'Changed_row'}, columns={'Other':'Changed_Col'})
df_ex.rename(columns={'cat':'not_cat'}, level=2)  # 需要指定层
df_ex.rename(index=lambda x:str.upper(x), level=2)  # 将行的第二层修改为大写字母的index

new_values = iter(list('abcdefgh'))  # 通过迭代器进行替换
df_ex.rename(index=lambda x:next(new_values), level=2)  # 修改了列索引中extra对应的index具体值
```
- `map`方法能够跨层修改
	- 同时也可以用于多级索引的压缩/展开, 这有的时候是有用的
```python
df_temp = df_ex.copy()
new_idx = df_temp.index.map(lambda x: (x[0], x[1], str.upper(x[2])))  # 对每个index的tuple进行操作
df_temp.index = new_idx  # 赋值回去

# 压缩index
new_idx = df_temp.index.map(lambda x: (x[0]+'-'+x[1]+'-'+x[2]))
df_temp.index = new_idx

# 展开index
new_idx = df_temp.index.map(lambda x:tuple(x.split('-')))
df_temp.index = new_idx
```

### 索引的设置和重置
- `.set_index(keys[,append=False])`
	- append是否保留原index
- `.reset_index(keys[,drop=False])`
	- drop是否将原index添加回表格中
```python
df_new = pd.DataFrame({'A':list('aacd'), 'B':list('PQRT'), 'C':[1,2,3,4]})
df_new.set_index('A', append=False)  # 单个
df_new.set_index(['A', 'B'])  # 多个
my_index = pd.Series(list('WXYZ'), name='D')  # 重新指定新的
df_new = df_new.set_index(['A', my_index])  # 重新指定新的

df_new.reset_index(['D'])  # D column被添加回表格
df_new.reset_index(['D'], drop=True)  # D column没有被添加回表格
df_new.reset_index()  # 重置所有索引, 生成新的索引
```

### 索引的变形
- 直接添加行列, 对应的位置将会是
```python
df_reindex = pd.DataFrame({"Weight":[60,70,80], "Height":[176,180,179]},
						  index=['1001','1003','1002'])  # 原来的表

# 重新进行index
df_reindex.reindex(index=['1001','1002','1003','1004'], columns=['Weight','Gender'])
# 仿照格式进行index
df_existed = pd.DataFrame(index=['1001','1002','1003','1004'], columns=['Weight','Gender'])
df_reindex.reindex_like(df_existed)
```



## 索引运算

### 集合的运算法则

$$\rm S_A.intersection(S_B) = \rm S_A \cap S_B \Leftrightarrow \rm \{x|x\in S_A\, and\, x\in S_B\}$$
$$\rm S_A.union(S_B) = \rm S_A \cup S_B \Leftrightarrow \rm \{x|x\in S_A\, or\, x\in S_B\}$$
$$\rm S_A.difference(S_B) = \rm S_A - S_B \Leftrightarrow \rm \{x|x\in S_A\, and\, x\notin S_B\}$$
$$\rm S_A.symmetric\_difference(S_B) = \rm S_A\triangle S_B\Leftrightarrow \rm \{x|x\in S_A\cup S_B - S_A\cap S_B\}$$

### 一般的索引运算

- 由于集合的元素是互异的，但是索引中可能有相同的元素，先用`unique`去重后再进行运算

```python
df_set_1 = pd.DataFrame([[0,1],[1,2],[3,4]],
						index = pd.Index(['a','b','a'],name='id1'))
df_set_2 = pd.DataFrame([[4,5],[2,6],[7,1]],
						index = pd.Index(['b','b','c'],name='id2'))
id1, id2 = df_set_1.index.unique(), df_set_2.index.unique()  # 去重

id1.intersection(id2)
>> Index(['b'], dtype='object')

id1.union(id2)
>> Index(['a', 'b', 'c'], dtype='object')

id1.difference(id2)
>> Index(['a'], dtype='object')

id1.symmetric_difference(id2)
>> Index(['a', 'c'], dtype='object')
```

索引可以这样运算, 元素可以通过`isin`进行运算
```python
df_1[df_1.col1.isin(df_2.col2)]
```



## HW

### Ex1
```python
# 1
df.loc[(df.age < 40) | (df.department.isin(["Dairy", "Bakery"]))].head()

# 2
df.loc[(df.index % 2 == 1)].iloc[:, [0, 2, -2]].head()

# 3
df_new = df.copy()
df_new = df_new.set_index(df_new.columns[-3:].to_list())  # 后三列作为索引
print(df_new.index.names)
df_new = df_new.reorder_levels([2,1,0],axis=0).head()  # 交换内外两层
print(df_new.index.names)
df_new = df_new.reset_index(level=1)  # 恢复中间层索引
print(df_new.index.names)
df_new.index = df_new.index.map(lambda x: '_'.join(x))  # 下划线合并两层索引
print(df_new.index.unique())
df_new.index = df_new.index.map(lambda x: tuple(x.split('_')))  # 复原两层索引
print(df_new.index.unique())
df_new = df_new.reset_index(drop=False)  # 恢复原表名称
df_new = df_new.rename(columns={'level_0': 'gender', 'level_1': 'department'})  # 恢复原表名称
df_new.head()
df_new = pd.DataFrame(df_new, columns=df.columns)  # 保持原表列名称相对位置
df_new.head()
```




### Ex2

```python
# 1
df_new = df.copy()
df_new = pd.DataFrame(df_new.values, columns=df.columns.map(lambda x: x.replace('\r\n', ' ')))  # 保持原表列名称相对位置
df_new.head()

# 2
df_set1 = df_new.copy()
df_set1.loc[:, "Cocoa Percent"] = df_set1.loc[:, "Cocoa Percent"].map(lambda x: eval(x.replace('%', '')))
df_set1_cond1 = df_set1.loc[:, "Cocoa Percent"] > df_set1.loc[:, "Cocoa Percent"].mean()
df_set1 = df_set1.loc[(df_new.Rating < 2.75) | df_set1_cond1]
df_set1.loc[:, "Cocoa Percent"] = df_set1.loc[:, "Cocoa Percent"].map(lambda x: f"{x:.0f}%")
df_set1.head()

# 3
df_set2 = df_new.copy()
df_set2 = df_set2.set_index(["Review Date", "Company Location"])
df_set2_cond1 = list(map(lambda x: (x[0] > 2012) & (x[1] not in ["France", "Canada", "Amsterdam", "Belgium"]), df_set2.index.values))  # 设置筛选条件
df_set2 = df_set2.loc[df_set2_cond1]
df_set2.head()
```



