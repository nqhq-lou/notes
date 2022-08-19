---
title: PowerShell get WMI objects, Get-CimInstance
tags: [shell/PowerShell]
---

- Windows Management Instrumentation (WMI) 是 Windows 系统管理的核心技术, 因为它以统一的方式公开大量信息.


### 获取WMI的win32 classes

```powershell
$win32classes = Get-CimClass -Namespace root/CIMV2 | Where-Object CimClassName -like Win32* | Select-Object CimClassName
$win32classes.Count  # 781
```





## references
- [获取WMI对象 from MSFT docs](https://docs.microsoft.com/zh-cn/powershell/scripting/samples/getting-wmi-objects--get-ciminstance-?view=powershell-7.2)
- 