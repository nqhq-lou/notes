---
title: python assertion
tags: [python/assertion]
---


- `assert expression[, reason]`
  - 如果`expression==False`, 则`raise AssertationError[reason]`

```Python
try:
    assert 1 == 2, "1 is not equal to 2!"
except AssertionError as reason:
    print("{}: {}".format(reason.__class__.__name__, reason))
    # AssertionError:1 is not equal to 2!
```

- 作用: 代码自我检查

```Python
def non_unique(data):
    return [i for i in data if data.count(i) > 1]
  
if __name__ == '__main__':
    assert non_unique([1,2,3,1,3]) == [1,3,1,3]  # example 1
    assert non_unique([1,2,3,4,5]) == [1,2,3,4,5]  # example 2
    assert non_unique([5,5,5,5,5]) == [5,5,5,5,5]  # example 3
    assert non_unique([10,9,10,10,9,8]) == [10,9,10,10,9]  # example 4
```