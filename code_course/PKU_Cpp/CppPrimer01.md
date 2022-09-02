# C++ Primer的学习笔记

### 开始
- 输出/输入运算符 `<<`/`>>`
- 注释`/* */`不能搞套娃
- `while (condition) {statement}`
    - `while (std::cin >> value)`不断读入, 直到无效输入, 注意`cin`的返回值
- `for (init-statement; condition; expression) {statement}`

### 变量和基本类型
- 算数类型
    ```C++
    cout << "bool\t\t" << sizeof(bool) << endl;
    cout << "char\t\t" << sizeof(char) << endl;
    cout << "wchar_t\t\t" << sizeof(wchar_t) << endl;
    cout << "char16_t\t" << sizeof(char16_t) << endl;
    cout << "char32_t\t" << sizeof(char32_t) << endl;
    cout << "short\t\t" << sizeof(short) << endl;
    cout << "int\t\t\t" << sizeof(int) << endl;
    cout << "long\t\t" << sizeof(long int) << endl;
    cout << "long long\t" << sizeof(long long int) << endl;
    cout << "float\t\t" << sizeof(float) << endl;
    cout << "double\t\t" << sizeof(double) << endl;
    cout << "long double\t" << sizeof(long double) << endl;
    ```
    ```C++
    bool		1
    char		1
    wchar_t		4
    char16_t	2
    char32_t	4
    short		2
    int		4
    long		8
    long long	8
    float		4
    double		8
    long double	16
    ```
