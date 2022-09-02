# C++ Primer的学习笔记

### 命名空间
    ```C++
    #include <iostream>
    #include <string>
    #include <vector>
    using std::cin;
    using std::cout, using std::endl;   // 每个函数都必须有自己的using
    using std::string;
    using std::vector;  // 直接这样写就好
    ```
- 标准库`std`, `string` `vector` `io`都定义在里面
    - `using namespace::name;`
    - 标准库中的名字总能在`std`中找到

### `string`
- 初始化
    ```C++
    string s1;  // 直接
    string s2(s1);  // 括号
    string s3 = s1; // 等号
    string s4("hello");
    string s5 = "hello";
    string s4(5, 'h');  // 次数重复
    ```
    - 带等号: 拷贝初始化
    - `string(10, 'c')`<==>`'cccccccccc'`
    - 存储中, 最后一位之外为`\0`
- 操作
    - `ostream << string`, `istream >> string`
    - `istream getline(istream, string)` 从输入流is读入一行, 返回is
    - `bool s.empty(void)` 为空则返回true
    - `string s[n]` 第n个字符的引用, n从0开始
    - `s1 + s2` s1和s2连接之后的结果(**连接字符串都用这个!**)
    - `s1 = s2`
    - `s1 == s2` `s1 != s2` 字符完全一样, 大小写敏感
    - `<` `<=` `>` `>=` 利用字符的字典序排序
    - `size_type s.size(void)` 字符串长度
        - `size_type`
- 头文件 `cctype`
    - 对字符的处理
    - 字母, 数字, 标点, 空格, 大小写
- tips: 建议使用`cname`格式的头文件, 而不是`name.h`
- 范围`for`
    - for (declaration : expression) {statement}
    - e.g.
    ```C++
    for (auto c : str)  // 对str中的每个字符
        cout << c << endl;
    for (auto &c : str) // 对str中的每个字符, 注意是引用!
        c = toupper(c); // str中每个字母都变大写
    ```
- 字符串下标类型! 为`string::size_type`, 也就是无符号类型

### `vector`
- 初始化
    ```C++
    vector<T> v1;   // 空的
    vector<T> v2(v1);   // v2为v1的副本
    vector<T> v2 = v1;   // 同上, 拷贝
    vector<T> v3(n);   // 初始化n个
    vector<T> v4(n, val);   // val重复n遍
    vector<T> v5{a,b,...};  // 易知
    vector<T> v6 = {a,b,...};   // 易知
    ```
- 操作
    - `v.emplace_back()` / `v.push_back()` 后面添加一个
    - `v.empty()` 如果为空, 返回`true`
    - `v.size()`
    - `v[n]` 第n个的引用
    - `v1 = v2`, `v1 = {a,b,...}`
    - `v1 == v2`, `v1 != v2`
