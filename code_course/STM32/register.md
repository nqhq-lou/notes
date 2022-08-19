# 什么是寄存器
- 参考文献: 光盘A, 1-程序源码_教程文档, 1-[野火]

## STM32芯片
- 基础描述
    - 从小圆点开始, 逆时针为第一个引脚, 一共144个
    - STM32F103: 内核/CPU为Cortex-M3
    - FLASH: Flash EEPROM Memory, 闪存
        - 能够快速读写和修改内容
        - 断电不会丢失数据
    - SRAM: Static Random-Access Memory
        - 静态随机存取存储器, 断电后信息丢失
- 架构
    - ICode总线: 指令总线
        - 程序编译为指令, 存放在FLASH中
        - 内核通过ICode总线读取指令
    - 驱动单元
        - DCode总线: 数据总线
            - 数据中, 常量存放在FLASH中, 变量存放在SRAM中
            - 需要总线矩阵, 防止读取冲突
        - 系统总线
            - 连接访问外设寄存器, 即"寄存器编程"
        - DMA总线
            - 传输数据, 可以访问外设寄存器, SRAM, FLASH
            - 需要总线矩阵, 防止读取冲突
    - 被动单元
        - FLASH
        - SRAM
        - ***FSMC***: Flexible Static Memory Controller
            - 灵活静态存储器控制器, 用于扩展静态的内存
        - AHB总线
            - Advanced High-performance Bus
            - 伸出两条总线: APB2 / APB1
                - Advanced Peripheral Bus
            - 片上外设

## 存储器映射
- 被控单元的FLASH, RAM, FSMC, AHB到APB的桥
    - 以上功能部件共同排列在一个4GB的地址空间里, 32Gb
    - 编程时, 通过地址找到他们, 然后对他们进行操作
- 存储器映射
    - Block0 ~ Block7
- Block0
    - `0x0000 0000` - `0x0007 FFFF`
        - 好像和BOOT引脚, FLASH, 系统存储器, SRAM有关
    - `0x0800 0000` - `0x0807 FFFF`
        - 512KB, FLASH的位置, 程序存放的地方
    - `0x1FFF F000` - `0x1FFF F7FF`
        - 2KB, ST出厂时写好的isp自举程序, Bootloader相关
        - 用户无法改动, 串口下载相关
- Block1
- Block2
    - `0x4000 0000` - `0x4000 77FF`
        - APB1总线外设
    - `0x4001 0000` - `0x4001 3FFF`
        - APB2总线外设
    - `0x4001 8000` - `0x5003 FFFF`
        - AHB总线外设

## 寄存器映射
- Block2区域中, 为片上外设(非CPU相关设计)
- 单元:
    - 4Byte为一个单元, 一共32bit
    - 每个单元对应不同的功能, 控制这些单元, 能够驱动外设工作
    - 可以通过每个单元的起始地址, 通过C语言的指针操作进行访问
    - **给这些单元按功能取别名: 寄存器映射**
- 例子
    - GPIOB端口输出数据寄存器的地址为`0x4001 0C0C`
    - 指针操作, 让GPIOB的16个端口都输出高电平
    ```C
    *(unsigned int *)(0x40010C0C) = 0xFFFF
    ```
    - 或者更简单的: 用宏定义
    ```C
    #define GPIOB_ODR *(unsigned int *)(GPIOB_BASE+0x0C)
    GPIOB_ODR = 0xFF
    ```

## 外设地址映射
- APB1挂载低速外设, APB2和AHB挂载高速外设
- 外设基地址
    - 相应总线的最低地址, 称为**该总线的基地址**, 也是挂在总线上的首个外设的地址
    - i.e. GPIOB 的外设基地址为 `0x4001 0C00`
- 外设寄存器
    - 某外设的地址范围内, 分布着该外设的寄存器.
    - 每个寄存器为4Byte=32bit, 能用来实现特定功能.
    - 寄存器名称:
        - CRL: **Configure** Register Low
        - CRH: **Configure** Register High
        - IDR: Input **Data** Register
        - ODR: Output **Data** Register
        - BSRR: Bit **Set Reset** Register
        - BRR: Bit **Remove** Register
        - LCKR: **Lock** Register
    - e.g. GPIOx_**BSRR**: **Bit Set Reset Register**
        - offset: `0x10`, 相对基地址的偏移地址
        - 寄存器位表
            - 0-31位的名称和权限, 表上方的数字为编号, 中间为位名称, 最下方为读写权限.
        - 位功能说明:
            - 文档的表格里有详细的说明
            - 00 - 15: BS0 - BS15, bit set
            - 16 - 31: BR0 - BR15, bit reset

