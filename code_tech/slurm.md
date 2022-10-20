---
title: slurm tricks
tags: [cluster/slurm]
---




## common args

```bash

# start jupyter
srun -p ai4science --cpus-per-task=16 --gres=gpu:1 jupyter notebook --ip='0.0.0.0' --port=10024 --allow-root


# use cpu
srun -p cpu -N1 -c96 --quotatype --async --kill-on-bad-exit=1 bash run-inputs.sh

# check virtual partition info
cinfo -p [vpname]
```

- [srun](http://sdoc.pjlab.org.cn:10099/docs/phonex-slurm/user-guide/srun.html?highlight=srun)
- 



## debug
- [debug on slurm](https://medium.com/@tony.littlewine/remote-debugging-with-gpus-in-distributed-slurm-compute-clusters-948b32234daa)
- [more1](https://github.com/microsoft/vscode-remote-release/issues/1722#issuecomment-718246436)



