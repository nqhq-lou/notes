---
title: about lightning global_step and current_epoch
tags: [pytorch/lightning]
---

## `global_step`

- `global_step` refers to the number of optimizer steps applied. It takes the initial value of 0 (because 0 steps have been applied to the optimizer).
- Any of the previous hooks can `self.log()`. These `self.log()` calls use the `global_step` value as the x-axis (if you were to plot it)

## `current_epoch`

- 



## references
- [global_step / current_epoch issue from GitHub](https://github.com/Lightning-AI/lightning/issues/7406)