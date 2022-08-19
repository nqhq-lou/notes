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

```dataview
list
from ""
sort file.name
```


## references
- [obsidian插件之dataview入门](https://www.zhihu.com/people/dawuxiaowu)
- 