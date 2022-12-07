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


### change remote
- https://careerkarma.com/blog/git-change-remote/

```
git remote set-url origin git@github.com:Career-Karma-Tutorials/git-submodule.git
```



## full tips after creating a project

```bash
### Command line instructions

You can also upload existing files from your computer using the instructions below.

##### Git global setup

git config --global user.name "louzekun"
git config --global user.email "louzekun@pjlab.org.cn"

##### Create a new repository

git clone ssh://git@github.com/ai4science/gnnxc.git
cd gnnxc
git switch -c main
touch README.md
git add README.md
git commit -m "add README"

##### Push an existing folder

cd existing_folder
git init --initial-branch=main
git remote add origin ssh://git@github.com/ai4science/gnnxc.git
git add .
git commit -m "Initial commit"

##### Push an existing Git repository

cd existing_repo
git remote rename origin old-origin
git remote add origin ssh://git@github.com/ai4science/gnnxc.git
```


for pjlab, `ssh://git@gitlab.pjlab.org.cn:1122/louzekun/gnnxc.git`


