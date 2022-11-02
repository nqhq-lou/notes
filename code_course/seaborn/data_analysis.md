---
title: data analysis by seaborn
tags: [python/module/seaborn]
---


```Python
seaborn.stripplot(x="lr", y="val_best", data=df, jitter=True)
sns.boxplot(x='day', y='total_bill', data=tips)
```


```Python
fig, axes = plt.subplots(2, 2, figsize=(8,6), sharex=True, sharey=True)  # 共用x轴, 不共用y轴
axes_flat = axes.reshape(-1)  # flatten
metric = "wd"
data_cate = ["train_last", "train_best", "val_best", "test_best"]
fig.suptitle(metric, size=20)
for c, ax in zip(data_cate, axes_flat):
    # seaborn.boxplot(x=metric, y=c, data=df, ax=ax)
    seaborn.stripplot(x=metric, y=c, data=df, ax=ax, jitter=True)
    ax.set_title(c)
plt.ylim(0,20000)
plt.tight_layout()
plt.show()
```







