---
title: PowerShell object
tags: [shell/PowerShell]
---

## 创建对象

```powershell
$obj = [object]@{1=1; 2=2; 3=3}
$obj
<#
Name                           Value
----                           -----
3                              3
2                              2
1                              1
#>
```

```powershell
function Test-Object {
  $ModuleName = "PSScheduledJob"
  $HelpCulture = "en-us"
  $HelpVersion = "3.1.0.0"
  [PSCustomObject]@{
    "ModuleName"=$ModuleName
    "UICulture"=$HelpCulture
    "Version"=$HelpVersion
  }
  $ModuleName = "PSWorkflow"
  $HelpCulture = "en-us"
  $HelpVersion = "3.0.0.0"
  [PSCustomObject]@{
    "ModuleName"=$ModuleName
    "UICulture"=$HelpCulture
    "Version"=$HelpVersion
  }
}
Test-Object
<#
ModuleName        UICulture      Version
---------         ---------      -------
PSScheduledJob    en-us          3.1.0.0
PSWorkflow        en-us          3.0.0.0
#>
```

```powershell
## Define the hashtable
$sampleHashtable = @{
    ID = 1;
    Shape = "Square";
    Color = "Blue";
}
## Create an object
$ShapeObject = [PSCustomObject]$sampleHashtable
Write-Output $ShapeObject
  
# $ShapeObject = New-Object -TypeName PSObject -Property $sampleHashtable
# Write-Output $ShapeObject
  
$ShapeObject = $ShapeObject | Add-Member -MemberType NoteProperty -Name "Side" -Value 4
Write-Output $ShapeObject
```

## references
- [关于对象 from MSFT docs](https://docs.microsoft.com/zh-CN/powershell/module/microsoft.powershell.core/about/about_objects?view=powershell-7.2)
- [对象=属性+方法 from PStips](https://www.pstips.net/powershell-object-contains-properties-and-methods.html)
- [Add Properties to Objects in PowerShell from DelftStack](https://www.delftstack.com/howto/powershell/adding-properties-to-objects-using-powershell/)
- 