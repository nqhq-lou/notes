---
title: pandas grouping
tags: [python/module/pandas, data_processing]
---

## 分组模式和对象

### 分组的一般模式
- `df.groupby(分组依据)[数据来源].使用操作方法`
	- e.g. `df.groupby('Gender')['Longevity'].mean()`
	- 按性别分类, 统计寿命的平均值.

### 分组依据的本质
```python
# 按学校性别分类, 数据为身高, 求类内平均值
df.groupby(['School', 'Gender'])['Height'].mean()
# 按条件分类,  数据为身高, 求类内平均值
condition = df.Weight > df.Weight.mean()  # 高于平均值 的条件
df.groupby(condition)['Height'].mean()
```
- 自定义新的分类依据
```python
cond_low = df_ex['Weight'] < df_ex['Weight'].quantile(0.75)
cond_normal = (df_ex['Weight'] >= df_ex['Weight'].quantile(0.25)) & (df_ex['Weight'] < df_ex['Weight'].quantile(0.75))
cond_high = df_ex['Weight'] >= df_ex['Weight'].quantile(0.75)
df_cate = pd.Series(['null'] * df.shape[0])  # 创
df_cate[cond_low], df_cate[cond_normal], df_cate[cond_high] = 'low', 'normal', 'high'  #
df.groupby(df_cate)['Height'].mean()
# 也可以混合起来慵
df.groupby(['School', df_cate])['Height'].mean()
```


### `Groupby`对象
- 以上操作, 实际上都是使用了`df.groupby()`方法生成了分组对象`Groupby`, 然后调用他的方法
	- 比如`.mean()`和`.median()`都是groupby上的方法
- `Groupby`对象有自己的属性和方法
```python
gb = df.groupby(['School', 'Grade'])  # Groupby对象
gb.ngroups  # 属性, 得到分组个数
res = gb.groups  # 得到dict (实际上是一个改进的dict)
res.keys()  # 显示分组的具体情况
df[['School', 'Gender']].drop_duplicates()  # 和上面的显示内容相同
gb.size()  # 统计每个分组的分类
gb.get_group(('Fudan University', 'Freshman'))  # 提供具体名字, 返回本组对应的df
```

### 分组的三大操作
- 聚合, 变换, 过滤


## 聚合函数

### 内置聚合函数
- 有限考虑内置聚合函数, 因为有性能优化
- 包括如下函数
	- `size/count/nunique` size, count size (这两个的区别?), 唯一个数
	- `all/any` all, any
	- `max/min/mean/median/prod` product of group values
	- `idxmax/idxmin/mad` first, last
	- `quantile/sum/std/var/`
	- `mad/skew/sem` mean absolute deviation, 偏度, standard error of the mean of groups
```python
gb = df.groupby('Gender')[['Height', 'Weight']]
gb.max()
>>        Height Weight
>> Gender
>> Female  170.2   63.0
>> Male    193.9   89.0
```

### `agg`方法
- 使用多个聚合函数
- 对特定列使用特定聚合函数
- 使用自定义函数
- 聚合结果重命名
```python
gb = df.groupby('Gender')[['Height', 'Weight']]
# 使用多个聚合函数
gb.agg(['sum', 'idxmax', 'skew'])
# 对特定列使用特定聚合函数
gb.agg({'Height':['mean','max'], 'Weight':'count'})
# 使用自定义函数
func0 = lambda x: x.mean()-x.min()
func1 = lambda x: x.mean()-x.min()
gb.agg([func0, func1])
# 聚合结果重命名, tuple(name, func)
gb.agg([('inferior', func0), ('super', func1)])
# 综合使用, 不同列不同函数, 有的进行重命名
gb.agg({'Height': [('my_func', my_func), 'sum'], 'Weight': lambda x:x.max()})
```


## 变换和过滤

### 变换函数和`transform`方法
- 最常用的内置变换函数是累计函数：`cumcount/cumsum/cumprod/cummax/cummin`
	- 完成组内累计操作, 然后显示所有行
- `rank`方法: **没看懂怎么用!!**
	- 是给出排序吗?
- `transform`方法: 进行组内操作
```python


gb.transform(lambda x: (x - x.mean()) / x.std())  # 进行组内标准化, 这里x指代组
gb.transform("mean")  # 传入函数的名称也可以
```

### 组索引与过滤
- True的组将被留下, False的组将被过滤, 未过滤组组成DataFrame返回
```python
gb.filter(lambda x: x.shape[0] > 100)  # 保留容量大于100的组
```



## 跨列分组

