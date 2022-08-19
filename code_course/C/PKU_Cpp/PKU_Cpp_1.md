# PKU Cpp from bilibili

## 命令行

###  命令行使用
`$ notepad filename`

`$ copy file1 file2`



## 命令行参数

```C
int main(int argc, char *argv[]) {
    return 0;
}
```
`argc`: 命令行参数的个数, 至少是1, 因为程序本身文件名也算一个命令行参数

`argv[]`: `argv[] = "filename"`

命令行参数内部有空格: `"Hello World!"` 用双引号括起来

## 位运算

- `n = n & 0xffffff00` == `n &= 0xffffff00` 把`n`的低八位变成零, 高位不变
- `(n & 0x80) != 0x80` 判断`n`的第七位是否为0
- `n |= 0xff` 把`n`的低八位全部变1, 高位不变
- `n ^= 0xff` 把`n`的低八位取反, 高位不变
- `~n` 按位非, 0 1交换
- 不引入临时变量, 交换两个变量的值:
    ```C
    int a = 5, b = 7;
    a = a ^ b;
    b = b ^ a;
    a = a ^ b;
    ```
- `a << b` 左移运算, 将`a`各二进位全部左移`b`位
    - 高位丢弃, 低位补`0` (等价于乘$2^n$)
- `a >> b` 右移运算, 将`a`各二进位全部右移`b`位
    - 对有符号数(包括`char`), 高位为`1`, 高位同样右移, 高位补`1`; 高位为`0`, 高位补`0`
    - `-25 >> 4`: `-25 = -1110 0111` -> `-1111 1110 = -2`
    - `25 >> 4`: `25 = 0001 1001` -> `0000 0001 = 1`
    - `-2 >> 4`: `-1`



## 引用

- 某个变量的引用, 等价于自己这个变量, 相当于此变量的一个别名.
    ```C
    int c = 5;
    int & r = n;
    ```
    - 定义引用的时候记得初始化
    - 不要改变引用的对象
    - 不能引用常量和表达式
    - 注意, 有'引用的引用'
    - 指针和引用的对比
    <details>
    <summary>可收缩代码示例</summary>

    ```C++
    // pointer
    void swap(int *a, int *b) { // 设置指针接收地址
        int tmp;
        tmp = *a;   *a = *b; *b = tmp;
    }
    int n1, n2; swap(&n1, &n2); // 输入地址
    ```
    ```C++
    // revalue
    void swap(int &a, int &b) { // 设置引用
        int tmp;
        tmp = a;    a = b;  b = tmp;
    }
    int n1, n2; swap(n1, n2);
    ```
    ```C++
    // 函数调用的返回值可以是引用, 看起来 很 强 的 样 子
    int n = 4;
    int &setValue() {return n;}
    int main() {
        setValue() = 40;// 对函数调用返回的结果n进行赋值
        cout << n;      // 输出 40
        return 0;
    }
    ```
    </details>

- 常引用: 类型名称为`const type &`
    - 不能通过常引用去修改其引用的内容, '只读'的引用
    ```C++
    int n = 100;
    const int & r = n;
    r = 200;    // 编译报错
    n = 300;    // 没问题
    ```
- 常引用和非常引用
    - `const type &` `const type`不可以被引用
    - 除非进行强制类型转换



## `const`关键字和常量

- 定义常量
    - `const char *SCHOOL_NAME = "Peking Univs."`
    - 多用`const`, 少用`#define`, `const`可以确定是什么类型, 方便后续进行
- 定义常量指针
    - 不可通过常量指针修改其指向的内容
    ```C++
    int n, m;
    const int *p = &n;  // p 指向 n 的地址
    *p = 5;     // error 取 p 的内容进行修改,
    n = 5;      // pass 应该这样修改
    p = &m;     // pass 改变常量指针指向内容, 允许!
    ```
    - 不能把常量指针赋值给非常量指针, 反过来可以
    ```C++
    const int *p1;  int *p2;
    p1 = p2;    // pass
    p2 = p1;    // error
    p2 = (int*)p1;  // pass 强转
    ```
- 常引用: 类型名称为`const type &`
    - 不能通过常引用去修改其引用的内容, '只读'的引用
    ```C++
    int n = 100;
    const int & r = n;
    r = 200;    // 编译报错
    n = 300;    // 没问题
    ```
- 定义指针常量
    - 不可更改指向, 可以更改指向内容
        ```C++
        int n, m;
        int *const p = &n;  // const p 指向 n 的地址
        *p = 5;     // pass
        p = &b;     // error 不允许修改指向内容
        ```



## 动态内存分配
- 复习一下
    - `&x`取`x`的地址, 是指针类型的表达式
    - `*x`取指针`x`对应的内容, 是变量类型的表达式
- `new`实现
    - `new type`返回值都是`*type`, 也就是这个类型的指针
    - 分配一个变量`p = new type`, 动态分配出`sizeof(type)`, 空间起始地址给`p`
        ```C++
        int *p;
        p = new int;    // 为此指针分配内存
        // int *p = new int;
        *p = 5;
        delete p;
        delete p;   // error 不能被删除多次, 但可以编译
        ```
    - 分配一个数组`p = new type[N]`, 动态分配出`N*sizeof(type)`, 空间起始地址给`p`
        - `N`是整形表达式
        ```C++
        int *pn, N = 5;
        pn = new int[2*N];
        // int *pn = new int[2*N]
        pn[0] = 5;  pn[10] = 10;    // 编译通过, 运行时数组越界
        delete []p;
        ```
- `delete`释放已分配的空间
    - `delete`***必须***指向`new`出来的空间!
    - `delete []`***必须***指向`new`出来的***数组***!
    - 如果不回收, 就不会被利用, 占用资源.



## 内联函数, 函数重载, 函数缺省参数
- `inline`内联函数 (可以重复调用)
    - 编译器处理内联函数, 将整个函数的代码插入到调用语句中, 不会产生调用函数的语句
        - 调用函数的语句: 函数地址, 传递参数, 提返回值
        - 函数调用浪费时间 (如果函数本身比较小, 就很浪费)
    ```C++
    inline int max(int a, int b) {
        if (a > b)  return a;
        return b;
    }
    ```
    - 不好的地方: 编译出来的程序体有可能比不内联大, 因为不清楚调用函数和内联函数哪个更大.
- 函数重载 (函数重名)
    - 函数名字相同, 而**参数个数**和**参数类型**不相同, 叫函数重载. 编译器根据语句中的参数个数/类型判断该调用哪个函数.
        ```C++
        int max(double f1, double f2);
        int max(int n1, int n2);
        int max(int n1, int n2, int n3);
        max(3,2.4); // error 二义性, 编译器报错
        ```



## 函数缺省参数
- 定义函数的时候, 让最右边的连续若干个参数有缺省值. 调用函数时, 在相应位置不写参数, 参数就是缺省值
    ```C++
    void func(int x1, int x2 = 2, int x3 = 3) {}
    func(10);   // == func(10, 2, 3);
    func(10, 8);    // == func(10, 8, 3);
    func(10, , 8);  // 不行, 只能最右边连续若干个参数缺省
    ```
- 目的在于提高程序的可扩充性. 前期就为后期参数的扩充做准备.













