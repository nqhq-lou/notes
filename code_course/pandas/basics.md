## Python basics on data proc

- list comprehension
```python
[f'{m}_{n}' for m in ['a', 'b', 'c'] for n in ['d', 'e'] if m!='c']
>> ['a_d', 'a_e', 'b_d', 'b_e']

[f'{m}_{n}' if m=='a' else f'_{n}' for m in ['a', 'b'] for n in ['d', 'e']]
>> ['a_d', 'a_e', '_d', '_e']
```

- lambda function and `map` method
```python
list(map(lambda x, y: str(x)+'_'+y, range(5), list('abcde')))
>> ['0_a', '1_b', '2_c', '3_d', '4_e']
```

- `zip` and `enumerate` method
```python
L1, L2, L3 = 'abc', 'ijk', 'xyz'
for idx, (m, n, l) in enumerate(zip(L1, L2, L3)):
	print(f"{idx}, ({m}, {n}, {l})")
>> 0, (a, i, x)
>> 1, (b, j, y)
>> 2, (c, k, z)
```


## Numpy basics

```python
import numpy
```

- seed
	- given certain seed, return fixed result
```python
numpy.random.seed(0)
numpy.random.rand()
>> 0.5488135039273248
```

### construct array
- construct arrays
```python
numpy.array([1,2,3])
>> array([1,2,3])

"""等差数列"""
numpy.linspace(1, 5, 11)  # (start, end(include), cnt)
>> array([1. , 1.4, 1.8, 2.2, 2.6, 3. , 3.4, 3.8, 4.2, 4.6, 5. ])

numpy.arange(1, 5, 3)  # (start, end(exclude), cnt)
>> array([1, 3])
```

- special matrix
```python
numpy.zeros((2,3)) # 传入元组表示各维度大小
>> 
array([[0., 0., 0.],
       [0., 0., 0.]])

numpy.eye(3) # 3*3的单位矩阵
>> 
array([[1., 0., 0.],
	   [0., 1., 0.],
	   [0., 0., 1.]])

numpy.eye(3, k=1) # 偏移主对角线1个单位的伪单位矩阵
>> 
array([[0., 1., 0.],
       [0., 0., 1.],
       [0., 0., 0.]])

numpy.full((2,3), 10) # 元组传入大小，10表示填充数值
>> 
array([[10, 10, 10],
       [10, 10, 10]])

numpy.full((2,3), [1,2,3]) # 每行填入相同的列表
>> 
array([[1, 2, 3],
       [1, 2, 3]])
```

- random matrix
```python
numpy.random.rand(3) # uniform in [0, 1], size = (3)

numpy.random.rand(3, 3) # size = (3,3)

numpy.random.uniform(5, 15, 3)  # uniform distribution

numpy.random.randn(2,2)  # normal distribution, shape = (2,2)

numpy.random.normal(0, 3, (3,2))  # mean, std(mu), size

numpy.random.randint(5, 15, (3,2))  # low, high(exclude), size
```

- random sample
```python
my_list = ['a', 'b', 'c', 'd']
numpy.random.choice(my_list, 2, replace=False, p=[0.1, 0.7, 0.1 ,0.1])
>> array(['b', 'a'], dtype='<U1')
numpy.random.permutation(my_list)
>> array(['c', 'b', 'a', 'd'], dtype='<U1')
```

### array reshape

```python
numpy.zeros((2,3)).T  # transpose

numpy.r_[np.zeros((2,3)),np.zeros((2,3))]  # vertical
>>
array([[0., 0., 0.],
	   [0., 0., 0.],
	   [0., 0., 0.],
	   [0., 0., 0.]])

numpy.c_[np.zeros((2,3)),np.zeros((2,3))]  # horizontal
>> 
array([[0., 0., 0., 0., 0., 0.],
	   [0., 0., 0., 0., 0., 0.]])
```

- 一维数组和二维数组进行合并时，应当把其视作列向量，在长度匹配的情况下只能够使用左右合并的`c_`操作
```python
numpy.r_[np.zeros(2),np.zeros((2,2))]  # error
numpy.c_[np.zeros(2),np.zeros((2,2))]  # size: (2,3)
```

