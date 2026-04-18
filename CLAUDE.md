# 柴火创客学院 · M0 零基础智能硬件入门 · 项目规范

## 你的角色

你是一个 Arduino 硬件编程助手，帮助零基础学员完成智能硬件原型开发。
学员不会写代码，你需要根据他们的自然语言需求生成完整的、可直接编译上传的代码。

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
| Seeeduino Lotus (Grove Kit) | `arduino:avr:uno` | `arduino:avr` |
| Wio Terminal | `Seeeduino:samd:seeed_wio_terminal` | `Seeeduino:samd` |
| XIAO ESP32S3 | `esp32:esp32:XIAO_ESP32S3` | `esp32:esp32` |

### 板卡管理器 URL

如果板卡包未安装，先添加 URL 再安装：

```bash
# Seeed 板卡（Grove Kit + Wio Terminal）
arduino-cli config add board_manager.additional_urls https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json

# ESP32 板卡（XIAO ESP32S3）· 中国大陆使用乐鑫官方镜像
arduino-cli config add board_manager.additional_urls https://jihulab.com/esp-mirror/espressif/arduino-esp32/-/raw/gh-pages/package_esp32_index_cn.json

# 更新索引
arduino-cli core update-index

# 安装板卡包
arduino-cli core install arduino:avr             # Grove Beginner Kit (使用 Arduino Uno 配置)
arduino-cli core install Seeeduino:samd          # Wio Terminal
arduino-cli core install esp32:esp32@2.0.17-cn   # XIAO ESP32S3（走 dl.espressif.cn 镜像，含工具链，3–8 分钟）
```

### 自动检测板子和端口

```bash
# 列出已连接的板子
arduino-cli board list

# 输出示例：
# Port         Protocol Type  Board Name           FQBN
# /dev/cu.usbmodem14101  serial  Arduino Uno  arduino:avr:uno
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

## 硬件平台 3：XIAO ESP32S3 Sense

当用户要求使用 XIAO ESP32S3 Sense 时，使用以下配置。详细参考见 `hardware/xiao-esp32s3-sense.md`。

### 硬件概要

- MCU: ESP32-S3R8 (Xtensa LX7 双核, 240MHz)
- Flash: 8MB
- PSRAM: 8MB（**摄像头和录音功能必须启用 PSRAM**）
- 摄像头: OV3660 (最高 2048×1536)，兼容 OV2640/OV5640
- 麦克风: PDM 数字麦克风 (CLK=GPIO42, DATA=GPIO41)
- 存储: microSD 卡槽 (CS=GPIO21, 最大 32GB FAT32)
- 无线: WiFi 802.11 b/g/n + BLE 5.0（**不支持蓝牙经典**）
- 用户 LED: GPIO21（**低电平点亮，高电平熄灭**，与 SD 卡 CS 共用）
- 接口: USB-C, I2C (SDA=GPIO5, SCL=GPIO6), SPI, UART
- 尺寸: 21×17.8mm

### 编译上传命令

```bash
# 安装板卡包（首次使用需要 · 中国大陆走乐鑫官方镜像）
arduino-cli config add board_manager.additional_urls https://jihulab.com/esp-mirror/espressif/arduino-esp32/-/raw/gh-pages/package_esp32_index_cn.json
arduino-cli core update-index
arduino-cli core install esp32:esp32@2.0.17-cn

# 编译（必须启用 PSRAM）
arduino-cli compile -b esp32:esp32:XIAO_ESP32S3 --build-property "build.extra_flags=-DBOARD_HAS_PSRAM" ./项目文件夹

# 编译并上传
arduino-cli compile -b esp32:esp32:XIAO_ESP32S3 --build-property "build.extra_flags=-DBOARD_HAS_PSRAM" -u -p <端口> ./项目文件夹

