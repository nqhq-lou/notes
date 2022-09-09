---
title: pandas deform
tags: [python/module/pandas, data_processing]
---


## 长宽表的变形

- 对于某一特征, 存储到某一列中 为长表(long), 存储到列名中 为宽表(wide).
- e.g. `Gender, Height` & `Height:F, Height:M`

### pivot
- 指定columns成为新的index, columns和values
- 需要满足唯一性要求: index和column组合起来, 对应的value必须唯一
	- 不然会一个空对应多个数值, 不知道要填哪个
	- 参数column将会成为`df.columns.name`
```python
df = pd.DataFrame({'Class':[1,1,2,2],
                   'Name':['San Zhang','San Zhang','Si Li','Si Li'],
                   'Subject':['Chinese','Math','Chinese','Math'],
                   'Grade':[80,75,90,85]})

df.pivot(index='Name', columns='Subject', values='Grade')
```
| Name      | Chinese | Math |
|:--------- | -------:| ----:|
| San Zhang |      80 |   75 |
| Si Li     |      90 |   85 |
![[pandas_deform_table1.png|300]]
- `pivot`支持多级联排, 使用list即可
```python
df = pd.DataFrame({'Class':..., 'Name':..., 'Examination':...,
				   'Subject':..., 'Grade':..., 'rank':...})
pivot_multi = df.pivot(index = ['Class', 'Name'],
                       columns = ['Subject','Examination'],  # df.columns.name
                       values = ['Grade','rank'])
```
![[pandas_deform_table2.png|400]]

### pivot_table
- 对于`pivot`必须满足唯一性, 这里可以使用`pivot_table`进行agg
	- 参数`aggfunc`, 应当填写不唯一时的聚合函数
		- 可以时字符串, 也可以是callable, like `'mean' == lambda x: x.mean()`
	- 参数`margins:bool`, 是否进行边际汇总
```python
df.pivot_table(index = 'Name', columns = 'Subject',
               values = 'Grade', aggfunc = lambda x:x.mean())  # 或者 'mean'

df.pivot_table(index = 'Name', columns = 'Subject',
			   values = 'Grade', aggfunc='mean', margins=True)
```
| Name      | Chinese | Math |
|:--------- | -------:| ----:|
| San Zhang |    77.5 | 87.5 |
| Si Li     |      75 |   90 |
and
| Name      | Chinese |  Math |  All |
|:--------- | -------:| -----:| ----:|
| San Zhang |    77.5 |  87.5 | 82.5 |
| Si Li     |      75 |    90 | 82.5 |
| All       |   76.25 | 88.75 | 82.5 |

### melt
```python
df_melted = df.melt(id_vars=['Class', 'Name'],  # hold
					value_vars=['Chinese', 'Math'],  # 做新的列值
					var_name='Subject',  # 作新的列名称
					value_name='Grade')  # 给定values的新列名称
```
![[pandas_deform_table3.png|500]]

### wide_to_long
- melt中, 原列名称只能表示一种分类
- `wide_to_long`可以处理具有多种含义的列名称
```python
# 结果见下图
df = pd.DataFrame({'Class':[1,2],'Name':['San Zhang', 'Si Li'],
                   'Chinese_Mid':[80, 75], 'Math_Mid':[90, 85],
                   'Chinese_Final':[80, 75], 'Math_Final':[90, 85]})
pd.wide_to_long(df,
                stubnames=['Chinese', 'Math'],  # 仍做colname
                i=['Class', 'Name'],  # index
                j='Examination',  # 原来colname中剩下来的部分, 用来做列值
                sep='_',  # 原colname的sep
                suffix='.+')  # sep后面的内容匹配, 这里可以是 r'(Mid|Final)'
```
![[pandas_deform_table4.png|400]]

- 一个例子
```python
res = pivot_multi.copy()  # 防止修改原表格内容
res
>> 
                    Grade                    rank                 
Subject             Chinese    Math          Chinese    Math      
Examination         Mid Final  Mid Final     Mid Final  Mid Final
Class Name                                                       
1     San Zhang      80    75   90    85      10    15   20     7
2     Si Li          85    65   92    88      21    15    6     2

res.columns = res.columns.map(lambda x:'_'.join(x))  # columns连接
res = res.reset_index()
res = pd.wide_to_long(res, stubnames=['Grade', 'rank'],
					  i = ['Class', 'Name'],
					  j = 'Subject_Examination',
					  sep = '_', suffix = '.+')  # colname中的内容转移到
res
>> 
                                     Grade  rank
Class Name      Subject_Examination             
1     San Zhang Chinese_Mid             80    10
                Chinese_Final           75    15
                Math_Mid                90    20
                Math_Final              85     7
2     Si Li     Chinese_Mid             85    21
                Chinese_Final           65    15
                Math_Mid                92     6
                Math_Final              88     2

res = res.reset_index()
res[['Subject', 'Examination']] = res['Subject_Examination'].str.split('_', expand=True)  # 新建行, 同时把原来组合列的列值拆开放进去
res = res[['Class', 'Name', 'Examination', 'Subject', 'Grade', 'rank']].sort_values('Subject')  # 按标准排序
res = res.reset_index(drop=True)  # 重置数字索引
res
>> 
   Class       Name Examination  Subject  Grade  rank
0      1  San Zhang         Mid  Chinese     80    10
1      1  San Zhang       Final  Chinese     75    15
2      2      Si Li         Mid  Chinese     85    21
3      2      Si Li       Final  Chinese     65    15
4      1  San Zhang         Mid     Math     90    20
5      1  San Zhang       Final     Math     85     7
6      2      Si Li         Mid     Math     92     6
7      2      Si Li       Final     Math     88     2
```


