### Lab 7 — CPU hardware architecture 2 and microprogrammed control
### 实验7 — CPU硬件架构2和微程序

#### 1. 实验目标
基于[Lab5](/Lab/Lab5/readme.md)完成CPU硬件的搭建，并设计微程序。

完成本实验后，能够：
1. 清楚CPU硬件的基本组成
2. 理解专用寄存器，如指令寄存器IR，操作数寄存器SRC和DST、内存地址寄存器MAR等的功能
3. 理解CPU取指令和指令的过程
4. 理解微程序控制的原理并用代码生成微程序存储器镜像

#### 2. 知识点

关键概念：
+ 指令周期：有取值周期和执行周期构成
+ 取指令：完成将指令和数据从内存加载到IR,DST,SRC寄存器的功能
+ 执行指令：指令控制单元根据IR、PSW和当前指令周期CYCLE产生访问微程序存储器的地址，进而获得微操作指令控制硬件执行某种功能。
+ 微程序控制：在每个时钟周期和特定ALU的PSW状态下生成正确的硬件控制信号

#### 3. 实验任务
##### 任务1: 完成CPU硬件架构
基于[Lab5](/Lab/Lab5/readme.md)中的电路：
+ 【红色标号】选择部分寄存器，充当专用寄存器IR, DST, SRC，MAR等
+ 【橙色标号】选择部分寄存器，充当通用寄存器C, D等
+ 【绿色标号】加入程序计数器PC (program counter)、ALU和RAM（MC8X8）
+ 【紫色标号1】设计构建指令控制器CU-IR，其接受指令寄存器、ALU的PSW输出为输入，产生访问微程序存储器ROM的地址
+ 【紫色标号2】设计构建控制单元，接受来自微程序存储单元输出的控制信号，转化成控制信号输出用于控制所有寄存器（将[Lab5](/Lab/Lab5/readme.md)中的寄存器控制器封装到控制单元CU中，其不再接受手动给定的`R-read`和`W-write`，而是从SRC/DST或微程序的输出中进行分离）、内存读写、ALU、PC等。
+ 【蓝色标号】加入ROM（地址位/数据位位宽根据自己所设计的CPU决定）用于存储微程序
+ TIPS: 为了减少导线，可将同一个硬件单元的控制信号进行集线处理，比如将ALU-CS/ALU-WE/ALU-OP/ALU-PSW集合成一个6bit的控制信号，这样控制单元只输出一个6bit的ALU控制信号就好。

完成上述步骤后，一个最小的可编程8bit CPU就诞生了：

![](/Chapter-4/figs/CPU.png)

为了方便调试和观察，我们可以：
+ 定义某个寄存器为输出寄存器，给他`od`输出接一个数码管，方便我们观察运算结果。
+ 可以给任何重要的信号添加探针/LED以观察电路的实时状态。
+ 给周期计数器的输出CYCLE接一个一位数码管，方便观察现在的指令周期。

电路搭建完成，给出总体电路截图即可，后续实验中我们再进行测试。

##### 任务2：Python脚本完成微程序镜像生成
+ 创建`hardware.py`文件，根据硬件定义内容：
  ```py
  # hardware.py
  
  # 首先是寄存器的编号
  # 注意：寄存器需要从1开始编号
  MAR = 1
  RAM = 2
  IR = 3
  ...

  # 然后是寄存器作为目的操作数和源操作数的读写控制
  # 作为目的操作数需要左移4位(这个可以自己定义)
  MAR_OUT = MAR
  MAR_IN = MAR << _DST_SHIFT
  RAM_OUT = RAM
  RAM_IN = RAM << _DST_SHIFT
  ...

  # PC的控制
  PC_CS = 1 << 11
  PC_WE = 1 << 12
  PC_EN = 1 << 13
  ....
  # ALU的控制
  ALU_CS = 1 << 14
  ...

  # HLT

  # CYCLE-clear

  ```
+ 完善[Lab6](/Lab/Lab6/readme.md])中的指令集文件`instruction.py`,添加指令的微程序：
  ```py
  # instruction.py
  import hardware as hw
  # 取指微程序
  FETCH = [
       hw.PC_OUT | hw.MAR_IN, # PC -> MAR
       ...
  ]
  # 其他指令
  INSTRUCTION_SET = {
    # 2地址
    2: {
        MOV: {
            # MOV C, 4
            (AM_REG, AM_IMM):[
                # 例如：
                hw.SRC_OUT | hw.DST_W # SRC -> DST内容所对应的寄存器
            ]
            (AM_REG, AM_REG):[
                # 需填上内容
            ]
        },
        ADD:{
            (AM_REG, AM_IMM):[
                # 需填上内容
            ]
            (AM_REG, AM_REG):[

            ]
        },
        ...
    },
    # 1地址
    1: {
        JMP: {
            AM_IMM: [

            ]
        },
        ...
    },
    # 0地址
    0: {
        ...
    }
  }
  ```
