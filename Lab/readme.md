## 8-bit CPU Laboratory Course / 8位CPU实验课程
*2025-2026-2 Principal of Computer Organization
Xuelong SUN @ GZHU*


### 1. Course Positioning / 课程定位

This laboratory course is designed to run in parallel with the theory course **Principles of Computer Organization**. The theory course explains the 8-bit CPU architecture by decomposing it into computation, memory, control, and instruction-set/architecture layers. The lab course follows the same decomposition, but converts each theoretical layer into a concrete artifact that students build, test, document, and finally integrate.

The final goal is that each student or student team independently builds a **programmable 8-bit CPU in LogicCircuit**, with a small software toolchain written in Python:

- an assembler that compiles `.asm` programs into program-memory images;
- a microprogram compiler that compiles symbolic microinstructions into control-ROM images;
- a tested LogicCircuit CPU that can load the generated memory images and execute programs.

本实验课程与《计算机组成原理》理论课同步设计。理论课将8位CPU体系结构分解为计算、存储、控制、指令系统与CPU结构四个层次；实验课则沿着同样的分解路径，让学生逐步构建、测试、记录并最终集成一个可编程的8位CPU。

最终目标是让学生独立完成一个基于 **LogicCircuit** 的可编程8位CPU，并配套完成一个用 Python 编写的小型软件工具链：
- 将 `.asm` 汇编程序编译为程序存储器镜像的汇编器；
- 将符号化微指令编译为控制ROM镜像的微程序编译器；
- 能够加载上述镜像并运行测试程序的 LogicCircuit CPU。
---

### 2. Lab overview and grading 实验课总览和评分

| Lab | English title | 中文标题 | Theory alignment 理论课对应 |Score Weight 分数权重|
|:---:|---|---|---|:---:|
| [1](Lab1/readme.md) | LogicCircuit, Markdown, and NAND-based gates | LogicCircuit、Markdown与NAND基本门 | Chapter 1: logic gates and computation | 6% |
| 2 | Python basics for PCO | 面向计组的Python基础 | tool preparation | 8% |
| 3 | 8-bit ALU and flags | 8位ALU与标志位 | Chapter 1: ALU integration |10% |
| 4 | Registers, program counter, and bus | 寄存器、程序计数器与总线 | Chapter 2: storage elements | 10% |
| 5 | Memory subsystem and instruction fetch | 存储系统与取指周期 | Chapter 2: RAM/ROM and Chapter 4 preparation | 10% |
| 6 | ISA design and assembler | 指令系统设计与汇编器 | Chapter 4: ISA and architecture | 12% |
| 7 | Microprogrammed control unit | 微程序控制器 | Chapter 3: microprogrammed control | 14% |
| 8 | CPU integration and demonstration | CPU集成与演示 | Chapter 4: full CPU architecture | 30% ([see 3.](#3-final-outcome-grading-rubric--最终成果评分细则))|
---

### 3. Final outcome grading rubric (Lab 8) / 最终成果评分细则 (实验8)

| Criterion 指标 | Weight 权重 | Excellent performance 满分表现|
|---|:---:|---|
| CPU functionality / CPU 功能| 35% | Executes all required instructions reliably; handles reset, halt, flags, memory, and control flow correctly |
| Software toolchain / 软件工具链 | 20% | Assembler and microprogram compiler are usable, documented, deterministic, and include error handling |
| Verification and demonstration / 验证与演示| 20% | Provides convincing test programs, expected/actual results, screenshots, and debugging traces |
| Architecture documentation / 架构文档撰写 | 15% | Clearly explains datapath, control signals, microcode format, ISA, and design trade-offs |
| Engineering quality / 工程质量 | 10% | Clean hierarchy, readable signal naming, modular files, reproducible build/run process |
