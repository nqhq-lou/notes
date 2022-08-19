---
title: PowerShell basics
tags: [shell/PowerShell]
---

## 特性

- 强类型语言, 不考虑大小写
- 不考虑代码中的空格或者制表符
- 分号`;`代表语句结束, 也可以不写
- 行注释: `#`, 块注释: `<#` to `#>`
- 脚本扩展名为: `.ps1`


## 帮助
- `Get-Help`
	- 模糊查询命令: `Get-Command *Process`
	- 查询详细用法: `Get-Help Get-Process -full`
	- 更新文档
		- `Update-Help -UICulture en-US`, 中文为`zh-CN`
- 最后总结


##  变量

```powershell
$a = 1
${"I" like $$} = 5.1

$a.GetType()  # Int32
$a.GetType.FullName  # System.Int32
$a -is [int]  # True
del $a  # del file named 1
del variable:a  # del variable $a

[int] $b = 1.1  # f
orce type
$b  # 1
```

- 强类型语言, 大小写不敏感
- 变量均以`$`开头
	- 特殊变量名称: 用`${xx}`, 如`${"I" like $$} = 5.1`
- 保护变量: `New-Variable num -Value 100 -Force -Option readonly`
	- 只能通过`del $num`删除
- 常量: `New-Variable num -Value 100 -Force -Option constant`
- 变量类型:
	- 整形: byte, sbyte, int16, uint16, int, uint32, long, ulong
	- 浮点: float, double, decimal
	- bool: `$true`, `$false`


## 运算

```powershell
+ - * / %
$i++; ++$i; $i--; --$i  # 和C++完全一致
```


## 数组

```powershell
$array = 1,2,3,4
$array = 1..4  # 两个点
$array=1,"2017",([System.Guid]::NewGuid()),(get-date)  # 数组多态
$a=@()  # 空数组
$a=,"1" # 一个元素的数组

$ip = ipconfig
$ip[1]  # ipconfig第二行的数据

$array -is [array]  # 判断是否是数组
$array += "elem5"  # 追加内容
$array.Count  # 5, 查看公有属性

$array[0..3]  # 切片
$array[0,3,1]  # 切片, 可以不按顺序

$array = $array[0..2] + $array[4..6]  # 相当于删除了 $array[3]

$array2 = $array.Clone()  # 内置方法, 深复制
$array2[2] = -1
$array.Equals($array2)

[int[]] $nums=@(1, 2, "err")  # 强类型数组, 最后一个会报错
```

- 逗号分隔, 不需要括号
- 访问: 通过下标访问
- 任何命令的返回文本为数组, 将会一行一行作为数组元素
- 详细见: [关于数组 from MSFT docs](https://docs.microsoft.com/zh-CN/powershell/module/microsoft.powershell.core/about/about_arrays?view=powershell-7.2)

### 字符串
```powershell
$s = "abcd"
$ss = "new $($s)"  # new abcd
```

## hash表

```powershell
$stu = @{name="test"; age="12"; sex="man"; books="ba","bb","bc"}
$stu = @{}  # 创建空hash表
$stu.name="haha"  # 插入内容
$stu.Remove("Name")  # 删除内容
```

- 详见: [关于hash表](https://docs.microsoft.com/zh-CN/powershell/module/microsoft.powershell.core/about/about_hash_tables?view=powershell-7.2)

## 对象

- `powershell`中一切都可以视为对象
	- `New-Object`创建一个对象, `Add-Member`添加属性方法


## 控制语句

### 条件判断/比较运算符

```powershell
-eq: 等于
-ceq: 敏感等于
-ne: 不等于
-gt: 大于
-ge: 大于等于
-lt: 小于
-le: 小于等于
-contains: 包含

$array -contains something
"a" -eq "A"  # True
"a" -ceq "A"  # False
"a" -is [string]  # True
"a" -isnot [string]  # False

-notcontains :不包含
!($a): 求反
-and: 和
-or: 或
-xor: 异或
-not: 逆
```


### 条件判断

```powershell
if ($value -eq 1) {
    code1
} elseif ($value -eq 2) {
    code2
} else {
	code3
}

$a = "Beijing"
switch($a)  # 必须写大括号
{
	"Beijing" {$res="BJ"}
	"Shanghai" {$res="SHA"}
}

$v=18
switch($v)
{
    {$_ -lt 10} {"小于10"} # $_ 表示当前的传入的变量 直接写的字符串会被输出
    10 {"等于10"}
    {$_ -gt 10} {"大于10"}
}
```


### 循环语句

```powershell
while ($n -gt 0) {
	$n++
    if ($n -eq 10) {
	    continue
	    $n++
    }
    if ($n -gt 20) {
	    break
    }
}

do { 
    $n=Read-Host "请输入数字"
} while($n -ne 0)

$sum=0
for ($i=1;$i -le 100;$i++) {
    $sum+=$i
}
$sum

# 打印该目录下大于1MB的文件名
foreach ($file in dir c:\windows) {
    if ($file.Length -gt 1mb) {
        $File.Name
    }
}

$letterArray = "a","b","c","d"
foreach ($letter in $letterArray) {
	Write-Host $letter
}

$array=1,"2019",([Guid]::NewGuid()),(get-date)
$array | foreach {$_.gettype()}  # $_ 代表遍历到的元素

$ls = ls  # 作为array记录结果
$ls | foreach {$_.Name}  # 正好打印名称

# 获取所有服务, 并对获取进程ID大于
Get-WmiObject Win32_Service | ForEach-Object {"Name:"+ $_.DisplayName, ", Is ProcessId more than 100:" + ($_.ProcessId -gt 100)}

```


## 特殊

```powershell
ls env:  # 环境变量

ls variable:  # 当前变量
del variable:a  # 删除变量 $a

del function:cc  # 删除函数 cc
```

- shell中多行输入: `@' bula bula '@`


## references
- [powershell基础语法 from Zhihu](https://zhuanlan.zhihu.com/p/91860920)
	- basics
- [PS Tips net](https://www.pstips.net/)
	- well-rounded
- [powershell入门指南from Zhihu](https://zhuanlan.zhihu.com/p/76708298)
	- a note of pstips