- `reshape`
```python
target = numpy.arange(8).reshape(2,4)
target
>>
array([[0, 1, 2, 3],
	   [4, 5, 6, 7]])

target.reshape((4,2))
>>
array([[0, 1],
	   [2, 3],
	   [4, 5], 
	   [6, 7]])

target.reshape((4,2), order='C')  # 按照行读取和填充, c-like
>>
array([[0, 1],
	   [2, 3],
	   [4, 5], 
	   [6, 7]])

target.reshape((4,2), order='F')  # 按照列读取和填充, fortran-like
>>
array([[0, 2],
	   [4, 6],
	   [1, 3],
	   [5, 7]])
```

- slice and index
```python
target = numpy.arange(9).reshape(3,3)
target
>> 
array([[0, 1, 2],
       [3, 4, 5],
       [6, 7, 8]])

target[:-1, [0,2]]
>>
array([[0, 2],
       [3, 5]])

# 本质上是返回了open mesh用的array
target[np.ix_([True, False, True], [True, False, True])]
>>
array([[0, 2],
       [6, 8]])

target[np.ix_([1,2], [True, False, True])]
>>
array([[3, 5],
       [6, 8]])
```

- 当数组维度为1维时，可以直接进行布尔索引，而无需`np.ix_`
```python
new = numpy.arange(9)
new[new%2==0]  # 逐个尝试数组内的操作, 实质是通过bool进行索引
>> array([0, 2, 4, 6, 8])
func_bool = lambda x: x%2==0
new[func_bool(new)]
>> array([0, 2, 4, 6, 8])
```

### commonly used method

- `where`
```python
a = numpy.arange(10)
numpy.where(a<5, a, 10*a)  # condition, true, false
>> array([ 0, 1, 2, 3, 4, 50, 60, 70, 80, 90])
```

- `nonzero`, `argmin`, `argmax`
```python
numpy.nonzero(numpy.arange(-5,5))
>> (array([0, 1, 2, 3, 4, 6, 7, 8, 9], dtype=int64),)

numpy.nonzero(numpy.eye(3, k=1))
>> (array([0, 1], dtype=int64), array([1, 2], dtype=int64))

a = numpy.array([[-2,-5,0],[1,3,-1]])
idx = numpy.unravel_index(a.argmax(), a.shape)
idx, a[idx]
>> ((1, 1), 3)

a = numpy.array([1,2,3,4])
a.argmin()
>> 0
```

- `any`, `all`
	- `any`指当序列至少 **存在一个** `True`或非零元素时返回`True`，否则返回`False`
	- `all`指当序列元素 **全为** `True`或非零元素时返回`True`，否则返回`False`
```python
a = np.array([0,1])
a.any(), a.all()
>> True, False
```

- `cumprod`, `cumsum`, `diff`
	- `cumprod`, `cumsum`分别表示累乘和累加函数，返回同长度的数组
	- `diff`表示和前一个元素做差，由于第一个元素为缺失值，因此在默认参数情况下，返回长度是原数组减1
```python
a = np.array([1,2,3])
a.cumprod(), a.cumsum(), numpy.diff(a)
>> array([1, 2, 6], dtype=int32),
   array([1, 3, 6], dtype=int32),
   array([1, 1])
```

- 统计函数
	- `max, min, mean, median, std, var, sum
	- `numpy.quantile`
		- 有时需要指定`axis`进行计算
		- `nan*`对应有缺失值的函数
	- 对于协方差和相关系数分别可以利用`cov, corrcoef`计算
```python
a = np.array([1, 2, np.nan])
numpy.nanquantile(a, 0.5)
>> 4.5
numpy.nanmax(a)
>> 2
numpy.max(a)
>> nan

target1 = np.array([1,3,5,9])
target2 = np.array([1,5,3,-9])
np.cov(target1, target2)
>> array([[ 11.66666667, -16.66666667],
          [-16.66666667, 38.66666667]])
np.corrcoef(target1, target2)
>> array([[ 1. , -0.78470603],
          [-0.78470603, 1. ]])
```

### broadcast

- 标量和数组的操作
```python
res = 3 * numpy.ones((2,2)) + 1
res = 1 / res
res
>> array([[0.25, 0.25],
          [0.25, 0.25]])
```

- 二维数组的操作
```python
res = np.ones((3,2))
res * np.array([[2,3]]) # 第二个数组扩充第一维度为3
>> array([[2., 3.],
          [2., 3.],
          [2., 3.]])