### `apply`的引入
- 能够实现分组下的跨列操作, 多列数据同时处理
	- 传入按组操作的函数
```python
def BMI(x:pd.DataFrame):
    Height = x['Height']/100
    Weight = x['Weight']
    BMI_value = Weight/Height**2
    return BMI_value.mean()
gb.apply(BMI)  # 计算组内BMI
```

### `apply`的使用
- 按照返回值的不同, 分为多种情况
#### 标量情况
```python
gb = df.groupby(['Gender','Test_Number'])[['Height','Weight']]
gb.apply(lambda x: 0)  # 直接输出0, 因为是测试
>> Gender  Test_Number
>> Female  1            0
>>         2            0
>>         3            0
>> Male    1            0
>>         2            0
>>         3            0
>> dtype: int64

gb.apply(lambda x: [0, 0]) # 虽然是列表，但是作为返回值仍然看作标量
```

#### `Series`情况
- 得到DataFrame
- 如果不同情况下的返回的Series的index和长度不同, 则会报错!
```python
gb.apply(lambda x: pd.Series([0,0],index=['a','b']))
>>                      a  b
>> Gender  Test_Number
>> Female  1            0  0
>>         2            0  0
>>         3            0  0
>> Male    1            0  0
>>         2            0  0
>>         3            0  0
```

#### `DataFrame`情况
- 会增加额外的index, 和原来的group的index组合, 进而组合成大的dataframe
```python
gb.apply(lambda x: pd.DataFrame(np.ones((2,2)), index = ['a','b'], columns=pd.Index([('w','x'),('y','z')])))

```
![[pandas_group_table1.png]]


## HW

### Ex1 汽车数据集
```python
# 1
gb = df.groupby('Country')
gb = gb.filter(lambda x: x.shape[0] >= 2).groupby('Country')
gb.agg({'Price': ['mean', ('Cov', lambda x: x.std()/x.mean()), 'count']})
  
# 2
df_new = df.copy()
df_cate = pd.Series(['null'] * df.shape[0])
df_idx = pd.Series(df.index)
cond_first = df_idx <= df_idx.quantile(1/3)
cond_second = (df_idx > df_idx.quantile(1/3)) & (df_idx <= df_idx.quantile(2/3))
cond_third = df_idx > df_idx.quantile(2/3)
df_cate[cond_first], df_cate[cond_second], df_cate[cond_third] = 'first', 'seconde', 'third'
df_new.groupby(df_cate)['Price'].mean()
  
# 3
gb = df.groupby('Type')
df_3 = gb.agg({'Price': ['max', 'min'], 'HP': ['max', 'min']})
df_3.columns = map(lambda l: '_'.join(l), df_3.columns)
df_3
  
# 4
def norm(x: pd.Series) -> pd.Series:
    return (x - x.min()) / (x.max() - x.min())
gb = df.groupby('Type')
gb['HP'].transform(norm)
  
# 5
gb = df.groupby('Type')
gb[['Disp.', 'HP']].corr()
```

### Ex2

```python
import pandas

class my_groupby:
    def __init__(self, df: pandas.DataFrame, group_cols: list[str]):
        self._df = df.reset_index(drop=False).set_index(group_cols).sort_index(axis=0, inplace=False)
        self._dict = {idx: self._df.loc[idx] for idx in self._df.index.unique()}
        # pandas.MultiIndex.from_product([df[col].unique() for col in group_cols], names=group_cols)
    def __getitem__(self, item):
        if isinstance(item, str):
            self._dict = {key: val.loc[item] for key, val in self._dict.items()}
            return self
        elif isinstance(item, slice):
            self._dict = {key: val.loc[:, item] for key, val in self._dict.items()}
            return self
        elif isinstance(item, list):
            self._dict = {key: val.loc[:, item] for key, val in self._dict.items()}
            return self
        else:
            raise Exception('Invalid index type')
    def __len__(self):
        return len(self._dict)
    def transform(self, my_func:callable):
        self._dict = {key: my_func(val) for key, val in self._dict.items()}
        return pandas.DataFrame.from_dict(self._dict).transpose()
  
def my_func(x: pandas.DataFrame) -> pandas.DataFrame:
    return pd.Series([x['Price'].mean(), x['Weight'].min()], index=['a', 'b'])
  
my_groupby(df, ['Type', 'Country'])['Price':'Disp.'].transform(my_func)
my_groupby(df, ['Type', 'Country'])[['Price', 'Weight']].transform(lambda x: x.mean())
```
- 输出结果不一样, 但是我不想改了, 有点麻烦
- 如果修改, 则根据_dict中的index列, 扩充成dataframe再拼接即可.