---
title: git remove all commit
tags: [git]
---


```bash
git checkout --orphan latest_branch  # 新建空白分支
git add -A  # 添加所有文件
git commit -am "."  # 简单提交一下
git branch -D main  # 强制删除旧分支，分支名称为main
git branch -m main  # 将当前分支重命名为main
git push -f origin main  # 强制推送到远程仓库
```