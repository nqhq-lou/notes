---
title: basics args of PowerShell on Windows
tags: [Windows/maintenance, shell/Powershell]
---

## Intro
- 众所周知, Windows系统很通用, 但是很垃圾
- 希望总结一下如何保养

## 修复
- 设置系统还原点
- 管理员powershell
    - `Dism /Online /Cleanup-Image /ScanHealth`
        - 检查与官方文件是否一致
    - `Dism /Online /Cleanup-Image /CheckHealth`
        - 检查能否修复
    - `Dism /Online /Cleanup-Image /RestoreHealth`
        - 尝试修复
        - 好像不会用很久, 自己的电脑用了4min就好了



# Windows Shell Basic
- Windows是`\`==!!!!!!!!!!==
- Linux是`/`

## 基础
- 位于`C:\Windows\System32`下的文件直接运行
- 调用操作: 路径种有空格
    - `& 'C:\Program Files\Perl'`
- 运行当下目录: `.\`
    - `.\test.exe`
    - `& '.\test folder\test.exe'`
- `Tab`补全

## PowerShell 命令
- 命令具有别名
- 强大功能: `cmdlet`
    - 命令规则都是: `动词-名词`
- `Get-Command`, `Get-Content`
- `Get-Command`
    - `Get-Command -Name *Process`
        - 查找以`Process`结尾的命令
- `Get-Help`
    - `Get-Help Get-Command`
        - 查找命令用法
- `Out-File`: 重定向输出
    - `ls | Out-File ls.log`
- 查看文件
    - `ls | Format-List` 显示
        - Name, Length
        - CreationTime, LastWriteTime, LastAccessTime
        - Mode, LinkType, Target, VersionInfo
    - `ls | Format-Table Name,Length`
## 脚本
- 记录PowerShell全文会话
    - 


## references
- [25个常用PowerShell命令总结](https://www.jb51.net/article/56237.htm)
- [为 Windows PowerShell 设置 alias](https://blog.csdn.net/lei_qi/article/details/106592404)