# Grove Beginner Kit for Arduino

> 官方 Wiki: https://wiki.seeedstudio.com/cn/Grove-Beginner-Kit-For-Arduino

## 概述

Grove Beginner Kit 是 Seeed Studio 推出的 Arduino 入门套件，一块 PCB 上集成了 Seeeduino Lotus 主控板和 10 个 Grove 模块，无需焊接和接线即可使用。

## 主控板

**Seeeduino Lotus** — Arduino UNO 兼容
- MCU: ATmega328P
- 时钟: 16MHz
- Flash: 32KB
- SRAM: 2KB
- 工作电压: 5V
- USB: Micro-USB（供电 + 编程）

## 模块清单

### 感知能力（传感器）

| 模块 | 型号 | 接口 | 地址/引脚 | 量程/说明 |
|------|------|------|-----------|----------|
| 光传感器 | — | 模拟 | A6 | 0-1023，值越大越亮 |
| 声音传感器 | — | 模拟 | A2 | 0-1023，检测声音强度 |
| 温湿度传感器 | DHT20 | I2C | 0x38 | 温度 -40~80°C，湿度 0-100% |
| 气压传感器 | BMP280 | I2C | 0x77 | 300-1100 hPa |
| 3轴加速度计 | LIS3DHTR | I2C | 0x19 | ±2g/±4g/±8g/±16g |

### 表达能力（执行器）

| 模块 | 接口 | 引脚 | 用法 |
|------|------|------|------|
| LED | 数字 | D4 | `digitalWrite(4, HIGH)` 亮，`LOW` 灭 |
| 蜂鸣器 | 数字 | D5 | `tone(5, freq)` 发声，`noTone(5)` 停 |
| OLED 显示屏 | I2C | 0x3C | 128×64 SSD1306，使用 U8g2 库 |

### 交互能力（用户输入）

| 模块 | 接口 | 引脚 | 用法 |
|------|------|------|------|
| 按钮 | 数字 | D6 | `digitalRead(6)`，按下为 LOW，松开为 HIGH |
| 旋钮（电位器） | 模拟 | A0 | `analogRead(A0)`，范围 0-1023 |

### 核心控制

| 模块 | 说明 |
|------|------|
| Seeeduino Lotus | 主控 MCU，运行 Arduino 程序 |
| Grove 接口 | 可通过 Grove 线缆连接外部模块 |

## 系统模型

```
感知（输入）  ──→  逻辑（Seeeduino Lotus）  ──→  表达/交互（输出）
```

## PlatformIO 开发环境

```ini
[env:seeeduino_lotus]
platform = atmelavr
board = seeeduino_v4
framework = arduino
monitor_speed = 9600
lib_deps =
    olikraus/U8g2@^2.35.4
    robtillaart/DHT20@^0.3.1
    adafruit/Adafruit BMP280 Library@^2.6.8
    dfrobot/DFRobot_LIS@^1.0.3
```

## 常用命令

```bash
pio run                 # 编译
pio run -t upload       # 编译 + 上传
pio device monitor      # 串口监视器
pio run -t clean        # 清理构建
```

## 注意事项

- 模块可以从 PCB 上掰下来通过 Grove 线缆单独连接，但在课程中建议保持一体
- USB 线必须是数据线（不是充电线），否则无法上传和通信
- 首次使用 PlatformIO 编译时会自动下载工具链，需要网络连接
