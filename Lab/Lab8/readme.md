### Lab 8 — CPU Integration and Demonstration
### 实验8 — CPU集成与演示

将前面所有模块集成为一个可编程8位CPU，并运行完整汇编程序。

#### 1. 实验目标
完成本实验后，学生应能够：

1. 连接数据通路、存储器、ALU、寄存器和微程序控制器；
2. 加载由汇编器生成的程序 ROM 镜像；
3. 加载由微程序编译器生成的控制 ROM 镜像；
4. 在微步级和指令级调试执行过程；
5. 演示一个可工作的可编程CPU。

本实验对应理论课 **第4章：指令系统与CPU体系结构**，并综合第1至第3章内容。

#### 2. 知识点
- 完整CPU结构是数据通路与控制器的集成。
- 复位过程与初始状态。
- 指令级执行与微步级执行。
- 可观察性：用探针暴露关键内部状态。
- 验收测试：用独立程序证明CPU能够工作。
- 工程取舍：能被验证的简单设计优于无法调通的复杂设计。

#### 3. 实验任务
按照[`final_report.md`](/Lab/Lab8/final_report.md)的内容撰写最终报告。

#### 4. 实验报告提交
建议按照如下的文件组织方式提交所有文件(LogicCircuit 工程文件，python 文件， 汇编程序，微程序镜像和Markdown报告)：

```text
final_cpu_project/
  hardware/
    *.CircuitProject
  software/
    assembler.py
    instruction.py
    hardware.py
    microprogram.py
  programs/
    add_demo.asm
    add_demo.bin
    if_demo.asm
    if_demo.bin
    loop_demo.asm
    loop_demo.bin
    microprogram.bin
  report/
    PCO_姓名_final_report.md
    PCO_姓名_final_report.pdf
    images/
```
将所有文件压缩成 `PCO_FinalReport_姓名.zip`，邮件发送到`xsun@gzhu.edu.cn`,邮件主题：`PCO-FinalReport`

截止日期（过期提交无成绩）: **2026年7月12日（第19周周日）前**。

**注：此提交就是期末考查，决定理论课成绩的50%，实验课成绩的30%, 不按时提交视为缺考，请认真对待！！**