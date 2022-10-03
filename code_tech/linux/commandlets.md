---
title: commandlets in linux
tags: [Linux/cmd]
---

## grep

[generals on regex](https://www.runoob.com/linux/linux-comm-grep.html)
[use regex in grep](https://phoenixnap.com/kb/grep-regex)

` ps aux | sort -rnk 4 | head -5 | grep '^[[:alnum:] +./:]\+[0-9]\+:[0-9]\+' -o`



## tar

https://cloud.tencent.com/developer/article/1404921


## find & xargs

- delete by type
	- `find -type f | xargs rm -f`
- delete by user
	- `find -user [usrname] | xargs rm -f`



## awk