## 编程上应该怎么做:
- 总线和外设基址宏定义
<details>
<summary>总线和外设基址宏定义</summary>
<pre><code class="language-cpp">
/* Peripheral Base Address */
#define PERIPH_BASE	((unsigned int)0x40000000)
/* Bus Base Address */
#define APB1PERIPH_BASE	(PERIPH_BASE + 0x00000000)
#define APB2PERIPH_BASE	(PERIPH_BASE + 0x00010000)
#define AHBPERIPH_BASE	(PERIPH_BASE + 0x00020000)
/* GPIO Peripheral Base Address */
#define GPIOA_BASE	(APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE	(APB2PERIPH_BASE + 0x0c00)
/* GPIOA register address */
#define GPIOA_CRL	(GPIOA_BASE + 0x00)
#define GPIOA_CRH	(GPIOA_BASE + 0x04)
#define GPIOA_IDR	(GPIOA_BASE + 0x08)
#define GPIOA_ODR	(GPIOA_BASE + 0x0c)
#define GPIOA_BSRR	(GPIOA_BASE + 0x10)
#define GPIOA_BRR	(GPIOA_BASE + 0x14)
#define GPIOA_LCKR	(GPIOA_BASE + 0x18)
/* GPIOB register address */
#define GPIOB_CRL	(GPIOB_BASE + 0x00)
#define GPIOB_CRH	(GPIOB_BASE + 0x04)
#define GPIOB_IDR	(GPIOB_BASE + 0x08)
#define GPIOB_ODR	(GPIOB_BASE + 0x0c)
#define GPIOB_BSRR	(GPIOB_BASE + 0x10)
#define GPIOB_BRR	(GPIOB_BASE + 0x14)
#define GPIOB_LCKR	(GPIOB_BASE + 0x18)
</code></pre>
</details>

- 使用指针控制BSRR寄存器
    - `*(unsigned int*)`: 将数值强转为地址, 然后取内容
```C
#define CONT *(unsigned int*)  // 转成地址, 然后*取内容更改
/* GPIOB 引脚0 输出低电平, 控制BR0 */
SET GPIOB_BSRR = 0x01 << 16
/* GPIOB 引脚0 输出低电平, 控制BS0 */
SET GPIOB_BSRR = 0x01 << 0
/* 读取 GPIOB 端口所有引脚的电平, 用GPIOB_IDR */
unsigned int temp;
temp = CONT GPIOB_IDR;
```

## 封装寄存器列表
- 利用结构体的存储地址进行排序!
    - 相关操作见**书: P64**
```C
typedef unsigned int  unint32_t  // 占用 4Byte
typedef unsigned short int  unint16_t  // 占用 2Byte
/* GPIO Reg List */
typedef struct {
    uint32_t CRL;
    uint32_t CRH;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t BRR;
    uint16_t LCKR;
} GPIO_TypeDef;
```
```C
GPIO_TypeDef* GPIOx;  // 定义一个 GPIO_TypeDef 型结构体指针 GPIOx
GPIOx = GPIOB_BASE;  // 把指针地址设置为宏 GPIOB_BASE 地址
GPIOx->IDR = 0xFFFF;
GPIOx->ODR = 0xFFFF;
uint32_t temp = GPIOx->IDR;
```

## 改变变量数值
- 用 移位`<<` / 取反`~`, 获得如`1111 1001`这样的%b
- 用 位与`&` / 位或`|` / 位异或`^`, 与需要更改的数字运算
```C
a = 0x9F;  // 原始值
a &= ~(1<<2);  // 对 bit 2 清零
a |= (3<<2);  // 对 bit 2 3 置 1
a ^= (1<<2); // 对 bit 2 取反
```

## GPIO的八种工作模式
- 书 P88
1. 输入模式
    - 模拟, 浮空, 上拉, 下拉
2. 输出模式
    - 推挽, 开漏
3. 复用功能
    - 推挽, 开漏







