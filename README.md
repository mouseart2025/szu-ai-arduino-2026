# AI 赋能智能硬件创客训练营 · 课程仓库（Arduino CLI 版）

> 深圳大学 × 柴火创客学院 | 2026 春季

## 这是什么？

这是课程开发仓库的 **Arduino CLI 版本**，使用学生已安装的 Arduino IDE 内置的 `arduino-cli` 进行编译和上传，**不需要额外安装 PlatformIO**。

适用场景：
- 学生已安装 Arduino IDE 2.x（L1 课程要求）
- PlatformIO 工具链下载受网络限制
- 希望零额外安装直接开始 Vibe Coding

## 与 PlatformIO 版仓库的区别

| 对比 | PlatformIO 版 (szu-ai-maker-2026) | Arduino CLI 版（本仓库） |
|---|---|---|
| 编译工具 | PlatformIO CLI（需额外安装） | Arduino IDE 内置 arduino-cli（已有） |
| 项目结构 | `platformio.ini` + `src/main.cpp` | `文件夹名.ino`（Arduino 标准） |
| 工具链 | 需要下载 PlatformIO packages | **复用 Arduino IDE 已下载的工具链** |
| 命令 | `pio run -t upload` | `arduino-cli compile -u` |

## 快速开始

```bash
# 1. 启动 AI CLI 工具
opencode

# 2. 告诉 AI 完成环境准备
> 请帮我完成以下准备工作：
> 1. 克隆课程仓库 https://github.com/mouseart2025/szu-ai-arduino-2026.git
> 2. 切换到 szu-ai-arduino-2026 目录
> 3. 找到我电脑上 Arduino IDE 内置的 arduino-cli 路径
> 4. 检查 Seeeduino:avr 板卡包是否已安装，没有就帮我安装
> 5. 进入 examples/01-led-blink，编译并上传到开发板
> 6. 阅读 CLAUDE.md，告诉我这个项目支持哪些硬件
```

## 仓库结构

```
szu-ai-arduino-2026/
├── CLAUDE.md               # AI 上下文（硬件信息 + arduino-cli 用法）
├── hardware/               # 硬件参考文档
│   └── grove-beginner-kit.md
├── examples/               # 已验证的示例项目
│   ├── 01-led-blink/
│   ├── 02-button-led/
│   └── 03-sensor-oled/
├── templates/              # 项目模板
│   └── grove-project/
└── students/               # 学生项目目录
```

## 讲师

冯磊、胡慧东 | 柴火创客空间
