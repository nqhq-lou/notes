---
title: PowerShell script strategy
tags: [shell/PowerShell, shell/scripts]
---

## script limitations

| scheme       | description                              |
|:------------ |:---------------------------------------- |
| Unrestricted | 权力最高, 没有任何执行限制               |
| Default      | 默认策略, 即Restricted                   |
| Restricted   | 不允许任何脚本执行                       |
| AllSigned    | 所有脚本必须经过签名才能运行             |
| RemoteSigned | 本地脚本无限制, 但是来自网络脚本需要签名 |


To remove the limit on PowerShell executing `ps1` scripts, use `Set-ExecutionPolicy RemoteSigned`

```powershell
执行策略可以防止您执行不信任的脚本。更改执行策略可能会使您面临 about_Execution_Policies帮助主题中所述的安全风险。是否要更改执行策略?
[Y] 是(Y) [N] 否(N) [S] 挂起(S) [?] 帮助 (默认值为“Y”): y
```