+ 微程序生成
  微程序存储镜像的本质是在**特定的地址处**存储**正确的硬件控制信号组成的二进制数**，而这个地址由任务1中指令控制单元CU-IR给出。所以，基本思路是遍历每一个存储位置（本质就是接收到的指令译码），按照上述`hardware.py`的内容生成对应的值：
   ```py
   import hardware as hw
   # 初始化一个微程序数组, 先全初始化为HLT
   # 16 bit address: 0x0000 - 0xffff
   micro = [hw.HLT for _ in range(0x10000)]

   # 遍历每一个地址
   for addr in range(0x10000):
        # 16bit addr: IR (15-8)| PSW(7-4) | CYC(3-0)
        # 根据定义提取ir,psw和cyc
        ir = addr >> 8
        psw = addr >> 4 & 0x0f
        cyc = addr & 0x0f

        # 取指周期
        if cyc < len(ins.FETCH):
          micro[addr] = ins.FETCH[cyc]
          continue
        
        # 执行周期
        index = cyc - len(ins.FETCH)
        # 按照操作数数目的不同，分情况获得硬件控制信号
        if ir & (1 << ins.ADDR2_F):
            # 二地址指令
            micro[addr] = get_addr2_exe_ins(ir, index) # 可以定义函数来实现
        elif ir & (1 << ins.ADDR1_F):
            # 一地址指令
            micro[addr] = get_addr1_exe_ins(ir, index)
        else:
            # 零地址指令
            micro[addr] = get_addr0_exe_ins(ir, index)
   # 最后将micro写入bin文件，生成存储器镜像
   with open(filename, 'wb') as fd:
        for var in micro:
            value = var.to_bytes(3, byteorder='little')
            fd.write(value)
   ```
   对于操作数数量不同的指令，得到硬件控制信号的方式不同，比如函数`get_addr2_exe_ins(ir, index)`, 可能的实现为：
   
   ```py
    def get_addr2_exe_ins(ir, index):
        # step1: 根据编码规则，先把信息从IR中分离出来
        # [7]  [6:4]   [3:2]   [1:0]
        #  1    OP    DST_AM  SRC_AM
        op = ir & 0xf0
        dst_am = (ir >> 2) & 0x03
        src_am = ir & 0x03
        
        # step2：检查OP是否在instruction.py文件定义的指令集中
        # 不存在的话直接指令周期计数器清零
        instruction = ins.INSTRUCTION_SET[2]
        if op not in instruction:
            return hw.CYC_CLR
        
        # step3: 若step2检查后存在，则检查寻址方式的组合是否存在
        am = (dst_am, src_am)
        if am not in instruction[op]:
            return hw.CYC_CLR
        
        # step4: 若step3检查后存在，则根据寻址方式的不同获得硬件控制信号
        # 若index等于了指令的周期数，则意味着该指令已执行完成，需要清零指令周期计数器，以便开始下一条指令的取值环节
        execute_ins = instruction[op][am]
        if index < len(execute_ins):
            return execute_ins[index]
        else:
            return hw.CYC_CLR  
   ```
   同样的，对于一地址和零地址指令所需要的函数`get_addr1_exe_ins()`和`get_addr0_exe_ins()`需要大家自己实现：

   > 提示：对于1地址指令，`JMP,JNZ`这些指令需要检查`PSW`的状态，实现起来会有些许不同。

   任务：创建`microprogram.py`文件，编写并完善上述代码，生成自己的微程序镜像`microprogram.bin`，然后加载到CPU的微程序存储器中并截图（局部即可），可参考理论课讲义:[第4章](/Chapter-4/readme.md)。

#### 4. 实验报告提交
把：
1. LogicCircuit 工程文件 (`*.CircuitProject`)；
2. `instruction.py`，`hardware.py`，`microprogram.py`
3. `microprogram.bin`；
4. `PCO_Lab7_姓名.md`；
5. `images/` 中的截图；

压缩成 `PCO_Lab7_姓名.zip`，邮件发送到`xsun@gzhu.edu.cn`,邮件主题：`PCO-Lab7-Assignment`

截止日期（过期提交无成绩）: **2026年6月30日（第18周周二）前**。

#### 5. 报告评分标准

| 评分项 | 权重 | 说明 |
|---|---:|---|
| CPU电路| 25% | 包含专用寄存器、PC等必须部件，总线结构和关键信号连接正确 |
| 微程序硬件脚本 | 15% | 信号定义完整且正确 |
| 微程序镜像生产脚本 | 35% | 逻辑正确，代码结构合理，能生成正确的微程序存储器镜像 |
| 报告清晰度 | 25% | 能清楚解释设计、示例和测试证据 |