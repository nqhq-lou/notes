# PKU Cpp from bilibili

## 面向对象的设计方法
- 设计程序的过程 -> 设计类的过程
    - 封装的过程: 数据结构和函数关系
    - class: Data & Function
    - 此外还有继承, 多态两种函数
        ```C
        class 类名 {
            访问范围说明符:
                成员变量1;
                成员变量2;
                成员函数声明1;
                成员函数声明2;
            访问范围说明符:
                更多成员变量;
                更多成员函数声明;
                ...
        }
        ```
- 例子
    - 矩形的情况, 提示: 可以使用缺省参数, 但是注意二义性!
        <!-- <details>
        <summary>矩形的例子</summary> -->

        ```C++
        class CRectangle {
            public:
                int w, h;   // 长 和 宽
                void Init(int w_ = 1, int h_ = 1) {
                    w = w_; h = h_; // 通过读入定义长宽
                }
                int Area() {
                    return w*h;
                }
                int Perimeter() {
                    return 2 * (w + h);
                }
        };  // 必须要有分号
        void printRectangle(CRectangle & r) {   // 通过引用进行输出
            cout << r.Area() << "," << r.Perimeter();
        }
        int main() {
            int w, h;
            CRectangle r;

            cin >> w >> h;
            r.Init(w, h);
            cout << r.Area() << endl << r.Perimeter();
            cout << sizeof(CRectangle); // sizeof = int + int = 8

            CRectangle r1, r2;
            CRectangle *p1 = &r1;   // 指向地址
            CRectangle *p2 = &r1;
            p1->w = 5;
            p2->Init(3, 4);

            CRectangle & rr = r2;
            rr.Init(3, 4);      // 进行引用, 仅仅是别名, 没什么区别

            printRectangle(r2); // 通过上文引用进行输出

            return 0;
        }
        ```

        <!-- </details> -->

    - 类的成员函数可以写在外面
        <!-- <details>
        <summary>成员函数写在外面</summary> -->

        ```C++
        class CRectangle {
        public:
            int w, h;   // 长 和 宽
            void Init(int w_, int h_);
            int Area();
            int Perimeter();
        };  // 必须要有分号
        // 需要使用作用域算符的形式, 写里面的函数
        void CRectangle::Init(int w_, int h_) {
            w = w_; h = h_; // 通过读入定义长宽
        }
        int CRectangle::Area() {
            return w*h;
        }
        int CRectangle::Perimeter() {
            return 2 * (w + h);
        }

        int main() {
            return 0;
        }
        ```

        <!-- </details> -->


- 一些细节
    - 对象的内存分配
        - 对象大小 = 所有成员变量大小之和
    - 对象之间可以使用各种`=`进行赋值
        - 但是不能比较, 除非算符重载(在哪里学w)

## 类成员可访问范围
- `private`, `public`,`protected`
    - `private`: **私有成员**, 只能在成员函数内被访问(或同类成员函数)
    - `public`: **公有成员**, 可以在任何地方被访问
    - `protected`: 保护成员
    - 目的为**隐藏**私有成员, **强制**要求成员变量的访问通过成员函数.

- 说明
    - 未声明, 则为`private`
    - 类的成员函数内部, 可以访问 所有**同类对象**的**全部属性, 函数**(包括别的但是同类的)
    - 类的成员函数外, 只能访问 该类对象的**公有成员**

