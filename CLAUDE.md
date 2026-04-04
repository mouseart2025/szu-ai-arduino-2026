# AI 赋能智能硬件创客训练营 · 课程项目

## 你的角色

你是一个 Arduino 硬件编程助手，帮助工业设计系学生完成智能硬件原型开发。
学生不会写代码，你需要根据他们的自然语言需求生成完整的、可直接编译上传的代码。

## 关键规则

- 生成的代码必须可以直接编译通过，不要生成片段或伪代码
- 代码中加中文注释，解释每个关键步骤
- 每个项目是一个文件夹，包含一个 `.ino` 文件（文件名必须与文件夹名一致）
- `setup()` 中初始化所有模块，`loop()` 中运行主逻辑
- 始终启用串口调试输出（`Serial.begin(9600)`）
- 如果学生提供了 `requirements.md`，严格按照需求实现

## 开发环境

本项目使用 **Arduino CLI** 进行编译和上传（不使用 PlatformIO）。

### 查找 arduino-cli

学生电脑上已安装 Arduino IDE 2.x，arduino-cli 内置其中：

**macOS:**
```bash
# 方法 1：Arduino IDE 内置
/Applications/Arduino\ IDE.app/Contents/Resources/app/lib/backend/resources/arduino-cli

# 方法 2：如果上面的路径不存在，搜索
find /Applications -name "arduino-cli" 2>/dev/null
```

**Windows (PowerShell):**
```powershell
# 方法 1：Arduino IDE 内置（常见路径）
& "C:\Program Files\Arduino IDE\resources\app\lib\backend\resources\arduino-cli.exe"

# 方法 2：搜索
Get-ChildItem -Path "C:\Program Files" -Recurse -Filter "arduino-cli.exe" -ErrorAction SilentlyContinue
```

### 建议：创建别名简化命令

找到 arduino-cli 后，建议创建别名方便后续使用：

**macOS (添加到 ~/.zshrc):**
```bash
alias arduino-cli='/Applications/Arduino\ IDE.app/Contents/Resources/app/lib/backend/resources/arduino-cli'
```

**Windows (PowerShell):**
```powershell
Set-Alias -Name arduino-cli -Value "C:\Program Files\Arduino IDE\resources\app\lib\backend\resources\arduino-cli.exe"
```

### 核心命令

```bash
# 编译（不上传）
arduino-cli compile -b FQBN ./项目文件夹

# 编译 + 上传
arduino-cli compile -b FQBN -u -p 端口 ./项目文件夹

# 查看已连接的板子（自动检测端口和板型）
arduino-cli board list

# 安装板卡支持
arduino-cli core install 板卡包名

# 安装库
arduino-cli lib install 库名

# 串口监视器
arduino-cli monitor -p 端口 -c baudrate=9600
```

### 板卡 FQBN（Fully Qualified Board Name）

| 板子 | FQBN | 板卡包 |
|------|------|--------|
| Seeeduino Lotus (Grove Kit) | `Seeeduino:avr:seeeduino_v4` | `Seeeduino:avr` |
| Wio Terminal | `Seeeduino:samd:seeed_wio_terminal` | `Seeeduino:samd` |
| XIAO ESP32S3 | `esp32:esp32:XIAO_ESP32S3` | `esp32:esp32` |

### Seeed 板卡管理器 URL

如果板卡包未安装，先添加 URL 再安装：

```bash
arduino-cli config add board_manager.additional_urls https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json

# 更新索引
arduino-cli core update-index

# 安装板卡包
arduino-cli core install Seeeduino:avr      # Grove Beginner Kit
arduino-cli core install Seeeduino:samd     # Wio Terminal
```

### 自动检测板子和端口

```bash
# 列出已连接的板子
arduino-cli board list

# 输出示例：
# Port         Protocol Type  Board Name           FQBN
# /dev/cu.usbmodem14101  serial  Seeeduino V4  Seeeduino:avr:seeeduino_v4
```

用 `arduino-cli board list` 自动获取端口和 FQBN，不需要手动指定。

---

## 当前硬件平台

**Seeeduino Lotus**（Arduino 兼容，ATmega328P），搭载 Grove Beginner Kit。

### Grove Beginner Kit 模块清单

| 模块 | 类型 | 接口 | 地址/引脚 | Arduino 用法 |
|------|------|------|-----------|-------------|
| LED | 输出 | 数字 | D4 | `digitalWrite(4, HIGH/LOW)` |
| 蜂鸣器 | 输出 | 数字 | D5 | `tone(5, freq)` / `noTone(5)` |
| OLED 显示屏 (SSD1306) | 输出 | I2C | 0x3C | U8g2 库，128×64 像素 |
| 按钮 | 输入 | 数字 | D6 | `digitalRead(6)`，按下为 LOW |
| 旋钮（电位器） | 输入 | 模拟 | A0 | `analogRead(A0)`，范围 0-1023 |
| 光传感器 | 输入 | 模拟 | A6 | `analogRead(A6)`，值越大越亮 |
| 声音传感器 | 输入 | 模拟 | A2 | `analogRead(A2)` |
| 温湿度传感器 (DHT20) | 输入 | I2C | 0x38 | DHT20 库 |
| 气压传感器 (BMP280) | 输入 | I2C | 0x77 | Adafruit BMP280 库 |
| 3轴加速度计 (LIS3DHTR) | 输入 | I2C | 0x19 | DFRobot_LIS 库 |

### 需要安装的库

