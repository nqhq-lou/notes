---
title: pandas basics
tags: [python/module/pandas, data_processing]
---

```python
import pandas
```

## file io

### file read
```python
pandas.read_csv(fname)
pandas.read_table(fname)
pandas.read_excel(fname)

pandas.read_table('../data/my_table.txt', header=None)  # no colname row
pandas.read_csv('../data/my_csv.csv', index_col=['col1', 'col2'])  # col as index col
pandas.read_table('../data/my_table.txt', usecols=['col1', 'col2'])  # only read these cols
pd.read_excel('../data/my_excel.xlsx', nrows=2)
pandas.read_csv('../data/my_csv.csv', parse_dates=['col5'])  # convert to date
# type is pandas._libs.tslibs.timestamps.Timestamp
pd.read_table('../data/my_table_special_sep.txt', sep=' \|\|\|\| ', engine='python')  # here the separator is r"||||"
```
- options
	- `header` 设置作为列名称的行, `None` for no specified colname
	- `index_col` 把某几列作为索引
	- `parse_dates` 指明需要转化为时间的列
	- `nrows` 读取数据的行数, 不算header
	- `sep` 指定分割用的符号, 建议同时指定`engine`为python
		- 注意sep使用正则表达式, 所以sep跟着的字符必须都是正则表达式
		- 如`|`需要转义`\|`

### file write
```python
df_csv.to_csv('../data/my_csv_saved.csv', index=False)
df_excel.to_excel('../data/my_excel_saved.xlsx', index=False)
df_txt.to_csv('../data/my_txt_saved.txt', sep='\t', index=False)

print(df_csv.to_markdown())  # 转markdown表格
print(df_csv.to_latex())  # 转latex表格
```
- options
	- `index` 行索引没有特殊意义, `False`不记录
	- `sep` 自定义分隔符


## 基本数据结构

### `Series`
- 对应一维结构
- 要素: values, index, dtype, name
	- 也是类的属性, 可以直接访问
	- 注意! index并不是唯一的! 可以有重复的index
```python
s := pd.Series(data = [100, 'a', {'dic1':5}],
          index = pd.Index(['id1', 20, 'third'], name='my_idx'),
          dtype = 'object',
          name = 'my_name')
>> my_idx
>> id1              100
>> 20                 a
>> third    {'dic1': 5}
>> Name: my_name, dtype: object

s.values  # array([100, 'a', {'dic1': 5}], dtype=object)
s.index  # Index(['id1', 20, 'third'], dtype='object', name='my_idx')
s.dtype  # dtype('O')
s.name  # 'my_name'
s.shape  # (3,)
s['third']  # {'dic1': 5}  # 这是进行索引
```

### `DataFrame`
- 对应二维结构
- 要素: values, index, columns, dtype
	- 也是类的属性, 可以直接访问
```python
data = [[1, 'a', 1.2], [2, 'b', 2.2], [3, 'c', 3.2]]
df = pd.DataFrame(data = data,
				  index = [f'row_{i}' for i in range(3)],
                  columns=['col_0', 'col_1', 'col_2'])
df = pd.DataFrame(data = {'col_0': [1,2,3],
                          'col_1':list('abc'),
                          'col_2': [1.2, 2.2, 3.2]},
                  index = ['row_%d'%i for i in range(3)])

df.values  # array([[1, 'a', 1.2], [2, 'b', 2.2], [3, 'c', 3.2]], dtype=object)
df.index  # Index(['row_0', 'row_1', 'row_2'], dtype='object')
df.columns  # Index(['col_0', 'col_1', 'col_2'], dtype='object')
df.shape  # (3, 3)
df.dtype
>> col_0     int64
>> col_1    object
>> col_2   float64
>> dtype: object
```
- 建立表格, 可以分别制定col和index, 也可以有col的形况下指定index
- 索引col, 可以索引单个或者列表个, 分别得到Series和DataFrame
- 通过`T`进行转置
```python
df['col_0']
>> 
row_0    1
row_1    2
row_2    3
Name: col_0, dtype: int64

df[['col_0', 'col_1']]  # 取前两列
>> 
       col_0 col_1
row_0      1     a
row_1      2     b
row_2      3     c

df = df[df.columns[:1]]  # 只取df的前两列

df.T
>> 
      row_0 row_1 row_2
col_0     1     2     3
col_1     a     b     c
col_2   1.2   2.2   3.2
```

- 插入一列, 使用insert方法
```python
df.insert(pos, colname, content)
df.insert(0, "head", None)
df.insert(0, "index_new", list(range(df.shape[0])))
```


## 常用基本函数

### 汇总函数