# 串口监视器
arduino-cli monitor -p <端口> -c baudrate=115200
```

### 关键引脚

| XIAO 引脚 | GPIO | 功能 | 备注 |
|-----------|------|------|------|
| D0 | GPIO1 | 模拟/数字/触摸 | |
| D1 | GPIO2 | 模拟/数字/触摸 | |
| D2 | GPIO3 | 模拟/数字/触摸 | |
| D3 | GPIO4 | 模拟/数字/触摸 | |
| D4 | GPIO5 | I2C SDA | |
| D5 | GPIO6 | I2C SCL | |
| D6 | GPIO43 | UART TX | |
| D7 | GPIO44 | UART RX | |
| D8 | GPIO7 | SPI SCK | SD 卡共用 |
| D9 | GPIO8 | SPI MISO | SD 卡共用 |
| D10 | GPIO9 | SPI MOSI | |

Sense 扩展板占用引脚（默认已连接）：

| 功能 | GPIO | 说明 |
|------|------|------|
| 麦克风 CLK | GPIO42 | 不可作 GPIO 使用（除非切割 J1 焊盘） |
| 麦克风 DATA | GPIO41 | 不可作 GPIO 使用（除非切割 J2 焊盘） |
| SD 卡 CS | GPIO21 | 同时也是用户 LED 引脚 |

### 摄像头快速参考

```cpp
#include "esp_camera.h"

// XIAO ESP32S3 Sense 摄像头引脚
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  10
#define SIOD_GPIO_NUM  40
#define SIOC_GPIO_NUM  39
#define Y9_GPIO_NUM    48
#define Y8_GPIO_NUM    11
#define Y7_GPIO_NUM    12
#define Y6_GPIO_NUM    14
#define Y5_GPIO_NUM    16
#define Y4_GPIO_NUM    18
#define Y3_GPIO_NUM    17
#define Y2_GPIO_NUM    15
#define VSYNC_GPIO_NUM 38
#define HREF_GPIO_NUM  47
#define PCLK_GPIO_NUM  13

void setup() {
    Serial.begin(115200);
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.frame_size = FRAMESIZE_VGA;      // 640x480
    config.pixel_format = PIXFORMAT_JPEG;
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.jpeg_quality = 12;
    config.fb_count = 1;

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed: 0x%x\n", err);
        return;
    }
    Serial.println("Camera ready!");
}
```

分辨率选项: `FRAMESIZE_QVGA` (320×240), `FRAMESIZE_VGA` (640×480), `FRAMESIZE_SVGA` (800×600), `FRAMESIZE_XGA` (1024×768), `FRAMESIZE_UXGA` (1600×1200)

### 麦克风快速参考

```cpp
#include <I2S.h>

void setup() {
    Serial.begin(115200);
    I2S.setAllPins(-1, 42, 41, -1, -1);  // CLK=GPIO42, DATA=GPIO41
    if (!I2S.begin(PDM_MONO_MODE, 16000, 16)) {
        Serial.println("I2S init failed!");
        return;
    }
    Serial.println("Microphone ready!");
}

void loop() {
    int sample = I2S.read();
    if (sample && sample != -1 && sample != 1) {
        Serial.println(sample);
    }
}
```

> 注意：采样率固定 16000Hz，位深固定 16-bit，单声道。ESP32 板卡包 2.x 和 3.x 的 I2S API 不同，以上为 2.x 写法。

### SD 卡快速参考

```cpp
#include "FS.h"
#include "SD.h"
#include "SPI.h"

