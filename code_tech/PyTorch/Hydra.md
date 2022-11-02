---
title: Hydra intro
tags: [python/module/Hydra]
---


## general ideas
- former configs could be overwritten by later configs
- The param structure is actually OmegaConf
- Hydra config experiment lazily
	- which means that the sweep experiment might be compacted if configs and python code are changed.



## lightning-hydra-template

- to notice
	- sweep by hydra or optimize metrics by Optuna
	- easy distributed training





## run

```bash
python run.py [group].[entry]=[value]  # change specific value
python run.py +[group]=[option]  # add a config group
python run.py ++[group]=[option]  # override a config value if it's already in the config, or add it otherwise
python run.py ~[group]  # remove group

python run.py -m [group]=[op1,op2,...]  # --multirun == -m

python run.py hydra.output_subdir=null  # disable .hydra to record yaml
```


## multirun

- parameters labeled in the last place is iterated first




## dir status

```python
from hydra.utils import get_original_cwd, to_absolute_path  
  
@hydra.main()  
def my_app(_cfg: DictConfig) -> None:  
print(f"Current working directory : {os.getcwd()}")  
print(f"Orig working directory : {get_original_cwd()}")  
print(f"to_absolute_path('foo') : {to_absolute_path('foo')}")  
print(f"to_absolute_path('/foo') : {to_absolute_path('/foo')}")  
  
if __name__ == "__main__":  
	my_app()
```

```bash
Current working directory : /Users/omry/dev/hydra/outputs/2019-10-23/10-53-03  
Original working directory : /Users/omry/dev/hydra  
to_absolute_path('foo') : /Users/omry/dev/hydra/foo  
to_absolute_path('/foo') : /foo
```


## logging
- I prefer `hydra/job_logging=disabled` and `verbose`







## references
- [Hydra docs](https://hydra.cc/docs/intro/)