```python
df.head([n=5])
df.tail([n=5])
df.info()  # 信息概况
df.describe()  # 可以进行统计数值列的统计量
```
- 如果想要对一份数据集进行全面且有效的观察，特别是在列较多的情况下，推荐使用[pandas-profiling](https://pandas-profiling.github.io/pandas-profiling/docs/)包，它将在第十一章被再次提到。

### 特征统计函数
- `sum, mean, median, var, std, max, min`
- `quantile, count, idxmax` 分位数、非缺失值个数、最大值对应的索引
- 默认沿col进行统计
```python
df_demo.max()
>> 
Height    193.9
Weight     89.0
dtype: float64

df_demo.quantile(0.75)
>> 
Height    167.5
Weight     65.0
Name: 0.75, dtype: float64

df_demo.count()
>> 
Height    183
Weight    189
dtype: int64

df_demo.idxmax() # idxmin是对应的函数
>> 
Height    193
Weight      2
dtype: int64
```

### 唯一值函数
- 对序列使用 `unique` 和 `nunique` 可以分别得到其唯一值组成的列表和唯一值的个数
- `value_counts` 可以得到唯一值和其对应出现的频数
```python
df['School'].unique()
>> 
array(['Shanghai Jiao Tong University', 'Peking University',
       'Fudan University', 'Tsinghua University'], dtype=object)

df['School'].nunique()
>> 4

df['School'].value_counts()
>> 
Tsinghua University              69
Shanghai Jiao Tong University    57
Fudan University                 40
Peking University                34
Name: School, dtype: int64
```

- 多个列的组合的唯一值`drop_duplicates`
	- kwargs: `keep="first"`
- 显示是否重复`duplicated`
	- kwargs: `keep=first`
	- 把重复元素设为`True`，否则为`False
	- `drop_duplicates`等价于把`duplicated`为`True`的对应行剔除
```python
df_demo = df[['Gender','Transfer','Name']]

df_demo.drop_duplicates(['Gender', 'Transfer'])
df_demo.drop_duplicates(['Gender', 'Transfer'], keep='last')
df_demo.drop_duplicates(['Name', 'Gender'], keep=False)  # 保留只出现过一次的性别和姓名组合
df['School'].drop_duplicates() # 在Series上也可以使用

df_demo.duplicated(['Gender', 'Transfer'])
df['School'].duplicated().head() # 在Series上也可以使用
```


## 替换函数

- pandas中三类替换: 映射替换、逻辑替换、数值替换

#### 映射替换
- 映射替换包含`replace` `str.replace` `cat.codes`
	- replace可以通过字典传入, 或者两个列表
```python
df['Gender'].replace({'Female':0, 'Male':1})
df['Gender'].replace(['Female', 'Male'], [0, 1])
```
- 方向性替换
	- 指定`method`参数为`ffill`则为用前面一个最近的未被替换的值进行替换，`bfill`则使用后面最近的未被替换的值进行替换
```python
s = pd.Series(['a', 1, 'b', 2, 1, 1, 'a'])
s.replace([1, 2], method='ffill')
>>
0    a
1    a
2    b
3    b
4    b
5    b
6    a
dtype: object

s.replace([1, 2], method='bfill')
>>
0    a
1    b
2    b
3    a
4    a
5    a
6    a
dtype: object
```
- 正则表达式替换
	- 也是使用`replace`

#### 逻辑替换
- 包括`where`和`mask`
	- 两者对称: `where`对false进行替换, `mask`对true进行替换
- 实际上, 传入的条件只需是与被调用的`Series`索引一致的布尔序列即可
```python
s = pd.Series([-1, 1.2345, 100, -50])
s.where(s<0)
>> 
0    -1.0
1     NaN
2     NaN
3   -50.0
dtype: float64

s.mask(s<0, -50)
>> 
0    -50.0000
1      1.2345
2    100.0000
3    -50.0000

s_condition= pd.Series([True,False,False,True], index=s.index)
s.mask(s_condition, -50)
>> 
0     -50.0000
1       1.2345
2     100.0000
3     -50.0000
dtype: float64
```


#### 数值替换
- `round, abs, clip`方法
	- 分别表示按照给定精度四舍五入、取绝对值和截断
```python
s = pd.Series([-1, 1.2345, 100, -50])
s.round(2)
>>
0     -1.00
1      1.23
2    100.00
3    -50.00
dtype: float64

s.abs()
>> 
0     1.0000
1     1.2345
2   100.0000
3    50.0000
dtype: float64

s.clip(0, 2)
>> 
0    0.0000
1    1.2345
2    2.0000
3    0.0000
dtype: float64
```


### 排序函数

- 两种排序方式: `sort_values` `sort_index`
	- `sort_index(list)` 按列表中顺序作为重要性排列
		- 也可以组为列表传入
	- `sort_values(colname, ascending=True)` 默认递增
		- 也可以作为列表传入
```python
df_demo = df[['Grade', 'Name', 'Height', 'Weight']].set_index(['Grade','Name'])
df_demo.sort_index(level=['Grade','Name'],ascending=[True,False])

df_demo.sort_values('Height')
df_demo.sort_values(['Weight','Height'],ascending=[True,False])

```


### `apply`方法

- `apply`方法常用于`DataFrame`的行迭代或者列迭代
	- `f`参数为参数为序列的函数, `axis`参数指定迭代方向
	- **apply的性能可能非常差**, 因此尽量用内置函数

```python
# apply实现mean的例子
def my_mean(x):
     res = x.mean()
     return res
df_demo.apply(my_mean, axis=0)
# 或者用lambda
df_demo.apply(lambda x: x.mean())

# mad函数的例子
df_demo.mad()
df_demo.apply(lambda x:(x-x.mean()).abs().mean())
```


## 窗口对象

- 滑动窗口`rolling`、扩张窗口`expanding`, 指数加权窗口`ewm`

### 滑窗对象
- 对序列使用`rolling`方法创建滑窗对象, 参数为`windows`窗口大小
- 同时也可以使用`apply`方法
```python
s = pd.Series([1,2,3,4,5])
roller = s.rolling(window = 3)
roller
>> Rolling [window=3,center=False,axis=0]

roller.mean()
>> array([nan, nan, 2., 3., 4.])

roller.sum()
>> array([nan, nan, 6., 9., 12.])

# 滑动协方差
s2 = pd.Series([1,2,6,16,30])
roller.cov(s2)
>> array([ nan, nan, 2.5, 7. , 12. ])

roller.apply(lambda x:x.mean())
>> array([nan, nan, 2., 3., 4.])
```

- `shift, diff, pct_change`是一组类滑窗函数
	- 公共参数为`periods = 1`, 可以为负数
	- 取向前第`n`个元素的值, 与向前第`n`个元素做差（与`Numpy`中不同，后者表示`n`阶差分）, 与向前第`n`个元素相比计算增长率
```python
s = pd.Series([1,3,6,10,15])
s.shift(2).values
>> array([nan, nan, 1., 3., 6.])
s.shift(-1).values
>> array([ 2., 3., 4., 5., nan])
s.rolling(3).apply(lambda x:list(x)[0]).values # s.shift(2)
>> array([nan, nan, 1., 3., 6.])


s.diff(3).values
>> array([nan, nan, nan, 3., 3.])
s.diff(-2).values
>> array([-2., -2., -2., nan, nan])
s.rolling(4).apply(lambda x:list(x)[-1]-list(x)[0]).values # s.diff(3)
>> array([nan, nan, nan, 3., 3.])

s.pct_change().values
>> array([ nan, 1. , 0.5 , 0.33333333, 0.25 ])
s.rolling(2).apply(lambda x: list(x)[-1]/list(x)[0]-1).values # s.pct_change()
>> array([ nan, 1. , 0.5 , 0.33333333, 0.25 ])
```


### 扩张窗口
- 窗口不断依次扩大
	- 设序列为{a1, a2, a3, a4}
	- 则其每个位置对应的窗口即{a1}, {a1, a2}, {a1, a2, a3}, {a1, a2, a3, a4}
```python
s = pd.Series([1, 3, 6, 10])
s.expanding().mean()
>> array([1. , 2. , 3.33333333, 5. ])
```


## HW

### Ex 1
```python
# 1
any(df[df.columns[-6:]].sum(axis=1)==df["Total"])

# 2
df2 = df.drop_duplicates(['#'], keep='first')
df2.shape
# 第一属性种类数量
print(df2["Type 1"].unique().shape[0])
# 前三多种类
print(df2["Type 1"].value_counts().head(3))
# 一二属性的组合种类数
df2_exist = df[['Type 1', 'Type 2']].drop_duplicates(keep='first')
print(df2_exist.shape[0])
# 未出现的属性组合
possible_types = pd.concat([df2["Type 1"], df2["Type 2"]]).drop_duplicates()
possible_types = set(possible_types)  # 单一属性, 包括np.nan
double_types = pd.DataFrame(
    data = [[t1, t2] for t1 in possible_types for t2 in possible_types
    if (t1 != t2 and t1 is not np.nan)],
    columns=df2_exist.columns
)
df2_notype = pd.concat([df2_exist, double_types]).drop_duplicates(keep=False)
df2_notype.shape

# 3
attack_series = df["Attack"]
high_cond = pd.Series(attack_series > 120, index=attack_series.index)
low_cond = pd.Series(attack_series < 50, index=attack_series.index)
mid_cond = np.logical_not(np.array([high_cond, low_cond]).any(axis=0))
mid_cond = pd.Series(data=mid_cond, index=attack_series.index)
attack_series = attack_series.mask(high_cond < 50, "low")
attack_series = attack_series.mask(low_cond > 120, "high")
attack_series = attack_series.mask(mid_cond, "mid")
attack_series.head(10)
# 或者一次性
df['Attack'].mask(df['Attack']>120, 'high') \
            .mask(df['Attack']<50, 'low') \
            .mask((df['Attack']<=120)&(df['Attack']>=50), 'mid')
```

### Ex2
```python
# 1
def ewm(d:pd.Series, alpha=0.2):
    def _single(x: pd.Series):
        weight = np.array([(1-alpha)**i for i in range(len(x))])
        return weight.dot(x.values[::-1]) / weight.sum()
    return d.expanding().apply(_single)
  
ewm(s, alpha=0.2).head()


# 2
def ewm_rolling(d:pd.Series, alpha=0.2, n=5):
    weight = np.array([(1-alpha)**i for i in range(n)])
    def _single(x: pd.Series):
        return weight.dot(x.values[::-1]) / weight.sum()
    return d.rolling(window=n).apply(_single)
  
ewm_rolling(s, alpha=0.2, n=5).head(10)
```










