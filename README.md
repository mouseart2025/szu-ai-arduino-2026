# 柴火创客学院 · M0 零基础智能硬件入门

> AI 帮你写代码 · 硬件动起来 · 课程统一仓库

## 这是什么？

柴火创客学院 **M0 零基础智能硬件入门** 的课程开发仓库，服务于柴火各类合作项目（高校课程、中小学工作坊、教师培训、公益活动等）。学员使用 AI CLI 工具（OpenCode 等）在本仓库中完成硬件编程项目——**你说想法，AI 写代码，硬件动起来**。

AI 工具启动后会自动读取 `CLAUDE.md`，获得完整的硬件平台信息和开发规范，从而能够根据你的需求描述直接生成可编译运行的代码。

## 开始前 · 先装好 3 样东西

- ✅ **Arduino IDE** · https://www.arduino.cc/en/software
- ✅ **AI CLI**（推荐 OpenCode）· 终端里 `opencode --version` 能看到版本号
- ✅ **本仓库**
  ```bash
  git clone https://github.com/mouseart2025/szu-ai-arduino-2026.git
  cd szu-ai-arduino-2026
  ```

## 第一次成功 · 找到你手上的硬件

在仓库目录下启动 `opencode`，**把对应硬件的 Prompt 整段复制给 AI**。
目标：环境打通 + 看到硬件有反应。

### 🟢 我拿的是 Grove Beginner Kit

````
我在 M0 课程仓库, 请帮我完成:
1. 找到 Arduino IDE 内置的 arduino-cli 路径
2. 检查 arduino:avr 板卡包是否已装, 没装就装上
3. arduino-cli board list 获取端口
4. 进入 examples/01-led-blink, 编译上传 (FQBN: arduino:avr:uno)
5. 上传成功后告诉我: 板上 D4 脚位的 LED 应该开始 1 秒闪烁
````

### 🔵 我拿的是 Wio Terminal

````
我在 M0 课程仓库, 手里是 Wio Terminal, 请帮我完成:
1. 找到 Arduino IDE 内置的 arduino-cli 路径
2. 加入 Seeed 板卡 URL (https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json) 并装 Seeeduino:samd 板卡包
3. arduino-cli board list 获取端口
4. 进入 examples/04-wio-hello-screen, 编译上传 (FQBN: Seeeduino:samd:seeed_wio_terminal)
5. 上传成功后告诉我: 屏幕应该显示 "AI Maker Camp" + "Wio Terminal Ready!", 按 A/B/C 按钮底部会有反馈
````

> 上传失败？**快速拨动侧面开关两次**进 bootloader 模式（蓝色 LED 呼吸闪烁），再试一次。

### 🟣 我拿的是 XIAO ESP32S3 Sense

````
我在 M0 课程仓库, 手里是 XIAO ESP32S3 Sense, 我在中国大陆, 请帮我完成:
1. 阅读 CLAUDE.md 中「ESP32 板卡包装不上？（中国大陆网络兜底方案）」小节
2. 按那个硬规则 + 5 步流程装 esp32:esp32@2.0.17-cn (走乐鑫中国镜像, 3-8 分钟)
3. 写一个最小草图让板载 LED 闪烁:
   - LED_BUILTIN 是 GPIO21, **反逻辑** (LOW 点亮, HIGH 熄灭)
   - 亮 500ms, 灭 500ms, 循环
4. 编译时加 --build-property "build.extra_flags=-DBOARD_HAS_PSRAM"
5. arduino-cli board list 获取端口后上传
6. 上传成功后告诉我: 板上小 LED 应该开始 0.5 秒闪烁
````

> **装板卡包卡住 / 超时 / 失败？** 看 `CLAUDE.md` 中「ESP32 板卡包装不上？（中国大陆网络兜底方案）」—— 硬规则 + 5 步标准流程, 2026/4 深职大 40 位教师验证通过, 实测 3 分 37 秒装完。

## 做自己的项目

环境通了之后：

```
写 requirements.md  →  AI 读需求 + 生成代码  →  编译上传  →  验收  →  迭代
```

在 `students/` 下新建项目文件夹，写 `requirements.md` 用自然语言描述你想做什么（参考 `templates/` 里对应硬件的模板），然后让 AI 读它生成代码。

## 仓库结构

```
szu-ai-arduino-2026/
├── CLAUDE.md                  # AI 上下文（硬件信息 + 开发规范 + ESP32 装包兜底）
├── README.md                  # 你正在看的这份
├── hardware/                  # 硬件参考手册
│   ├── grove-beginner-kit.md
│   ├── wio-terminal.md
│   └── xiao-esp32s3-sense.md
├── examples/                  # 已验证的示例项目（可直接跑）
│   ├── 01-led-blink/          # Grove: LED 闪烁
│   ├── 02-button-led/         # Grove: 按钮控 LED
│   ├── 03-sensor-oled/        # Grove: 传感器 + OLED
│   └── 04-wio-hello-screen/   # Wio Terminal: 屏幕验证
├── templates/                 # 项目模板（复制一份开始做自己的）
│   ├── grove-project/
│   ├── wio-terminal-project/
│   └── xiao-project/
└── students/                  # 你的项目放这里
```

## 硬件平台

| 阶段 | 设备 | 说明 |
|:---:|---|---|
| 入门 | Grove Beginner Kit | 11 模块一体板，Seeeduino Lotus 主控 |
| 进阶 | Wio Terminal | 带彩色屏幕 + 按钮 / 摇杆 / 板载传感器的一体化交互设备 |
| AI 视觉 | XIAO ESP32S3 Sense | 拇指大小，内置摄像头 + WiFi + 麦克风 |

> 不同合作项目可按需选用其中 1–3 块板。M0 是"零基础 + AI 协助"的方法论，不是特定硬件。

## 卡住了找谁

- **现场培训 / 工作坊中** → 问身边的讲师 / 助教
- **回家自学卡住** → 把报错截图 + 你做了什么 + 期望什么 + 实际什么, 一起丢给 AI（OpenCode / 豆包 / DeepSeek / Kimi 都行），大概率能解
- **还是不行** → GitHub Issues 提问, 或联系柴火助教团队

## 讲师团队

冯磊、胡慧东、高宇星、邝钟伦 | 柴火创客空间
