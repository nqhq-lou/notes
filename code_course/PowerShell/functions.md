---
title: PowerShell functions
tags: [shell/PowerShell]
---


### 设计逻辑
- 简短: 函数名称简短, 显而易见
- 聚合: 函数可以完成多个操作
- 封装和扩展: 将一批PowerShell语句进行封装, 实现全新的功能要求
- 函数的结构: 函数名, 参数, 函数体
- 谓词verb有选择范围, 见[PowerShell 命令的已批准谓词](https://docs.microsoft.com/zh-CN/powershell/scripting/developer/cmdlet/approved-verbs-for-windows-powershell-commands?view=powershell-7.2)


## 定义函数

- 建议在脚本中写好函数, 然后粘贴到shell中

### 输入

```powershell
function read-name {
	$name = Read-Host "Please input your name"
	$name
}
```

### 输出

```powershell
# 展示带有颜色的信息
Write-Host "very good" -ForegroundColor White -BackgroundColor Red  # 如设置结果

# 将对象发送给管道, PowerShell默认没有指定命令, 就运行Write-Output
Write-Output "ACB"  # 没有空格的字符可以不写引号

# 其他输出方式
Write-Warning/Verbose/Debug/Error
```

- `Write-Output`输出基本过程:
	- `Write-Output`命令将`string`类型的对象`Hello World!`放入管道中
	- 管道中只有这个`string`对象，其会直接到达管道的末端，也就是`Out-Default`命令
	- `Out-Default`命令将对象传递给`Out-Host`命令
	- `Out-Host`命令要求`PowerShell`的格式化系统格式化该对象
	- `Out-Host`将格式化的结果集放在显示界面上


### 万能参数

```powershell
function Add {
    $sum=0
    $args | foreach {$sum=$sum+$_}
    $sum
}

Add 1 2 3 4 10  # 20
```

- `$args`本质是一个数组

### 固定参数

```powershell
function StrCat($str1, $str2) {
	return $str1 + $str2
}

StrCat "hello" "world"  # helloworld
StrCat -str1 "hello" -str2 "world"  # helloworld
StrCat("hello", "world")  # array, not a string

function StrCat($str1="hello", $str2="world") {
	return $str1 + $str2
}
StrCat "hello" "w"  # hellow
StrCat "hello"  # helloworld
StrCat -str2 "hello"  # hellohello
```

### 类型限制

```powershell
function subtract([int]$val1, [int]$val2) {
	return $val1 - $val2
}

subtract 1 a  # sCannot convert value "a" to type "System.Int32".
```

```powershell
function DayOfWeek([datetime]$date) {
	return $date.DayOfWeek
}

DayOfWeek "1927-8-1"  # Monday
DayOfWeek 2008-8-1  # Friday
```

### 多个返回值

```powershell
function MultiRet($i) {
    "$i is $($i)"
    "2*$i is $($i*2)"
    "$i^2 is $($i*$i)"
}
$a = MultiRet 2
$a[-1]  # 2^2 is 4


function lottery([int]$cnt=1) {
    $randgen = New-Object system.random
    for ($i = 1; $i -le $cnt; $i++) {
        $randgen.Next(1, 50)
    }
}
$ret = lottery
$ret.GetType().FullName  # System.Int32
$ret = lottery 10
$ret.GetType().FullName  # System.Object[], 根据返回值, 类型不同
```

### `return`语句

```powershell
function test($num) {
	1
	9
	return 10
	7
}
test  # 1, 9, 10
```

### 输出过滤

```powershell
function test() {
	Write-Host "Try to calculate"  # 运行函数时输出
	"3.1415926"  # 返回值
	Write-Host "Done"  # 运行函数时输出
	"with return val pi"  # 返回值
}

$val = test  # the two sentences
$val  # 3.1415926, with return val pi
```

- 有时不需要很多输出, 于是可以使用`Write-Host`指定输出内容