res * np.array([[2],[3],[4]]) # 第二个数组扩充第二维度为2
>> array([[2., 2.],
          [3., 3.],
          [4., 4.]])
res * np.array([[2]]) # 等价于两次扩充，第二个数组两个维度分别扩充为3和2
>> array([[2., 2.],
          [2., 2.],
          [2., 2.]])
```

- 一维和二维的操作
	- 当一维数组$A_k$与二维数组$B_{m,n}$操作时，等价于把一维数组视作$A_{1,k}$的二维数组，使用的广播法则与二维中一致，当$k!=n$且$k,n$都不是$1$时报错。
```python
# 以下内容结果相同
np.ones(3) + np.ones((2,3))
np.ones(3) + np.ones((2,1))
np.ones(1) + np.ones((2,3))
```

### 向量和矩阵的计算

- 向量内积
	- `a.dot(b)`

- 向量范数和矩阵范数
	- 最重要的是`ord`参数
| ord | norm for matrices | norm for vectors |
| :---- | ----: | ----: |
| None   | Frobenius norm | 2-norm |
| 'fro'  | Frobenius norm  | / |
| 'nuc'  | nuclear norm    | / |
| inf    | max(sum(abs(x), axis=1))   | max(abs(x)) |
| -inf   | min(sum(abs(x), axis=1))  |  min(abs(x)) |
| 0      | /   |  sum(x != 0) |
| 1      | max(sum(abs(x), axis=0))  |  as below |
| -1     | min(sum(abs(x), axis=0))   |  as below |
| 2      | 2-norm (largest sing. value) | as below |
| -2     | smallest singular value    | as below |
| other  | /   | sum(abs(x)\*\*ord)\*\*(1./ord) |
$$||A||_F = \sqrt{tr(A^T A)} = \sqrt{\sum_{i,j} a_{ij}^2}$$

```python
matrix_target =  np.arange(4).reshape(-1,2)

numpy.linalg.norm(matrix_target, 'fro')  # 3.7416573867739413
numpy.linalg.norm(matrix_target, np.inf)  # 5.0
numpy.linalg.norm(matrix_target, 2)  # 3.702459173643833

vector_target =  np.arange(4)
np.linalg.norm(vector_target, np.inf)  # 3.0
np.linalg.norm(vector_target, 2)  # 3.7416573867739413
numpynp.linalg.norm(vector_target, 3)  # 3.3019272488946263

```

### 矩阵乘法

$$\rm [\mathbf{A}_{m\times p}\mathbf{B}_{p\times n}]_{ij} = \sum_{k=1}^p\mathbf{A}_{ik}\mathbf{B}_{kj}$$
```python
a = np.arange(4).reshape(-1,2)
b = np.arange(-4,0).reshape(-1,2)
a@b
>> array([[ -2, -1],
          [-14, -9]])
```



## HW

### Ex1：利用列表推导式写矩阵乘法

一般的矩阵乘法根据公式，可以由三重循环写出，请将其改写为列表推导式的形式。

```python
def matmul(m1:numpy.ndarray, m2:numpy.ndarray) -> numpy.ndarray:
    if m1.shape[1] != m2.shape[0]:
        raise Exception(f'shape not match for m1 {m1.shape} and m2 {m2.shape}')
    ret = [[m1r.dot(m2c) for m2c in m2.T] for m1r in m1]
    return numpy.array(ret)
  
a = np.arange(4).reshape(-1,2)
b = np.arange(-4,0).reshape(-1,2)
a@b == matmul(a,b)
>> array([[ True, True],
		  [ True, True]])
```

### Ex2：更新矩阵

设矩阵 $A_{m×n}$ ，现在对 $A$ 中的每一个元素进行更新生成矩阵 $B$ ，更新方法是 $B_{ij}=A_{ij}\sum_{k=1}^n\frac{1}{A_{ik}}$ ，例如下面的矩阵为 $A$ ，则 $B_{2,2}=5\times(\frac{1}{4}+\frac{1}{5}+\frac{1}{6})=\frac{37}{12}$ ，请利用 `Numpy` 高效实现。
$$\begin{split}A=\left[ \begin{matrix} 1 & 2 &3\\4&5&6\\7&8&9 \end{matrix} \right]\end{split}$$
```python
def matupdate(m: numpy.ndarray) -> numpy.ndarray:
    return m * (1/m).sum(axis=1, keepdims=True)
  