void setup() {
    Serial.begin(115200);
    if (!SD.begin(21)) {  // CS = GPIO21
        Serial.println("SD Card Mount Failed!");
        return;
    }
    // 写文件
    File file = SD.open("/test.txt", FILE_WRITE);
    if (file) {
        file.println("Hello XIAO!");
        file.close();
    }
}
```

### WiFi 快速参考

```cpp
#include <WiFi.h>

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin("SSID", "PASSWORD");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.print("\nIP: ");
    Serial.println(WiFi.localIP());
}
```

### XIAO ESP32S3 Sense 注意事项

- **PSRAM 必须启用**：编译时必须加 `--build-property "build.extra_flags=-DBOARD_HAS_PSRAM"`，否则摄像头和录音功能会失败
- 串口波特率使用 `115200`
- 用户 LED 是**反逻辑**：`digitalWrite(LED_BUILTIN, LOW)` 点亮，`HIGH` 熄灭
- GPIO41/GPIO42 虽标记为模拟引脚但**不支持 ADC**（被麦克风占用）
- SD 卡最大 32GB，必须格式化为 FAT32
- SD 卡与 SPI 共用引脚，不能同时使用外部 SPI 设备和 SD 卡
- 上传失败时：按住 Boot 按钮再按 Reset 进入 BootLoader 模式
- **仅支持 BLE 5.0**，不支持蓝牙经典（Classic Bluetooth）
- WiFi/摄像头长时间运行会发热，建议加散热片
- esp_camera 库已内置于 ESP32 板卡包中，不需要额外安装

### ESP32 板卡包装不上？（中国大陆网络兜底方案）

当学员报告"ESP32 板卡包下载失败 / 超时 / 卡住"时，**按以下硬规则处理**（2026/4 深职大 40 位教师验证通过，实测 3 分 37 秒装完）：

**硬规则（任一条违反立刻停下问学员）**：

- 只能用 `jihulab.com` + `dl.espressif.cn`，**不能**走 `github.com` / `raw.githubusercontent.com` / Google
- 不能自己编造 URL
- 任何一步失败 2 次，停下报告，不要继续瞎试

**标准步骤**：

1. **先检查旧残骸** — 查看 `~/Library/Arduino15/packages/esp32/` (Mac) 或 `%USERPROFILE%\AppData\Local\Arduino15\packages\esp32\` (Windows)：
   - 存在且可能装坏（比如缺 xtensa 工具链）→ 重命名为 `esp32-broken-备份`
   - 不存在 → 跳过

2. **加入乐鑫中国镜像**：
   ```bash
   arduino-cli config add board_manager.additional_urls https://jihulab.com/esp-mirror/espressif/arduino-esp32/-/raw/gh-pages/package_esp32_index_cn.json
   ```

3. **刷新索引**：
   ```bash
   arduino-cli core update-index
   ```

4. **安装带 `-cn` 后缀的版本**（自动从 `dl.espressif.cn` 下载全套含工具链，3–8 分钟）：
   ```bash
   arduino-cli core install esp32:esp32@2.0.17-cn
   ```

5. **验证**：
   - `arduino-cli core list | grep esp32` 应出现 `esp32:esp32 2.0.17-cn INSTALLED`
   - 写最小草图 `/tmp/test/test.ino`：
     ```cpp
     void setup(){}
     void loop(){}
     ```
   - 编译：`arduino-cli compile --fqbn esp32:esp32:XIAO_ESP32S3 /tmp/test`
   - 编译通过 = 成功

**每步做完简短汇报结果。失败原样贴报错，不要隐藏**。

**常见坑**：

| 症状 | 处理 |
| --- | --- |
| `arduino-cli` 命令找不到 | Arduino IDE 自带的可能没加入 PATH，在 Arduino 安装目录里找 `arduino-cli`（Mac: `/Applications/Arduino IDE.app/Contents/Resources/app/lib/backend/resources/arduino-cli`）|
| jihulab 访问慢 / 偶尔超时 | 重试一次即可，这是全国仅存的一个好用镜像 |
| 安装过程中断 | 从上次中断的步骤继续，不要从头 |
| `xtensa-esp32s3-elf-gcc not found` | 工具链没装全，执行 `arduino-cli core install esp32:esp32@2.0.17-cn --force` |
| Arduino IDE 看不到 ESP32 板 | 完全退出 Arduino IDE 再重开；菜单 `工具 → 开发板 → ESP32 Arduino → XIAO_ESP32S3` |
| 想换更新版本 | `2.0.17-cn` 换成 `3.3.8-cn`（最新），其他不变 |

---

## Grove 扩展套件（40 合 1）

学员可以从讲师处借用以下 Grove 模块，通过 Grove 线连接到 Beginner Kit 或 Wio Terminal 的 Grove 接口。设计方案时应优先使用以下可用模块。

### 传感器

| 模块 | 英文名 | 类型 | 说明 |
|------|--------|------|------|
| 超声波测距 | Grove - Ultrasonic Ranger | 数字 | 测距 3–350cm |
| PIR 人体感应 | Grove - Mini PIR Motion Sensor | 数字 | 被动红外，检测人/动物移动 |
| 火焰检测 | Grove - Flame Sensor | 数字/模拟 | 火焰/紫外检测 |
| 触摸开关 | Grove - Touch Sensor | 数字 | 电容式，轻触触发 |
| 水滴检测 | Grove - Water Sensor | 数字 | 水滴/水位接触检测 |
| 土壤湿度 | Grove - Moisture Sensor | 模拟 | 花盆浇水提醒 |
| 霍尔磁传感 | Grove - Hall Sensor | 数字/模拟 | 磁体靠近检测、测速 |
| 振动检测 | Grove - Vibration Sensor (SW-420) | 数字 | 振动/碰撞触发 |
| 循迹传感 | Grove - Line Finder v1.1 | 数字 | 反射式光电，黑线检测 |
| 温度传感 | Grove - Temperature Sensor | 模拟 | 环境温度（NTC） |
| 温湿度 | Grove - Temperature & Humidity Sensor (DHT11) | 数字 | 温湿度数字传感 |
| 声音强度 | Grove - Sound Sensor | 模拟 | 环境噪声检测 |
| 光线强度 | Grove - Light Sensor v1.2 | 模拟 | 环境光检测 |
| 响度 | Grove - Loudness Sensor | 模拟 | 较灵敏的声音强度检测 |
| 三轴加速度计 | Grove - 3-Axis Digital Accelerometer (±1.5g) | I2C | 姿态/震动/倾斜检测 |

### 输入

| 模块 | 英文名 | 类型 | 说明 |
|------|--------|------|------|
| 拇指摇杆 | Grove - Thumb Joystick | 模拟×2 + 数字 | X/Y 两路模拟 + 按压开关 |
| 旋转电位器 | Grove - Rotary Angle Sensor | 模拟 | 调节阈值/亮度/音量 |
| 倾斜开关 | Grove - Tilt Switch | 数字 | 检测倾斜/翻转 |
| 磁簧开关 | Grove - Magnetic Switch | 数字 | 磁体靠近触发（门窗检测） |
| 按钮 | Grove - Button | 数字 | 单击/长按 |
| 拨动开关 | Grove - Switch(P) | 数字 | 模式切换/启停 |
| 红色 LED 按钮 | Grove - Red LED Button | 数字 | 按钮 + 红色指示灯 |
| 黄色 LED 按钮 | Grove - Yellow LED Button | 数字 | 按钮 + 黄色指示灯 |
| 蓝色 LED 按钮 | Grove - Blue LED Button | 数字 | 按钮 + 蓝色指示灯 |

### 输出

| 模块 | 英文名 | 类型 | 说明 |
|------|--------|------|------|
| 继电器 | Grove - Relay | 数字 | 隔离控制外部电源/大电流设备 |
| 振动马达 | Grove - Vibration Motor | 数字 | 触感反馈/静默提醒 |
| 小喇叭 | Grove - Speaker | PWM | 播放提示音/简单音效 |
| 蜂鸣器 | Grove - Buzzer | PWM | 提示音/报警 |

### 显示

| 模块 | 英文名 | 类型 | 说明 |
|------|--------|------|------|
| 字符 LCD | Grove - 16x2 LCD (White on Blue) | I2C | 16×2 字符屏，显示状态/菜单 |
| 4 位数码管 | Grove - 4-Digit Display | TM1637 | 显示计时/温度/计数 |
| LED 条形显示 | Grove LED Bar v2.0 | MY9221 | 10 段进度条/强度可视化 |
| RGB 灯条 | Grove - RGB LED Stick (10-WS2813 Mini) | WS2813 | 10 颗可寻址 RGB，单点控制 |

### LED

| 模块 | 英文名 | 类型 | 说明 |
|------|--------|------|------|
| 红色 LED | Grove - Red LED | 数字 | 状态指示 |
| 绿色 LED | Grove - Green LED | 数字 | 状态指示 |
| 蓝色 LED | Grove - Blue LED | 数字 | 状态指示 |
| 可级联 RGB LED | Grove - Chainable RGB LED V2.0 | P9813 | 串接多颗，动画灯效 |
| 自动变色 LED | Grove - Multi Color Flash LED (5mm) | 数字 | 内置闪烁/变色效果 |

### 无线

| 模块 | 英文名 | 类型 | 说明 |
|------|--------|------|------|
| 红外发射 | Grove - Infrared Emitter | 数字 | 遥控家电/IR 通信 |
| 红外接收 | Grove - Infrared Receiver | 数字 | 学习/解码遥控器信号 |

### 时钟

| 模块 | 英文名 | 类型 | 说明 |
|------|--------|------|------|
| 实时时钟 | Grove - RTC | I2C | 掉电走时，定时功能（需 CR1220 电池） |

> 如需查看某个模块的详细用法和 Arduino 示例代码，在 Seeed Studio Wiki（https://wiki.seeedstudio.com）搜索上表中的英文名即可。

---

## 需求文档格式

学生会在项目目录的 `requirements.md` 中用自然语言描述需求。格式参考 `templates/grove-project/requirements.md` 或 `templates/wio-terminal-project/requirements.md`。
