# Word Trainer · V1.0 需求文件与开发步骤

> 项目：词卡背单词（Word Trainer）
> 定位：C++ 三合一练习项目 —— 控制台词库管理 + Raylib 图形卡片学习
> 前置技能：控制台熟练、Raylib 基础（字库/键盘/绘制）、C++ 入门（struct/vector/string）
> 模板：需求 → 开发步骤（每步可编译运行，不跳步）

---

## 一、项目背景与目标

做一个小工具：**自己维护词库（控制台），用卡片翻面学习单词（图形窗口）**。

```
控制台（管词库）                        Raylib 窗口（学单词）
word_trainer.exe --manage list   →     卡片正面：apple
word_trainer.exe --manage add    →     [回车] 翻面
word_trainer.exe --manage remove →     卡片反面：苹果
                                      [Y] 认识 / [N] 不认识 → 下一张
```

学完一轮，把"认识/不认识"结果写回词库文件——**下次优先出你不认识的**（V1.5 再做，V1.0 先记录）。

## 二、功能需求

### 模式一：控制台词库管理（--manage）

| 编号 | 功能 | 说明 |
|---|---|---|
| F1 | list | 打印词库全部单词（序号 + 英文 + 中文 + 记忆状态） |
| F2 | add | 追加一个单词（英文,中文） |
| F3 | remove | 按序号删除一个单词 |
| F4 | count | 统计词库总数 |
| F5 | 词库文件 | CSV 格式：`english,chinese,right,wrong` 每行一个单词，文件不存在自动创建 |

### 模式二：图形卡片学习（--learn，默认）

| 编号 | 功能 | 说明 |
|---|---|---|
| F6 | 卡片显示 | 窗口显示单词英文（大字），下方进度"第 3/20 张" |
| F7 | 翻面 | 按回车：英文 → 中文 |
| F8 | 自测记录 | 翻面后按 Y（认识）/ N（不认识），right/wrong +1，自动下一张 |
| F9 | 进度条 | 顶部进度条：已学/总数 |
| F10 | 学习报告 | 学完一轮：显示正确率 + 用时（秒） |
| F11 | 状态写回 | 学习结束把 right/wrong 保存回 CSV（下次接着累计） |
| F12 | 空词库处理 | 词库为空时窗口显示提示，不崩溃 |

### 命令行接口

```text
word_trainer.exe [--manage] <词库路径>
  --manage    控制台管理模式（子命令：list / add / remove / count）
  无 --manage 图形学习模式（默认）
  示例：
    word_trainer.exe --manage words.csv list
    word_trainer.exe --manage words.csv add "apple,苹果"
    word_trainer.exe --manage words.csv remove 3
    word_trainer.exe words.csv          ← 图形学习
```

## 三、技术要点（本轮新知识）

| 知识点 | 用途 | 类比 |
|---|---|---|
| `ifstream` / `ofstream` | 读/写词库文件（fstream 文件流） | 打开档案柜读写 |
| CSV 简单解析 | 按逗号拆行、按行还原 | 表格每一行分栏 |
| `argc` / `argv` | 命令行参数解析（main 的入口参数） | 给程序传纸条 |
| `vector` 增删 | 单词列表的 push_back / erase | 名单加人删人 |
| 状态机（回忆猜数字） | 卡片正面 → 翻面 → 自测 | 每张卡片的生命周期 |

复用已会技能：raylib 字库加载（common_chars.txt + LoadFontEx）、GetKeyPressed、游戏循环、struct 封装。

## 四、开发步骤（每步可独立编译运行）

**第 1 步：struct Word + CSV 读写（纯控制台）**
- `struct Word { string english; string chinese; int right; int wrong; };`
- 写 `loadWords(path, vector<Word>&)` / `saveWords(path, const vector<Word>&)`
- main 里硬编码词库路径，load 后打印数量 —— 验证"文件能读能写"通了

**第 2 步：控制台管理模式（--manage）**
- argc/argv 解析：第二参数 list/add/remove/count
- list 打印全部；add 追加；remove 按序号删；count 统计
- 纯控制台跑通，词库管理闭环

**第 3 步：图形学习模式 · 显示卡片**
- raylib 窗口 + 字库加载（复用猜数字配置）
- loadWords 后，窗口显示第 1 张英文（60px 大字）+ 进度文字
- 按空格 → 下一张（先不做翻面）

**第 4 步：翻面 + 自测 + 自动下一张**
- 回车翻面：英文 → 中文（状态机：FRONT → BACK）
- 翻面后按 Y/N 记录 right/wrong，自动下一张并回到正面
- 学完一轮显示正确率 + 用时

**第 5 步：进度条 + 状态写回**
- 顶部 DrawRectangle 进度条（已学/总数）
- 学习结束 saveWords 写回（right/wrong 累计）
- 完整闭环：管理加词 → 图形学 → 状态存回

**第 6 步：打磨与边界**
- 空词库提示、文件不存在处理、CSV 行解析容错（跳过坏行）
- 界面布局调整（卡片居中、反馈颜色）
- 全流程验收

## 五、验收标准（V1.0 完成 = 全部通过）

1. `--manage add/list/remove/count` 四命令全部可用，CSV 文件内容正确；
2. 图形模式正确显示卡片，回车翻面、Y/N 记录、自动下一张；
3. 学完一轮显示正确率，且 right/wrong 成功写回 CSV（重开程序数值还在）；
4. 空词库、损坏行、文件不存在都不崩溃，有明确提示；
5. 代码模块化：word 模型 / 词库读写 / 控制台命令 / 图形绘制分离。

## 六、学习目标（这一步项目要带走的知识）

- **文件持久化**：数据不只在内存里，能存下来、下次读回来（所有真实程序的起点）
- **命令行参数**：argc/argv——让程序可以被脚本调用（file_sorter 也用得上）
- **双模式架构**：控制台与图形共用一个数据层（词库模块），只是"外壳"不同
- **状态机复用**：猜数字的 state 思维直接迁移到"卡片正/反"状态
