### Lab 1 — LogicCircuit, NAND-based Building Blocks and Markdown Report
### 实验1——LogicCircuit、基于NAND的基本部件和Markdown报告

*2025-2026-2 Principal of Computer Organization
Xuelong SUN @ GZHU*

#### 1. Goal / 实验目标:

完成本实验后，能够：
1. 创建 LogicCircuit 工程，并用层次化子电路组织设计；
2. 仅用 NAND 门构造基本逻辑门；
3. 构造并验证半加器和全加器；
4. 使用开关、常量、探针和截图展示测试证据；
5. 使用 Markdown 撰写结构清晰的实验报告。

#### 2. Knowledge / 知识点：
##### 2.1 LogicCircuit
+ 安装：可在软件的[官网](https://www.logiccircuit.org/)下载安装包。
+ 官方文档：https://www.logiccircuit.org/help.html
+ 基本操作：新建工程、放置元件、连线、输入输出与电路测试。

##### 2.2 Markdown基本语法
+ 本质是一种文本文档`.md`，语法简明，撰写快速方便，只关心内容，不在乎格式的沉浸式表达。
+ 学习Markdown:
  + 可参考：https://markdown.com.cn/basic-syntax/links.html,
  + 一个互动性更强的教程: https://commonmark.org/help/tutorial/
+ 章节、段落、文字样式、表格，图片，代码块，数学公式，超链接与文内引用

##### 2.3 NAND 基本部件
本实验对应理论课 **第1章：数的表示与计算**，尤其是从 NAND 逻辑到算术电路的构造路径。

Key Concept / 关键概念：
- Boolean value: `0` and `1`. 
  布尔值：`0` 与 `1`。
- NAND gate: a functionally complete logic gate. 
  NAND 门：功能完备逻辑门。
- Truth table: an exhaustive description of a combinational circuit.
  真值表：组合逻辑功能的完整描述。
- Combinational circuit: output depends only on current input.
  组合电路：输出只取决于当前输入。
- Subcircuit hierarchy: complex systems should be built from reusable modules (Abstraction).
  复杂系统应由可复用模块逐步构建 (抽象)。
- Verification: a circuit is not considered complete until its behavior is tested and recorded.
  验证：没有测试和记录证据的电路不能视为完成。

#### 3. Markdown quick start / Markdown 快速入门

所有实验报告均使用 Markdown。最基本的报告应包含标题、正文、表格、代码块、图片和简短反思。

建议使用Visual Studio Code安装Markdown插件（边写边预览）来完成实验报告的撰写:

```markdown
# 实验1 - 题目
*姓名 学号*

## 1. 实验目标
说明本实验希望完成什么。

## 2. 实验内容
### 2.1 任务1 - 标题
#### 2.1.1 内容：
解释电路的主要设计思路。
| A | B | XOR期望值 | XOR实际值 |
|---|---|---:|---:|
| 0 | 0 | 0 | 0 |
| 0 | 1 | 1 | 1 |
##### 2.1.2 结果与验证：
![全加器测试](images/lab1_full_adder.png)
### 2.2 任务2 - 标题
#### 2.2.1 内容：
##### 2.2.2 验证：

## 3. 实验总结与反思
- 遇到了什么困难？如何定位和解决问题？
- 有什么新的认识与思考？
```

建议规则：

- 使用一个 `#` 作为报告标题，再用 `##` 组织章节。
- 所有截图放入 `images/` 文件夹并清晰命名,推荐截图软件:[PixPin](https://pixpin.cn/)。
- 真值表和测试用例尽量用表格表达。
- 程序、输入输出可用代码块。
- 运算表达式请使用`LaTex`公式
- 不要只提交截图；每张截图都应说明它证明了什么。
- 一定要有反思和总结。

#### 4. 实验任务

##### 任务1：基于 NAND 的门电路库

仅使用 NAND 门构建以下子电路：

- `NAND_NOT`
- `NAND_AND`
- `NAND_OR`
- `NAND_XOR`

每个门电路都要给出真值表，并用开关和探针测试。

##### 任务2：加法器

构造：

- `HALF_ADDER` 半加器；
- `FULL_ADDER` 全加器。

全加器必须包含输入 `A`、`B`、`Cin`，输出 `Sum`、`Cout`。

##### 任务3：可选扩展

用四个全加器构造4位串行进位加法器。该任务为实验3中的8位ALU打基础。

#### 5. 实验报告提交
把：
1. LogicCircuit 工程文件 (`*.CircuitProject`)；
2. `PCO_Lab1_姓名.md`；
3. `images/` 中的截图；

压缩成 `PCO_Lab1_姓名.zip`，邮件发送到`xsun@gzhu.edu.cn`,邮件主题：`PCO-Lab1-Assignment`

截止日期（过期提交无成绩）: **2026年5月8日（第9周周五）前**。

#### 6. 报告评分标准

| 评分项 | 权重 | 说明 |
|---|---:|---|
| 目标与概念解释 | 20% | 能清楚解释 NAND 完备性、真值表和组合电路 |
| 电路设计 | 25% | 门电路与加法器结构正确，层次清晰，信号命名规范 |
| 验证证据 | 25% | 真值表完整，截图能够证明电路行为正确 |
| Markdown 质量 | 20% | 章节、表格、图片和格式清晰 |
| 反思 | 10% | 能说明遇到的问题、调试方法和收获 |