## 构造函数 Constructor
- 成员函数的一种: 用于执行必须执行的初始化, 防止忘记
    - 与类名相同, 可以有参数, 不可以有返回值
    - 作用为: 对象初始化时调用, 如给成员变量赋值. 之后再也不会被调用
    - 如果没写, 编译器生成一个默认的无参数的构造函数; 如果写了就不生成
    - 一个类可以有多个构造函数
    <!-- <details>
    <summary>无构造函数</summary> -->

    ```C++
    class Complex {
        private:
            double real, imag;
        public:
            void set(double r, double i);
    };  // 编译器自动生成默认构造函数
    Complex cl; // 默认构造函数被调用
    Complex *pc = new Complex;  // 同上
    ```

    <!-- </details> -->

    <!-- <details>
    <summary>有构造函数</summary> -->

    ```C++
    class Complex {
        private:
            double real, imag;
        public:
            void set(double r, double i);
            Complex(double r, double i = 0);
            Complex::Complex(Complex c1, Complex c2);
    };  // 编译器自动生成默认构造函数
    Complex::Complex(double r, double i = 0) {
        real = r; imag = i;
    }
    Complex::Complex(Complex c1, Complex c2) {
        real = c1.real + c2.real;
        imag = c1.imag + c2.imag;
    }
    Complex cl; // 编译器报错, 缺少构造函数的参数
    Complex *pc = new Complex; // 同上
    Complex c1(2);  // 可以有, 有参数了
    Complex *pc2 = new Complex(3, 4);    // 可以有
    Complex c3(c1, *c2);    // 可以有
    ```

    <!-- </details> -->

    <!-- <details>
    <summary>数组1</summary> -->

    ```C++
    class CSample {
        int x;
        public:
            CSample() {
                cout << "constructor 1" << endl;
            }
            CSample(int n) {
                x = n;
                cout << "constructor 2" << endl;
            }
    };
    int main() {
        CSample array1[2];  // 用无参构造函数初始化
        CSample array2[2] = {4, 5};  // 有参构造函数初始化, 初始化两次
        CSample array2[3] = {3};  // 有参无参各一次, 初始化两次
        CSample *array4 = new CSample[2];   // 两次无参初始化
        delete []array4;
        return 0;
    }
    ```

    <!-- </details> -->

    <!-- <details>
    <summary>数组2</summary> -->

    ```C++
    class CCSample {
        int x;
        public:
            CCSample();
            CCSample(int n) {x = n;}
            CCSample(int m, int n) {x = m + n;}
    };
    int main() {
        CCSample array1[3] = {1, CCSample(1,2)};
        // 分别使用一个参数, 两个参数, 无参数初始化
        CCSample *pArrary[3] = {new CCSample(4), new CCSample(1,2)};
        // 用new出来的地址取初始化
    }
    ```

    <!-- </details> -->

- 复制构造函数
    - 直接抄袭
    - 如果某函数有一个参数/返回值是类A的对象, 那么该函数被调用.返回的时候, 类A的复制构造参数将被调用.

    <!-- <details>
    <summary>简单抄袭</summary> -->

    ```C++
    class Complex {
        private:
            double real, imag;
    };
    Complex c1;     // 缺省
    Complex c2(c1); // 调用缺省的复制构造函数, c2 = c1
    ```

    <!-- </details> -->

    <!-- <details>
    <summary>自定义抄袭</summary> -->

    ```C++
    class Complex {
        private:
            double real, imag;
        public:
            Complex() {};
            Complex(const Complex & c) {    // 必须是本类的引用
                real = c.real;  imag = c.imag;
            }
    };
    Complex c1;     // 缺省
    Complex c2(c1); // 调用自定义的复制构造函数, c2 = c1
    ```

    <!-- </details> -->

## 类型转换构造函数
- 实现类型的自动转换
    - 只有一个参数, 不是复制构造函数
    - 作用方式: 建立一个临时的类对象
    <!-- <details>
    <summary>类型转换示例</summary> -->

    ```C++
    class Complex {
        public:
            double real, imag;
            Complex(int r) {
                real = r;   imag = 0;
            }
            Complex(double r, double i) {
                real = r;   imag = i;
            }
    };
    int main() {
        Complex c1(7, 8);
        Complex c2(12);
        c1 = 9;
        cout << c1.real << c1.imag << endl;
        return 0;
    }
    ```

    <!-- </details> -->


## 析构函数 Destructor

