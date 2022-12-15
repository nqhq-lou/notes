---
title: dataview manual
tags: [manual/dataview]
---

```dataview
list
from "code_tech"
where
contains(file.tags, "PowerShell")
sort file.ctime
```


```dataview
table tags, title
from "code_tech"
sort file.ctime
```

```Python
	```dataview
	list
	from ""
	sort file.name
	```


## references
- [obsidian插件之dataview入门](https://www.zhihu.com/people/dawuxiaowu)
- [add task checker](https://forum.obsidian.md/t/progress-bar-for-incomplete-total-tasks/30744)