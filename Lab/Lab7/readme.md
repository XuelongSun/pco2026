### Lab 7 — CPU hardware architecture 2 and microprogrammed control
### 实验7 — CPU硬件架构2和微程序

#### 1. 实验目标
基于[Lab5](/Lab/Lab5/readme.md)完成CPU硬件的搭建，并设计微程序。

完成本实验后，能够：
1. 清楚CPU硬件的基本组成
2. 理解专用寄存器，如指令寄存器IR，操作数寄存器SRC和DST等的功能
3. 理解CPU取指令和指令的过程
4. 理解微程序控制的原理并用代码生成微程序存储器镜像

#### 2. 知识点

关键概念：
+ 指令周期：有取值周期和执行周期构成
+ 取指令：完成将指令和数据从内存加载到寄存器的功能
+ 微程序控制：在每个时钟周期和特定ALU的PSW状态下生成正确的硬件控制信号

#### 3. 实验任务
##### 任务1: 完成CPU硬件架构
##### 任务2：Python脚本完成微程序镜像生成
微程序存储镜像的本质是在特定的地址处生成正确的硬件控制信号
```py

```

#### 4. 实验报告提交
把：
1. LogicCircuit 工程文件 (`*.CircuitProject`)；
2. `microprogram.py`；
3. `PCO_Lab7_姓名.md`；
4. `images/` 中的截图；

压缩成 `PCO_Lab7_姓名.zip`，邮件发送到`xsun@gzhu.edu.cn`,邮件主题：`PCO-Lab7-Assignment`

截止日期（过期提交无成绩）: **2026年6月23日（第17周周二）前**。