## 索引

### stack与unstack
- `unstack`将index中的索引放在column中
	- 同样满足唯一性: 被转为列索引的行索引层 & 保留的行索引层, 组成的index结构是唯一的
	- 不然unstack之后有的位置会对应多个值, 出现歧义
	- `ValueError('Index contains duplicate entries, cannot reshape')`
- `stack` 将column中的索引压入
	- 两者就是逆操作
```python
df = pd.DataFrame(np.ones((4,2)),
                  index = pd.Index([('A', 'cat', 'big'),
                                    ('A', 'dog', 'small'),
                                    ('B', 'cat', 'big'),
                                    ('B', 'dog', 'small')]),
                  columns=['col_1', 'col_2'])

# unstack
df.unstack()  # 默认最内层, 这里是 ('big', 'small')对应的第2/-1层
df.unstack(level=2)  # 效果相同
>> 
        col_1       col_2      
        big small   big small
A cat   1.0   NaN   1.0   NaN
  dog   NaN   1.0   NaN   1.0
B cat   1.0   NaN   1.0   NaN
  dog   NaN   1.0   NaN   1.0

df.usntack(levle=[1,2])  # 这两层都放到行内
>> 
    col_1       col_2    
    cat   dog   cat   dog  
    big small   big small
A   1.0   1.0   1.0   1.0
B   1.0   1.0   1.0   1.0


df = df.T  # 列索引有三级
df.stack()  # 第二层
df.stack([1, 2])  # 第一二层
>> 
                     A    B
index_1 cat big    1.0  1.0
        dog small  1.0  1.0
index_2 cat big    1.0  1.0
        dog small  1.0  1.0
```


### 聚合和变形的关系
- 变形中, values个数不变
- 聚合中, values的数量发生变化
	- 产生新的列索引, 多个值变成一个值



## 其他变形函数

### crosstab
- `crosstab`能够实现的功能, `pivot_table`都能实现
- 默认情况下`crosstab`统计元素组合出现的频数
```python
pd.crosstab(index=df.School, columns=df.Transfer)  # 统计不同学校transfer的情况

pd.crosstab(index=df.School, columns=df.Transfer, values=df.shape[0], aggfunc='count')  # 完整的写法
pd.crosstab(index=df.School, columns=df.Transfer, values=df.Transfer, aggfunc='count')  # 完整的写法, 第二种

df.pivot_table(index = 'School', columns = 'Transfer',
               values = 'Name', aggfunc = 'count')  # pivot的等效写法

pd.crosstab(index = df.School, columns = df.Transfer,
			values = df.Height, aggfunc = 'mean')  # 统计对应(School,Transfer)组合的身高平均值

```

### explode
- `explode`参数能够对某一列的元素进行纵向的展开，被展开的单元格必须存储`list, tuple, Series, np.ndarray`中的一种类型
```python
# column A这里是神奇的组合
df_ex = pd.DataFrame({'A': [[1, 2], 'my_str', {1, 2}, pd.Series([3, 4])], 'B': 1})
df_ex.explode('A')
# col A 变成: [1, 2, 'my_str', 1, 2, 3, 4]
```

### get_dummies
`get_dummies`是用于特征构建的重要函数之一，其作用是把类别特征转为指示变量。例如，对年级一列转为指示变量，属于某一个年级的对应列标记为1，否则为0
```python
pd.get_dummies(df.Grade).head()
```
|     | Freshman | Junior | Senior | Sophomore |
| ---:| --------:| ------:| ------:| ---------:|
|   0 |        1 |      0 |      0 |         0 |
|   1 |        1 |      0 |      0 |         0 |
|   2 |        0 |      0 |      1 |         0 |
|   3 |        0 |      0 |      0 |         1 |
|   4 |        0 |      0 |      0 |         1 |




## Ex 

没时间做了, 之后吧!