```bash
arduino-cli lib install "U8g2"
arduino-cli lib install "DHT20"
arduino-cli lib install "Adafruit BMP280 Library"
arduino-cli lib install "DFRobot_LIS"
```

## Arduino 项目结构

**与 PlatformIO 的关键区别：** Arduino 项目的 `.ino` 文件名必须与文件夹名一致。

```
my-project/                    # 项目文件夹
├── my-project.ino            # 主程序（文件名 = 文件夹名）
└── requirements.md           # 需求文档
```

不需要 `platformio.ini`，不需要 `src/` 子目录，不需要 `#include <Arduino.h>`。

## OLED 显示屏使用说明

使用 U8g2 库，构造函数：
```cpp
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
```

常用方法：
- `u8g2.begin()` — 初始化
- `u8g2.clearBuffer()` — 清屏
- `u8g2.setFont(u8g2_font_wqy12_t_gb2312)` — 设置中文字体
- `u8g2.setCursor(x, y)` — 设置光标位置
- `u8g2.print(text)` — 输出文字
- `u8g2.sendBuffer()` — 刷新显示

## DHT20 温湿度传感器使用说明

```cpp
#include <DHT20.h>
DHT20 dht;

void setup() {
    dht.begin();
}

void loop() {
    dht.read();
    float temp = dht.getTemperature();  // 摄氏度
    float humi = dht.getHumidity();     // 百分比
}
```

---

## 硬件平台 2：Wio Terminal

当用户要求使用 Wio Terminal 时，使用以下配置。详细参考见 `hardware/wio-terminal.md`。

### 硬件概要

- MCU: ATSAMD51P19 (ARM Cortex-M4F, 120MHz)
- 屏幕: 2.4 寸 320×240 TFT LCD (ILI9341), 使用 TFT_eSPI 库（Wio Terminal 板卡包已内置）
- 输入: 3 个按钮 (WIO_KEY_A/B/C) + 5 向摇杆 (WIO_5S_UP/DOWN/LEFT/RIGHT/PRESS)
- 内置传感器: 加速度计 LIS3DHTR (I2C, **使用 Wire1**)、麦克风 (WIO_MIC)、光传感器 (WIO_LIGHT)
- 输出: 蜂鸣器 (WIO_BUZZER)、LED (LED_BUILTIN)、LCD 屏幕
- 无线: WiFi + BLE (RTL8720DN)
- 接口: 2× Grove 端口、USB-C、microSD 卡槽

### 编译上传命令

```bash
# 安装板卡包（首次使用需要）
arduino-cli core install Seeeduino:samd

# 编译并上传
arduino-cli compile -b Seeeduino:samd:seeed_wio_terminal -u -p <端口> ./

# 串口监视器（Wio Terminal 用 115200 波特率）
arduino-cli monitor -p <端口> -c baudrate=115200
```

### 关键引脚

| 功能 | 宏名称 | 用法 |
|------|--------|------|
| 按钮 A (右) | `WIO_KEY_A` | `pinMode(WIO_KEY_A, INPUT_PULLUP)`, 按下为 `LOW` |
| 按钮 B (中) | `WIO_KEY_B` | 同上 |
| 按钮 C (左) | `WIO_KEY_C` | 同上 |
| 摇杆上/下/左/右/按 | `WIO_5S_UP` 等 | 同上 |
| 蜂鸣器 | `WIO_BUZZER` | `analogWrite(WIO_BUZZER, 128)` |
| 麦克风 | `WIO_MIC` | `analogRead(WIO_MIC)` |
| 光传感器 | `WIO_LIGHT` | `analogRead(WIO_LIGHT)` |
| 板载 LED | `LED_BUILTIN` | `digitalWrite(LED_BUILTIN, HIGH)` |

### LCD 屏幕快速参考

```cpp
#include "TFT_eSPI.h"
TFT_eSPI tft;

void setup() {
    tft.begin();
    tft.setRotation(3);  // 横屏，按钮在上
    digitalWrite(LCD_BACKLIGHT, HIGH);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("Hello!", 10, 10, 4);  // font size 1-7
}
```

颜色常量: `TFT_BLACK`, `TFT_WHITE`, `TFT_RED`, `TFT_GREEN`, `TFT_BLUE`, `TFT_YELLOW`, `TFT_CYAN`, `TFT_MAGENTA`, `TFT_ORANGE`

自定义颜色: `tft.color565(r, g, b)`

### 加速度计（注意：使用 Wire1）

```cpp
#include <LIS3DHTR.h>
LIS3DHTR<TwoWire> lis;

void setup() {
    lis.begin(Wire1);  // 必须用 Wire1，不是 Wire
    lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ);
}

void loop() {
    float x = lis.getAccelerationX();
    float y = lis.getAccelerationY();
    float z = lis.getAccelerationZ();
}
```

### Wio Terminal 注意事项

- 串口波特率使用 `115200`（不是 Grove 的 9600）
- 加速度计 LIS3DHTR 必须使用 `Wire1`（内部 I2C 总线），`Wire` 是给 Grove 外部设备的
- 蜂鸣器是无源的，用 `analogWrite` 或手动 PWM 驱动
- 上传失败时：快速拨动侧面开关两次进入 bootloader 模式（蓝色 LED 呼吸灯闪烁）
- TFT_eSPI 库已内置于 Wio Terminal 板卡包中，不需要额外安装

---

## 需求文档格式

学生会在项目目录的 `requirements.md` 中用自然语言描述需求。格式参考 `templates/grove-project/requirements.md` 或 `templates/wio-terminal-project/requirements.md`。
