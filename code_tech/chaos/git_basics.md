---
title: git basics
tags: [software/git]
---

# Git 入门

## 逻辑
- ![Git的逻辑](https://github.com/neolee/wop-ecnu-pub/raw/d93a56cf3b6cb317585433ed7a6d60efda6a5bc9/assets/git-states.png)
- 工作区, working directory
  - PC资源管理器中能够看到的目录
- 版本库, repository
  - `.git`文件夹
- 暂存区, stage
  - `add`或者modify, 但是`commit`之前的内容

## 初始化配置
- 君の名字
  - `git config --global user.name "<your name>"`
- 君の電郵
  - `git config --global user.email your_email@foo.bar`
- 对git进行文档书写时的编辑器
  - 如果不熟悉`vim`, 可以使用VSCode
    - `git config --global core.editor "code -w"`
    - `-w`的意思是, code关闭前占用命令行. (以免进行不安全的操作)
  - 熟悉`vim`: `git config --global core.editor "vim"`
- 还想看看都能配置什么?
  - `git config --list`

## 第一次`init`
- `init`
  - `shell`里的当前目录就是工作目录
- `status`
  - 查看现在 working dir 出来的文档的状况
  - 会显示出来: new, modified, untracked
- `add <paths_or_files>`
  - 将(目录下的)文件加入 staging area 中
- `commit`
  - 将 stage area 的内容提交到 repo
  - 这个时候会打开一个文档, 需要在这个文档里写对本次commit的描述
  - 保存文档并退出之后, 就commit成功了
- `tag <tag>`
  - 给最新的 commit 加 tag, 方便后续追踪
  - `tag <tag> <commit id>`: 给这个`id`加tag
  - 删除tag: `git tag -d <tag>` (因为tag不重复, 所以直接删除即可)
  - 注意!!: tag是给commit的, 不是给branch的!
- `log`
  - 显示之前所有提交内容: 编号(`commit id`), (`tag`s), 作者日期, 描述
  - 编号的前几位用于区分这个(至少4位)
- `checkout <tag/id>`
  - 切换到这个版本

## 工作流程
- 从`commit`中创建`branch` (提取文件到工作区)
- 对这个`branch`的文件进行修改
  - `add`和modify, 实际上都是从将新的内容提交到`stage area`
  - 等到`commit`之前, 这些内容都在`stage area`
- 对`branch`进行`commit`

## `branch`: 分支
- `HEAD`: 指针
  - 指针指向的内容, 是当前可以查看的内容
  - 指针可以不指向stage区哦
  - 指针可以指向`commit`或者`branch`
  - `switch --detach <id/tag>`: 切换这个commit但是不创建分支
    - `switch -d <id/tag>`
- `branch`: 分支
  - `switch -c <brName> <id/tag>`: 给这个commit创建分支并且, 切换到这个分支
    - 如果`<id/tag>`缺省, 则默认给当前branch/commit创建分支
  - `git switch -`: 切换回上一个所在的分支

## `restore`: 恢复
- 对`stage`进行恢复
  - `git restore -s [file]`
    - 将`stage`的`[file]`恢复为工作区的内容
    - 修改过的内容将会变为untracked
  - `git restore -s .`
    - 将整个文件夹恢复为work dir
    - 修改的文件将会变为untracked
  - `git restore [file]`
- 文件在暂存区且未作修改的情况
  - `git restore --staged <file>`
    - 把文件从暂存区移动到工作区，即文件不被追踪；
- 文件在暂存区且已经修改的情况
  - 使用`git restore --staged <file>`
    - 把文件从暂存区移动到工作区，且不会撤销修改的内容
  - 使用`git restore <file>`
    - 文件仍在暂存区且会撤销文件修改的内容；

## 关于github

### 我想要star


### personal token



### 第一次push



## 参考文献
- [Git与Github入门 from neolee](https://github.com/neolee/wop-ecnu-pub/blob/master/x3-git-github.ipynb)

