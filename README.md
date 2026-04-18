# 柴火创客学院 · M0 零基础智能硬件入门

> AI 帮你写代码 · 硬件动起来 · 课程统一仓库

## 这是什么？

这是柴火创客学院 **M0 零基础智能硬件入门** 的课程开发仓库，服务于柴火各类合作项目（高校课程、中小学工作坊、教师培训、公益活动等）。学员使用 AI CLI 工具（OpenCode 等）在本仓库中完成硬件编程项目。

AI 工具启动后会自动读取 `CLAUDE.md`，获得完整的硬件平台信息和开发规范，从而能够根据你的需求描述直接生成可编译运行的代码。

**你只需要安装过 Arduino IDE，不需要额外安装其他开发工具。**

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
├── CLAUDE.md               # AI 上下文（硬件信息 + 开发规范）
├── hardware/               # 硬件参考文档
│   └── grove-beginner-kit.md
├── examples/               # 已验证的示例项目
│   ├── 01-led-blink/       # Grove: LED 闪烁
│   ├── 02-button-led/      # Grove: 按钮控 LED
│   ├── 03-sensor-oled/     # Grove: 传感器 + OLED
│   └── 04-wio-hello-screen/# Wio Terminal: 屏幕验证
├── templates/              # 项目模板
│   ├── grove-project/      # Grove Beginner Kit 项目模板
│   └── wio-terminal-project/ # Wio Terminal 项目模板
└── students/               # 学生项目目录
```

## 硬件平台

| 阶段 | 设备 | 说明 |
|:---:|---|---|
| 入门 | Grove Beginner Kit | 11 模块一体板，Seeeduino Lotus 主控 |
| 进阶 | Wio Terminal | 带彩色屏幕 + 按钮 / 摇杆 / 板载传感器的一体化交互设备 |
| AI 视觉 | XIAO ESP32S3 Sense | 拇指大小，内置摄像头 + WiFi + 麦克风 |

> 不同合作项目可按需选用其中 1–3 块板。M0 是"零基础 + AI 协助"的方法论，不是特定硬件。

## 工作流

```
写 requirements.md  →  AI 读需求 + 生成代码  →  编译上传  →  验收  →  迭代
```

## 讲师团队

冯磊、胡慧东、高宇星、邝钟伦 | 柴火创客空间
