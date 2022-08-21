---
title: git tips
tags: [git]
---

### remove current `main` branch

```bash
git checkout --orphan latest_branch  # 新建空白分支
git add -A  # 添加所有文件
git commit -am "."  # 简单提交一下
git branch -D [branch_name]  # 强制删除旧分支
git branch -m [branch_name]  # 将当前分支重命名为branch_name
git push -f origin main  # 强制推送到远程仓库
```


### remove remote file/folder

```python
git rm -r -n --cached [files/folders]  # -n 预览要删除的文件列表而不是删除
git rm -r --cached [files/folders]  # 进行删除
git commit -m "..."  # 提交
git push origin [branch_name]  # push
```