a = np.arange(1, 10).reshape(3,3)
matupdate(a)
>> array([[1.83333333, 3.66666667, 5.5 ],
		 [2.46666667, 3.08333333, 3.7 ],
		 [2.65277778, 3.03174603, 3.41071429]])
```


### Ex3：卡方统计量
设矩阵$A_{m\times n}$，记$B_{ij} = \frac{(\sum_{i=1}^mA_{ij})\times (\sum_{j=1}^nA_{ij})}{\sum_{i=1}^m\sum_{j=1}^nA_{ij}}$，定义卡方值如下：
$$\chi^2 = \sum_{i=1}^m\sum_{j=1}^n\frac{(A_{ij}-B_{ij})^2}{B_{ij}}$$
请利用`Numpy`对给定的矩阵$A$计算$\chi^2$

```python
def get_chi2(m: numpy.ndarray) -> float:
    _co = m.sum(axis=1, keepdims=True) @ m.sum(axis=0, keepdims=True) / m.sum()
    return numpy.sum((m-_co)**2 / _co)
  
a = np.arange(1, 10).reshape(3,3)
get_chi2(a)
>> 0.46875
```


### Ex4：改进矩阵计算的性能
设$Z$为$m×n$的矩阵，$B$和$U$分别是$m×p$和$p×n$的矩阵，$B_i$为$B$的第$i$行，$U_j$为$U$的第$j$列，下面定义$\displaystyle R=\sum_{i=1}^m\sum_{j=1}^n\|B_i-U_j\|_2^2Z_{ij}$，其中$\|\mathbf{a}\|_2^2$表示向量$a$的分量平方和$\sum_i a_i^2$。
现有某人根据如下给定的样例数据计算$R$的值，请充分利用`Numpy`中的函数，基于此问题改进这段代码的性能。

```python
np.random.seed(0)
m, n, p = 100, 80, 50
B = np.random.randint(0, 2, (m, p))
U = np.random.randint(0, 2, (p, n))
Z = np.random.randint(0, 2, (m, n))
def solution(B=B, U=U, Z=Z):
    L_res = []
    for i in range(m):
        for j in range(n):
            norm_value = ((B[i]-U[:,j])**2).sum()
            L_res.append(norm_value*Z[i][j])
    return sum(L_res)
solution(B, U, Z)
```

```python
def solution(B: numpy.ndarray, U: numpy.ndarray, Z: numpy.ndarray) -> float:
    _co = numpy.expand_dims(B, axis=2) - numpy.expand_dims(U, axis=0)  # (m, p, 1) - (1, p, n) = (m, p, n)
    _co = (_co**2).sum(axis=1).squeeze()  # (m, n)
    return (_co*Z).sum()
  
np.random.seed(0)
m, n, p = 100, 80, 50
B = np.random.randint(0, 2, (m, p))
U = np.random.randint(0, 2, (p, n))
Z = np.random.randint(0, 2, (m, n))
solution(B, U, Z)
>> 100566

%timeit -n 30 solution(B, U, Z)
>> 1.32 ms ± 124 µs per loop (mean ± std. dev. of 7 runs, 30 loops each)
```


### Ex5：连续整数的最大长度
输入一个整数的`Numpy`数组，返回其中严格递增连续整数子数组的最大长度，正向是指递增方向。例如，输入\[1,2,5,6,7\]，\[5,6,7\]为具有最大长度的连续整数子数组，因此输出3；输入\[3,2,1,2,3,4,6\]，\[1,2,3,4\]为具有最大长度的连续整数子数组，因此输出4。请充分利用`Numpy`的内置函数完成。（提示：考虑使用`nonzero, diff`函数）

```python
def get_incre_max(m: numpy.ndarray) -> int:
    _co = numpy.where((numpy.diff(m))!=1, 0, 1)  # 于后非连续, 标记0
    _co = numpy.r_[0, _co, 0]  # 前后加0
    _co = numpy.argwhere(_co==0).reshape(-1)
    return numpy.diff(_co).max()
  
x = np.array([3,2,1,2,3,4,6])
get_incre_max(x)
```