- 字面值常量
    - `24`十进制, `024`八进制, `0x24`十六进制
    - `\`, `\0`, `\x`转义
    - `u U L u8`前缀->字符(串)
    - `u U l L ll LL`后缀->整形
    - `f F l L`后缀->浮点型
    - `true` `false`布尔字面值
    - `nullptr`指针字面值
- 声明变量, 而不定义
    - 在一个程序中使用别的程序定义的名字
    - `extern int i`声明`i`的存在, 之后才能使用
    - `extern int i = 3`不是声明! 是定义
- 标识符 identifier
    - 字母+数字+下划线
    - 数字不能开头, 长度没有限制, 大小写字母敏感
- 作用域 scope
    - 大都以`{}`花括号为限制
        - main在`{}`外, 有全局作用域
        - `{}`内为块作用域
- 引用(此处指 左值引用)
    - 即别名, 定义时必须初始化, 将之与初始值绑定在一起 bind
    - e.g. `int &refVal = ival;`
- 指针
    - 指针存放某个**对象**的地址, 取地址符`&`, 解引用符`*`
    - 指针的类型需要与对应对象的类型一致
    - e.g. 指向对象`int *p = &ival`, 访问对象`cout << *p`
    - 指针的四种状态
        - 指向一个对象
        - 指向紧邻对象所占空间的下一个位置
        - 空指针
        - 无效指针(即不同于上面任何状态)
    - 空指针 = `0`, `nullptr`, `NULL`
    - `void*`: 一种特殊类型指针, 可以存放任意对象的地址
        - 仅仅储存地址, 无法访问内存空间中对应的对象
    - **注意!!!**
        - `int* p1, p2;`p1为指针`int*`, p2为`int`!!
        - `int *p1, *p2;`两个均为指针`int*`
- 指针和引用
    - 指针的指针: 需要两次解引用
    ```C++
    int ival = 1024;
    int *pi = &ival;
    int **ppi = &pi;
    cout << ival << *pi << **ppi << endl;
    ```
    - 指向指针的引用
        - 引用本身不是一个对象, 因此不能定义 指向引用的指针
        - 但是指针是对象, 因此可以定义 对指针的引用
    ```C++
    int ival = 1024;  int *p;  int *&r = p;
    // r是一个指针类型的引用, 因此是*&
    r = &i;  *r = 0;    // 将i修改为零, 此时p r均指向i的地址
    ```
- `const`限定符
    - `const`对象仅在文件内有效
    - 如果想在多个文件之间共享`const`对象, 必须在变量的定义之前添加`extern`关键字
- 常量引用`const type&`
    - 常引用不能修改所绑定的对象
    ```C++
    int i = 42;
    const int &r = i;
    r = 0;  // 错误, r为一个常量引用, 不能通过r修改i
    i = 0;  // 正确, i可以被直接修改
    ```
    - 非常引用不能引用常量对象
    - 区分
        - 对`const`的引用: 常量引用
            ```C++
            const int ci = 1024;
            const int &ri = ci; // 正确, 常量引用
            int &r2 = ci;   // 错误, 非常量引用不可引用常量对象
            ```
            - 即, 需要生成一个`const int`类型的`&`进行引用
        - 一个`const&`引用: 引用常量(实际上不存在, 因为引用不是一个对象, 因此不能称之为常量)
            - 因此, 引用常量不存在, 代码出错
- 常量和指针
    - 指针常量: 指向常量的指针
        ```C++
        const int ci = 1024;
        int *pi = &ci;          // 错误, pi不能指向常量
        const int *cpi = &ci;   // 正确, 指针常量
        const double *const ccpi = &ci; // 正确, 但是ccpi中存储的地址不能再改变
        ```
        - 即, 需要一个`const int*`类型的指针, 指向`const int`型
    - 常量指针: 指针本身定义为常量
        ```C++
        int i = 1024;
        int *const pi = &i; // 之后不能修改pi的值
        ```
- 顶层/底层`const`
    - 顶层`const`: 指针本身是个常量
        - 影响较小
    - 底层`const`: 指针所指对象是常量
        - 拷贝时拷入和拷出的对象必须具有相同的底层`const`资格, 或非常量可以转化为常量
- `constexpr`和常量表达式
    - 常量表达式: 值不会改变并且在编译过程中就能得到计算结果的表达式
        - 值不变, 编译可得计算结果
    - `constexpr`: C++11, 允许将变量声明为`constexpr`类型, 以便由编译器验证变量的值是否是一个常量表达式
        - 指针和引用可以定义为`constexpr`, 但是收到严格限制, 略
- 处理类型
    - 类型别名
        - `typedef`
        ```C++
        typedef double wage;    // wage和double是同义词
        typedef wage base, *p;  // base和double是同义词, p是double*
        ```
        - `using`
        ```C++
        using SI = Sales_item;  // SI和那个是同义词
        ```
        - `关于指针`
        ```C++
        typedef char *pstring;  // pstring是char*的别名
        const pstring cstr = 0; // cstr指向char, 是常量指针(不是指针常量!)
        // <==> char *const cstr;
        const pstring *ps;      // 指针ps的对象是指向char的常量指针
        ```
    - `auto`类型
        - 编译器自行判断表达式类型, 自己定义的class也可以
            ```C++
            auto i = 0, pi = 3.14;
            Sales_item val;
            auto item = val;    // 自动判断为Sales_item类型
            ```
        - 和`const`的关系: 还挺复杂的, 略
    - `decltype` = declared type
        - 选择并返回操作数的数据类型
            ```C++
            int i = 0;
            decltype(i) d;  // d为int类型
            decltype(f()) sum = x;  // sum的类型为f()返回值的类型
            ```
        - 返回的类型包括: 顶层`const`和引用
            ```C++
            int i = 0, *p = &i, &r = i; // p为指向int*
            decltype(r + 0) = b;    // b的类型为int
            decltype(*p) c;     // 错误, c为 int&(为什么??)
            decltype((i)) d;    // 错误, d为 int&(因为加括号了)
            decltype(i) e;      // 正确, e为 int
            ```
- 头文件
    - 隐式包含头文件
    - 头文件保护符 header guard
        ```C++
        // 头文件名称为 sales_item.h, 推荐写成下面的样子
        #ifdef SALESITEM_H
        #define SALESITEM_H
        // 添加东西
        #endif
        ```
