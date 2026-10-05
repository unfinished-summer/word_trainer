# Word Trainer 背单词工具

基于 C++20 的命令行单词记忆训练工具，支持 CSV 词库管理与按日期自动调度复习；V2.0 迭代接入 raylib 图形界面。项目从学习仓库中独立拆分（git subtree 迁移，保留完整提交历史）。

## 项目功能

- 背词模式：默认启动，按上次学习日期自动筛选今天该复习的词
- 管理模式：`--manage` 参数进入，管理词库
- 词库存储：`words.csv`，一行一词，读写稳定
- 复习调度：`shouldReview` 判断到期词，`daysSince` 计算复习间隔
- 图形界面（V2.0 迭代）：raylib 渲染

## 构建运行

### 依赖

- CMake 3.10+，支持 C++20 的编译器
- raylib 5.5（CMake FetchContent 自动拉取源码编译，无需手动安装）
- 首次构建需联网下载 raylib（约 1 分钟）

### 构建运行（Visual Studio）

1. 用 VS 打开 `word-trainer` 文件夹；
2. 顶部选择 x64 配置，点击「生成」（首次自动下载依赖）；
3. 按 `F5` 运行。

### 构建运行（命令行）

```
cmake -B build
cmake --build build
build\word-trainer.exe
```

## 使用方式

```
word-trainer               # 背词模式（默认）
word-trainer --manage      # 管理模式
```

## 项目目录结构

```
word-trainer/
├── word_trainer.cpp    # 入口：模式分发（背词 / 管理）
├── word.h              # 单词数据结构
├── wordbank.h/.cpp     # 词库 CSV 读写、复习调度
├── ui.h / ui.cpp       # 界面层（控制台 + raylib 图形界面）
├── console.h / .cpp    # 控制台交互辅助
├── date_util.h / .cpp  # 日期工具：今天日期、间隔天数
├── path_util.h / .cpp  # 路径工具
├── words.csv           # 词库数据
├── CMakeLists.txt      # 构建配置（FetchContent 拉取 raylib）
├── CMakePresets.json   # CMake 预设
└── docs/               # 需求文档、经验总结、代码体检报告
```

## 开发文档

- `word-trainer-V1.0需求与开发步骤.md` / `V1.5` / `V2.0` — 分版本需求与开发计划
- `词卡背单词V1.0总结与经验.md` / `V1.5` — 迭代经验沉淀
- `docs/code-review/代码体检报告.html` — 代码质量体检报告

## 编码约定

- 源码 UTF-8 无 BOM，MSVC 加 `/utf-8` 编译选项
- 控制台启动时 `chcp 65001`，保证中文正常显示