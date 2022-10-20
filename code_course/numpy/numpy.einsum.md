


## usage

- vectors
	- ![einsum_vectors](https://pic1.zhimg.com/80/v2-a626e7d59c489670a5eefda09679bfa4_1440w.webp)


- 2D matrixes
	- ![einsum_matrixes](https://pic2.zhimg.com/80/v2-42c4a13d58085c0a69b03a50f0e41e0d_1440w.webp)



## benchmark

### vector outer
```Python
a = np.arange(4)
b = np.arange(6)
%timeit -n 1000 np.einsum("i,j->ij", a, b);
%timeit -n 1000 a[:,np.newaxis] * b[np.newaxis,:];
%timeit -n 1000 np.outer(a, b);
>>> 27.7 µs ± 6.03 µs per loop (mean ± std. dev. of 7 runs, 1,000 loops each)
>>> 1.69 µs ± 96.6 ns per loop (mean ± std. dev. of 7 runs, 1,000 loops each)
>>> 2.3 µs ± 55.1 ns per loop (mean ± std. dev. of 7 runs, 1,000 loops each)

a = np.arange(400)
b = np.arange(600)
%timeit -n 1000 np.einsum("i,j->ij", a, b);
%timeit -n 1000 a[:,np.newaxis] * b[np.newaxis,:];
%timeit -n 1000 np.outer(a, b);
>>> 311 µs ± 46.1 µs per loop (mean ± std. dev. of 7 runs, 1,000 loops each)
>>> 350 µs ± 41.9 µs per loop (mean ± std. dev. of 7 runs, 1,000 loops each)
>>> 292 µs ± 48.3 µs per loop (mean ± std. dev. of 7 runs, 1,000 loops each)

a = np.arange(4000)
b = np.arange(6000)
%timeit -n 100 np.einsum("i,j->ij", a, b);
%timeit -n 100 a[:,np.newaxis] * b[np.newaxis,:];
%timeit -n 100 np.outer(a, b);
>>> 157 ms ± 25.5 ms per loop (mean ± std. dev. of 7 runs, 100 loops each)
>>> 131 ms ± 4.04 ms per loop (mean ± std. dev. of 7 runs, 100 loops each)
>>> 156 ms ± 22.6 ms per loop (mean ± std. dev. of 7 runs, 100 loops each)
```




## references

- [einsum初探](https://zhuanlan.zhihu.com/p/101157166)