# PKU Cpp from bilibili

## 友元 Friend
- 友元函数, 友元类
    - 友元关系不能继承, 不能传递

## `this`指针
- C++到C的翻译
- 作用: 指向成员函数所指向(属于)的对象
    - 静态成员函数中不可使用`this`, 因为是无主的指针
<!-- <details>
<summary>可收缩代码示例</summary> -->

```C++
    class Complex {
        private:
            double real, imag;
        public:
            Complex(double r, double i)
                : real(r), imag(i) {}
            void Print() {
                cout << real << "+" << imag << "i" << endl;
            }
            Complex AddOne() {
                this->real++;
                this->Print();
                return *this;
            }
    };
    int main() {
        Complex c1(1,1), c2(0,0);
        c2 = c1.AddOne();
        return 0;
    }

```

<!-- </details> -->

## 常量对象, 常量成员函数, 常引用
- 常量对象
    - 不希望值被改变, 前面加`const`
    - `const Complex c1;`
- 常量成员函数(习惯于在后面加`const`)
    - 不应该修改其所作用对象的值(静态成员变量除外)
    - 不能调用同类的非常量成员函数(静态成员函数除外)
    - 其重载部分没听, 略
<!-- <details>
<summary>常量成员函数示意</summary> -->

```C++
class Sample {
    public:
        int value;
        void func() {}
        Sample() {}
        void GetValue() const {
            value = 0;  // error
            func();     // error
        }
}
int main() {
    const Sample o;
    o.value = 100;  // error 不能改变常量对象的内容
    o.func();       // error 不能调用非常量函数
    o.GeValue();    // pass
    return 0;
}
```
<!-- </details> -->

- 常引用
    - 对象做函数参数, 复制构造函数麻烦, 指针不好看, 用常引用
    - 常: 能够避免被引用的对象被意外改变
<!-- <details>
<summary>常引用示例</summary> -->

```C++
class Sample {}
void PrintfObj(Sample & o); // 常引用
```
<!-- </details> -->


## 运算符重载的基本概念
- 对抽象数据类型也能直接使用运算符
    - C++预定义的计算符, 作用对象有限
    - 程序更简洁, 代码更容易理解
- 运算符重载
    - 对已有的运算符赋予多重含义
    - 使同一运算符作用于不同数据时, 有不同的行为
    - 扩展运算符的适用范围, 使其能够用于所有类的抽象数据类型
- 实质为函数重载
    - 程序编译时
        - 将运算符的表达式 编译为 对运算符函数的调用
        - 运算符的操作对象 编译为 运算符函数的参数
    - 运算符被多次重载时, 根据**具体实参类型**决定调用哪个运算符
    - 可以重载为普通函数 / 类的成员函数
- `返回值类型 operator 运算符 (形参表)`
    - 重载为普通函数, 参数个数为运算符目数(参与运算参量的个数)
    - 重载为成员函数, 参数个数为运算符目数减一
```C++
    class Complex {
        public:
            double real, imag;
            Complex(double r = 0.0, double i = 0.0)
                : real(r), imag(i) {}
    };
    Complex operator+ (const Complex & a, const Complex & b) {
        return Complex(a.real + b.real, a.imag + b.imag);
    }   // 重载为普通函数
    Complex operator- (const Complex & a, const Complex & b) {
        return Complex(a.real - b.real, a.imag - b.imag);
    }   // 重载为普通函数
    int main() {
        Complex c1(2,3), c2(5,7), c3;
        c3 = c1 + c2;   // 调用 Complex operator+(c1, c2)
        return 0;
    }
```
```C++
    class Complex {
        public:
            double real, imag;
            Complex(double r = 0.0, double i = 0.0)
                : real(r), imag(i) {}
            Complex operator+ (const Complex & operand2) {
                return Complex(this->real + operand2.real, this->imag + operand2.imag);
            }   // 重载为成员函数
            Complex operator- (const Complex & operand2) {
                return Complex(this->real - operand2.real, this->imag - operand2.imag);
            }   // 重载为成员函数
    };
    int main() {
        Complex c1(2,3), c2(5,7), c3;
        c3 = c1 + c2;   // 调用 Complex c1.operator+(c2)
        return 0;
    }
```

## 赋值`=`运算符重载
- 编译器可以接受同类赋值
- 重载后, `=`两边可以不匹配
    - `int`到`Complex`
    - `char*`到`string`
- 只能重载为**成员函数**!!
```C++
class String {
    private:
        char *str;
    public:
        String():str(NULL) {}
        String(String & s);
        const char *c_str() {return str;}
        char *operator = (const char *s);
        String & String::operator= (const String & s);
        ~String() {if(str) delete []str;}
};
String::String(String & s) {
    if (s.str) {
        str = new char[strlen(s.str) + 1];
        strcpy(str, s.str);
    } else str = NULL;  // 使用同重载=的方法解决复制构造函数
}
char *String::operator= (const char *s) {
    if(str) delete []str;   // 删除原有
    if(s) { // s不为NULL才会执行拷贝
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    } else str = NULL;
    return str;
}
String & String::operator= (const String & s) {
    if (str) delete []str;
    str = new char[strlen(s.str)+1];
    strcpy(str, s.str);
    return *this;
}
int main() {
    String s;
    s = "Good Luck";
    cout << s.c_str() << endl;
    // String s2 = "hello!";   // error编译器报错
    s = "Bonjour";
    cout << s.c_str() << endl;
    return 0;
}
```

## 深复制 / 浅复制
- 浅复制: 复制了指针
- 深复制: 把一个对象的指针变量指向的内容, 复制到另一个对象中指针成员对象指向的地方

## 返回值类型
- 希望能够实现**连等**, 所以返回值和参数值类型相同
- 返回值是为了**连等**能够实现
- 好的风格: 尽量保留运算符原本的特性