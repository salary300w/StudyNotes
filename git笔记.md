- [git笔记](#git笔记)
  - [基础命令](#基础命令)
  - [子模块](#子模块)
# git笔记
## 基础命令
|命令|作用|
|:---:|:---:|
|`git init`|git获取目录管理权限|
|`git status`|查看本地库状态|
|`git rm --cached <file name>`|删除暂存区的文件（不影响工作区）|
|`git reflog`|查看版本信息|
|`git log`|查看详细版本信息|
|`git reset --hard 版本号`|穿梭到指定版本号的版本|
|`git branch 分支名`|以当前分支为基础创建分支|
|`git branch -v`|查看分支|
|`git branch -D 分支名`|删除分支|
|`git checkout 分支名`|切换分支|
|`git checkout -b 分支名`|以当前分支为基础创建分支|
|`git merge 分支名`|把指定分支合并到当前分支上|
|`git remote -v`|查看当前远程地址的别名|
|`git remote add 别名 链接`|给对应的远程库链接创建别名，默认为origin|
|`git push`|将代码推送至远程仓库|
|`git push --set-upstream origin 分支名`|远程仓库没有当前分支时，将代码推送至远程仓库|
## 子模块
|命令|作用|
|:---:|:---:|
|`git submodule add url`|将`url`表示的仓库添加为正在工作的仓库的子模块|
|`git clone --recurse-submodules url`|同时克隆`url`表示的项目，以及该项目嵌套的子模块|
|`git submodule update --init`|克隆当前项目所需要的子模块|