- 成员函数的一种, 名字在类名前面加`~`
    - 没有参数和返回值, 一个类最多有一个析构函数
    - 用于对象消亡时的善后工作, 释放分配的空间等
    - 自动生成缺省析构函数, 也可以自己定义
    - 这里视频后来跳过去没看
    <!-- <details>
    <summary>析构函数示例</summary> -->

    ```C++
    class String{
        private:
            char *p;
        public:
            String() {
                p = new char[10];
            }
            ~String() {
                delete []p; // new出来的需要手动delete, 其他可以自动
            }
    };
    ```

    <!-- </details> -->

# 静态成员变量/静态成员函数
- 静态成员: 说明前加了`static`关键字
    - 普通成员变量, 每个对象各自一份
    - 静态成员变量, 所有对象共享一份
        - `sizeof()`不会计算静态成员变量
        - 所以是放在所有对象外的, 被共享的
        - 同时, 静态成员变量不需要对象就能访问
    - 普通成员函数, 必须作用于某个对象
    - 静态成员函数, 并不具体作用于某个对象
        - 访问方式: 注意! 并不具体作用于某个对象!!!
        - `CRectangle::PrintTotal();`
        - `CRectangle r; r.PrintTotal();`
        - `CRectangle *p = &r; p->PrintTotal();`
        - `CRectangle & ref = r; int n = ref.PrintTotal();`
- 实质上
    - 静态成员变量本质上是 全局变量, 没有对象存在, 静态成员变量也存在
    - 静态成员函数本质上是 全局函数
    - 作用为, 将某些和对象紧密相关的全局变量写在类里面
    - 成为一个整体, 利于理解和维护
    <!-- <details>
    <summary>静态成员XX示例</summary> -->

    ```C++
    class CRectangle {
        private:
            int w, h;
            static int nTotalArea;
            static int nTotalNumber;    // 记得声明!!
        public:
            CRectangle (int w_, int h_) {
                w = w_; h = h_;
                nTotalNumber++;
                nTotalArea += w*h;
            }
            CRectangle (CRectangle & r) {
                w = r.w; h = r.h;
                nTotalNumber++;
                nTotalArea += w*h;
            }   // 有了静态之后必须补充 复制构造函数
            // 不然会出现临时变量的复制生成方式会导致Number少一个
            ~CRectangle() {
                nTotalNumber--;
                nTotalNumber -= w*h;
            }
            static void PrintTotal() {
                cout << nTotalNumber << "," << nTotalArea << endl;
            }
    };
    int CRectangle::nTotalArea = 0; // 在这里声明!!
    int CRectangle::nTotalNumber = 0;
    ```

    <!-- </details> -->

- 注意
    - 在静态成员函数中, 不能访问非静态成员变量, 也不能调用非静态成员函数.
    - 不然无法确定调用的非静态XX`CRectangle::w`到底指代哪个成员的.


## 成员对象和封闭类
- 成员对象: 一个类的成员变量是另一个类的对象
    - 包含成员对象的类叫**封闭类**

<!-- <details>
<summary>封闭类示例</summary> -->

```C++
class CTyre {
    private:
        int radius;
        int width;
    public:
        CTyre(int r, int w)
            : radius(r), width(w){}
        // 初始化列表
        // 跟着需要初始化的成员变量, 更容易看
};
class CEngine {
};
class CCar {
    private:
        int price;
        CTyre tyre;
        CEngine engine;
    public:
        CCar(int p, int tr, int tw)
            : price(p), tyre(tr, tw){}
};
int main() {
    CCar car(20000, 17, 225);
    // 如果不定义, 就会error
    // 推荐使用初始化列表
    return 0;
}
```

<!-- </details> -->

- 构造和析构函数调用顺寻
    - 按照封闭类中的定义顺序: 构造顺序, 析构倒序






<!-- <details>
<summary>可收缩代码示例</summary> -->

```C++

```

<!-- </details> -->



