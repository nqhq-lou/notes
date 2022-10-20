---
title: OmegaConf intro
tags: [python/module/OmegaConf]
---


## create

### yaml format
- `.` dot for depth

### `dataclass` format
- `dataclass` is a class to organize params with order
```python
@dataclass
class MyConfig:
	port: int = 80
	host: str = "localhost"

conf = OmegaConf.structured(MyConfig)
print(OmegaConf.to_yaml(conf))
# port: 80
# host: localhost

conf = OmegaConf.structured(MyConfig(port=443))
print(OmegaConf.to_yaml(conf))
# port: 443
# host: localhost
```


## runtime


## references
- [readthedocs for OmegaConf](https://omegaconf.readthedocs.io/en/latest/)