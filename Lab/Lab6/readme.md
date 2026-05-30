### Lab 6 — ISA design and assembler
### 实验6 — 指令系统设计与汇编器

#### 1. 实验目标

定义CPU指令系统，并实现一个两遍扫描汇编器，将汇编程序转换为程序 ROM 镜像。

完成本实验后，学生应能够：

1. 理解汇编语言与机器码之间的关系；
2. 理解寻址方式，并能够定义指令编码表；
3. 实现标签解析；
4. 生成 LogicCircuit 可加载的 RAM 镜像文件(`.bin`)；
5. 为CPU编写小型测试程序。

本实验对应理论课 [第4章](/Chapter-4/readme.md) 中的指令系统与汇编器。

#### 2. 知识点

关键概念：

- 指令系统结构：软件与硬件之间可见的约定。
- 操作码、目的操作数、源操作数。
- 寻址方式：
  + 立即数：将数字5写入寄存器A
    ```asm
    MOV A, 5 
    ```
  + 寄存器寻址：将寄存器B中的值写入寄存器A
      ```asm
      MOV A, B 
      ```
  + 直接寻址：将内存RAM地址5处的值写入寄存器A
      ```asm
      MOV A, [5] 
      ```
  + 寄存器间接寻址：将内存RAM地址等于寄存器B中的值处的值写入寄存器A
      ```asm
      MOV A, [B] 
      ```
- 标签与地址解析。
- 两遍扫描汇编：
  - 第一遍：收集标签和指令地址；
  - 第二遍：生成二进制字节。
- 汇编程序、机器码与 RAM 镜像的区别。

#### 3. 参考指令系统与汇编器要求
+ 指令系统
    至少支持如下指令：
    + 二地址指令（目的操作数，源操作数）：`MOV, ADD, SUB, AND, OR, XOR, CMP`
    + 一地址指令（目的操作数）：`INC, DEC, NOT，JZ, JNZ, JO, JNO, JMP`
    + 零地址指令（无操作数）：`HLT`

    及其对应的各种可行寻址方式，如`ADD C, 2`,`ADD C, B`, `ADD C, [2]`, `ADD [C], [2]`。

+ 汇编器
  要求必须支持：
  + 空行；
  + 以 `:` 结尾的标签；
  + 十进制常量，例如 `10`；

#### 4. 实验任务
##### 任务1: 指令集定义
创建`instruction.py`文件，文件内需要定义指令集设计的规则。这是汇编器进行汇编的基础。该文件内应当有如下内容：
```py
# instruction.py

# address mode
AM_IMM = 0
AM_REG = 1
AM_DIR = 2
AM_REG_RAM = 3

# 二地址指令
ADDR2_F = ...
ADDR2_OP = ...
MOV = (1 << ADDR2_F) | (0 << ADDR2_OP)
ADD = (1 << ADDR2_F) | (1 << ADDR2_OP)
...
# 一地址指令
ADDR1_F = 
ADDR1_OP = 
INC = (1 << ADDR1_F) | (0 << ADDR1_OP)
DEC = (1 << ADDR1_F) | (1 << ADDR1_OP)
...
# 零地址指令
HLT = 0x3f # 00111111

# 指令集
INSTRUCTION_SET = {
    # 2地址
    2: {
        MOV: {
            (AM_REG, AM_IMM):[] # []内是微指令，暂时可以留空, 后续实验会补上
            (AM_REG, AM_REG):[]
        },
        ADD:{
            (AM_REG, AM_IMM):[]
            (AM_REG, AM_REG):[]
        },
        ...
    },
    # 1地址
    1: {
        JMP: {
            AM_IMM: []
        },
        ...
    },
    # 0地址
    0: {
        ...
    }
}
```
##### 任务2: 汇编器实现
创建`assembler.py`文件，用于读取`.asm`文件并转化成机器码，完成汇编过程。
该文件应当有如下内容：
```py
# assembler.py

import instruction as ins

OP2 = {
    'MOV': ins.MOV,
    'ADD': ins.ADD,
    ...
}

OP1 = {
    'INC': ins.INC,
    'DEC': ins.DEC,
    ...
}

OP0 = {
    'HLT': ins.HLT,
}

# 寄存器索引
REGISTERS = {
    'A': ,
    'B': ,
    'C': ,
    'D': ,
    'O': ,
}

# 汇编程序中的标签
labels = {}

# 要转成二进制的内容
results = []

# 打开.asm文件读取内容到lines
with open(input_file, encoding='utf8') as fd:
    lines = fd.readlines()

# 第一遍解析标签
for index, line in enumerate(lines):
    if source.endswith(":"):
        # 以冒号结尾为标签
        # 处理
        pass

# 第二遍解析操作数，转成操作码
for index, line in enumerate(lines):
    # 去除多余的空格
    source = line.strip()
    if source.endswith(":"):
        # 如果是标签就跳过进行下一句
        continue
    # 用逗号分隔代码, 得到操作码和操作数
    tmp = source.split(',')
    # 如若source = "MOV A, B"，则tmp = ['MOV A', 'B']
    # 继续处理，然后按照是几地址指令分情况转码
    ir = ?
    dst = ?
    src = ?
    # 最后将结果写入results
    results.append([ir, dst, src])
    pass

# 生成.bin文件 - RAM镜像
with open(output_file, 'wb+') as fd:
    # 遍历results, 每个r是3个数，每个占一字节，共3字节
    for r in results:
        for v in r:
            fd.write(v.to_bytes(1, byteorder='little'))
```

##### 任务3：汇编器验证
1. 将实验材料提供的`program.asm`转化成二进制机器码`program.bin`。
2. 将`program.bin`加载到LogicCircuit的RAM(8bit地址8bit数据)中并截图。
3. 编写一个计算斐波那契数列的汇编代码`fibonacci.asm`并转化成二进制机器码`fibonacci.bin`。
   提示：斐波那契递推公式：$x(n) = x(n-1) + x(n-2), n > 2\in Z^+ $, $x(0)=0, x(1)=1$

##### *选做任务：
升级汇编器，使其支持：
+ 分号开始的注释；
  ```asm
  MOV C, 1; this is a comment
  ; this is a comment
  MOV D, C
  ```
+ 十六进制常量，例如 `0x0A`；
+ 二进制常量，例如 `0b00001010`；
+ 标签或指令未知时给出带源代码行号的错误报告。

#### 4. 实验报告提交
把：
1. `instruction.py`, `assembler.py`, `fibonacci.asm`；
2. `program.bin`, `fibonacci.bin`
3. `PCO_Lab6_姓名.md`；
4. `images/` 中的截图；

压缩成 `PCO_Lab6_姓名.zip`，邮件发送到`xsun@gzhu.edu.cn`,邮件主题：`PCO-Lab6-Assignment`

截止日期（过期提交无成绩）: **2026年6月16日（第16周周二）前**。


#### 5. 报告评分标准

| 评分项 | 权重 | 说明 |
|---|---:|---|
| ISA定义正确 | 20% | 操作码、寻址方式和语义清晰 |
| 汇编器正确性 | 40% | 能正确处理标签、常量和字节生成 |
| 斐波那契汇编程序 | 15% | 程序有意义，并能对应后续CPU测试 |
| 报告清晰度 | 25% | 能清楚解释设计、示例和测试证据 |