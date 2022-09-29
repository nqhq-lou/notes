---
title: dataset sGDML
tags: [physics/solidstate/datasets, AI4Science/datasets]
---

## website
- [sGDML datasets](http://www.sgdml.org/#datasets)


## content inspect
```python
d = numpy.load("benzene/{fname}.")
print(d['name'])
for k in d.files:
    print(k, d[k].shape)
    if len(d[k].shape) <= 1:
        print(d[k])
    print()
```

- `benzene_ccsd_t-train.npz`
	- E = energy
	    - shape (1000,1)
	- name = name
	    - content 'benzene_ccsd'
	- F = force?
	    - shape (1000, 12, 3),
	- theory = theory
	    - content 'Psi4: CCSD(T), cc-pVDZ'
	- R = coordinate?
	    - shape (1000, 12, 3)
	- z = nuclear charge
	    - shape = (12,)
	    - content = `[6 6 6 6 6 6 1 1 1 1 1 1]`
	- type = ???
	    - content 'd'
	- md5
	    - content 'ea95280ad146d16439c1326a4df0e260'
- 可以看到原子并不在同一
- `benzene_ccsd_t-test.npz`
	- sample cnt = 500



