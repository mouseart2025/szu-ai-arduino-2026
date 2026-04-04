# Wio Terminal 硬件参考手册

> L3-L7 课程使用 · AI 赋能智能硬件创客训练营

## 概述

Wio Terminal 是 Seeed Studio 推出的一体化微控制器开发板，集成彩色屏幕、多种传感器、WiFi/BLE 无线通信。

## 硬件规格

| 项目 | 规格 |
|------|------|
| MCU | Microchip ATSAMD51P19 (ARM Cortex-M4F, 120MHz, 可超频至 200MHz) |
| Flash | 512KB 程序存储 + 4MB 外部 Flash |
| RAM | 192KB |
| 屏幕 | 2.4 寸 ILI9341 TFT LCD, 320×240, 16-bit 色彩 (RGB565) |
| 无线芯片 | Realtek RTL8720DN, 双频 WiFi (802.11 a/b/g/n) + BLE 5.0 |
| 存储扩展 | microSD 卡槽 (最大 16GB) |
| 接口 | USB Type-C (供电 + OTG), 2× Grove 端口, 40-pin 树莓派兼容 GPIO, 20-pin FPC |
| 内置传感器 | LIS3DHTR 三轴加速度计, 麦克风, 光传感器 (400-1050nm), 940nm 红外发射器 |
| 输入 | 3 个用户按钮 (A/B/C) + 5 向摇杆 |
| 输出 | 蜂鸣器 (无源压电), LCD 屏幕, LED |

---

## PlatformIO 配置

```ini
[env:wio_terminal]
platform = atmelsam
board = seeed_wio_terminal
framework = arduino
monitor_speed = 115200
lib_deps =
    seeed-studio/Seeed Arduino rpcWiFi@^1.0.6
    seeed-studio/Seeed Arduino rpcUnified@^2.1.4
    seeed-studio/Seeed Arduino mbedtls@^3.0.1
    seeed-studio/Seeed Arduino FS@^2.1.1
    seeed-studio/Seeed Arduino SFUD@^2.0.2
    seeed-studio/Seeed_Arduino_Linechart@^1.0.0
    lovyan03/LovyanGFX@^1.1.8
```

> 注意: TFT_eSPI 库已内置于 Wio Terminal Arduino 核心中，无需额外添加到 lib_deps。

### Arduino IDE 设置

Board Package URL:
```
https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
```
Board 选择: **Seeed Wio Terminal**

### 进入 Bootloader 模式

快速连续拨动侧面滑动开关两次，蓝色 LED 呈呼吸灯闪烁表示进入 bootloader。

---

## 引脚定义总表

### 用户输入

| 宏名称 | Arduino Pin | 功能 | 配置 |
|--------|-------------|------|------|
| `WIO_KEY_A` / `BUTTON_1` | 28 | 顶部右按钮 | `INPUT_PULLUP`, 按下为 `LOW` |
| `WIO_KEY_B` / `BUTTON_2` | 29 | 顶部中按钮 | `INPUT_PULLUP`, 按下为 `LOW` |
| `WIO_KEY_C` / `BUTTON_3` | 30 | 顶部左按钮 | `INPUT_PULLUP`, 按下为 `LOW` |
| `WIO_5S_UP` | 31 | 五向摇杆 上 | `INPUT_PULLUP`, 按下为 `LOW` |
| `WIO_5S_LEFT` | 32 | 五向摇杆 左 | `INPUT_PULLUP`, 按下为 `LOW` |
| `WIO_5S_RIGHT` | 33 | 五向摇杆 右 | `INPUT_PULLUP`, 按下为 `LOW` |
| `WIO_5S_DOWN` | 34 | 五向摇杆 下 | `INPUT_PULLUP`, 按下为 `LOW` |
| `WIO_5S_PRESS` | 35 | 五向摇杆 按下 | `INPUT_PULLUP`, 按下为 `LOW` |

### 内置传感器和输出

| 宏名称 | Arduino Pin | 功能 | 用法 |
|--------|-------------|------|------|
| `WIO_BUZZER` | 12 | 无源蜂鸣器 | `analogWrite(WIO_BUZZER, 128)` 或手动 PWM |
| `WIO_MIC` | 39 | 内置麦克风 | `analogRead(WIO_MIC)` |
| `WIO_LIGHT` | 27 (A13) | 光传感器 (背面) | `analogRead(WIO_LIGHT)` |
| `WIO_IR` | 14 | 940nm 红外发射器 | `digitalWrite(WIO_IR, HIGH/LOW)` |
| `LED_BUILTIN` | 13 | 板载 LED | `digitalWrite(LED_BUILTIN, HIGH/LOW)` |

### LCD 控制

| 宏名称 | Arduino Pin | 功能 |
|--------|-------------|------|
| `LCD_BACKLIGHT` | 72 | 背光控制, `digitalWrite(LCD_BACKLIGHT, HIGH)` 开启 |
| `LCD_DC` | 70 | LCD 数据/命令选择 |
| `LCD_RESET` | 71 | LCD 复位 |

### I2C 总线

| 宏名称 | Arduino Pin | 用途 |
|--------|-------------|------|
| `PIN_WIRE_SDA` | 46 | I2C0 SDA (Grove 外部设备) |
| `PIN_WIRE_SCL` | 45 | I2C0 SCL (Grove 外部设备) |
| `PIN_WIRE1_SDA` | 78 | I2C1 SDA (内置 LIS3DHTR) |
| `PIN_WIRE1_SCL` | 77 | I2C1 SCL (内置 LIS3DHTR) |

### SPI 总线

| 总线 | MISO | MOSI | SCK | SS | 用途 |
|------|------|------|-----|-----|------|
| SPI0 | 47 | 48 | 49 | 50 | 外部设备 |
| SPI1 | 84 | 85 | 86 | 87 | RTL8720DN WiFi |
| SPI2 | 61 | 62 | 63 | 64 | microSD 卡 |
| SPI3 | 66 | 67 | 68 | 69 | LCD 屏幕 |

### UART 串口

| 接口 | RX Pin | TX Pin | 用途 |
|------|--------|--------|------|
| `Serial` | — | — | USB 串口调试 |
| `Serial1` | 40/41 | 41/40 | Grove UART / GPIO |
| `Serial2` | 83 | 82 | RTL8720DN 通信 |

### DAC 输出

| 宏名称 | Arduino Pin | 端口 |
|--------|-------------|------|
| `PIN_DAC0` | 9 | PA02 |
| `PIN_DAC1` | 10 | PA05 |

### RPI GPIO 引脚 (40-pin 排针)

| Arduino Pin | 宏名称 | 端口 | 模拟通道 | PWM |
|-------------|--------|------|----------|-----|
| 0 | `RPI_D0` / `RPI_A0` / `A0` | PB08 | ADC_CH2 | TC4_CH0 |
| 1 | `RPI_D1` / `RPI_A1` / `A1` | PB09 | ADC_CH3 | TC4_CH1 |
| 2 | `RPI_D2` / `RPI_A2` / `A2` | PA04 | ADC_CH4 | TC0_CH0 |
| 3 | `RPI_D3` / `RPI_A3` / `A3` | PA07 | ADC_CH7 | TC1_CH1 |
| 4 | `RPI_D4` / `RPI_A4` / `A4` | PB04 | ADC_CH6 | — |
| 5 | `RPI_D5` / `RPI_A5` / `A5` | PB05 | ADC_CH7 | — |
| 6 | `RPI_D6` / `RPI_A6` / `A6` | PB06 | ADC_CH8 | — |
| 7 | `RPI_D7` / `RPI_A7` / `A7` | PB07 | ADC_CH9 | — |
| 8 | `RPI_D8` / `RPI_A8` / `A8` | PA06 | ADC_CH6 | TC1_CH0 |

---

## LCD 屏幕 (TFT_eSPI)

### 初始化

```cpp
#include "TFT_eSPI.h"
TFT_eSPI tft;

void setup() {
    tft.begin();
    tft.setRotation(3);  // 0-3, 横屏推荐 3
    digitalWrite(LCD_BACKLIGHT, HIGH);  // 开启背光
    tft.fillScreen(TFT_BLACK);
}
```

### 颜色常量 (RGB565, 16-bit)

`TFT_BLACK`, `TFT_WHITE`, `TFT_RED`, `TFT_GREEN`, `TFT_BLUE`,
`TFT_YELLOW`, `TFT_CYAN`, `TFT_MAGENTA`, `TFT_ORANGE`,
`TFT_NAVY`, `TFT_DARKGREEN`, `TFT_DARKCYAN`, `TFT_MAROON`,
`TFT_PURPLE`, `TFT_OLIVE`, `TFT_LIGHTGREY`, `TFT_DARKGREY`

自定义颜色: `tft.color565(r, g, b)` — r/g/b 为 0-255

### 屏幕方向

| setRotation 值 | 方向 | 分辨率 (宽×高) |
|----------------|------|----------------|
| 0 | 竖屏 (USB 在下) | 240×320 |
| 1 | 横屏 | 320×240 |
| 2 | 竖屏 (USB 在上) | 240×320 |
| 3 | 横屏 (推荐, 按钮在上) | 320×240 |

### 绘图函数

```cpp
// 像素
tft.drawPixel(int32_t x, int32_t y, uint32_t color);

// 线条
tft.drawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);
tft.drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color);
tft.drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color);

// 矩形
tft.drawRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);
tft.fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);

// 圆角矩形
tft.drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, uint32_t color);
tft.fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, uint32_t color);

// 圆形
tft.drawCircle(int32_t x0, int32_t y0, int32_t r, uint32_t color);
tft.fillCircle(int32_t x0, int32_t y0, int32_t r, uint32_t color);

// 椭圆
tft.drawEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color);
tft.fillEllipse(int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color);

// 三角形
tft.drawTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color);
tft.fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color);

// 填充整个屏幕
tft.fillScreen(uint32_t color);
```

### 文字函数

```cpp
// 设置文字属性
tft.setTextColor(uint32_t color);                    // 文字颜色 (透明背景)
tft.setTextColor(uint32_t fgcolor, uint32_t bgcolor); // 文字颜色 + 背景色
tft.setTextSize(uint8_t size);                        // 文字大小倍数 (1-7)
tft.setCursor(int16_t x, int16_t y);                  // 设置光标位置

// 绘制文字
tft.drawString(const String& string, int32_t x, int32_t y);
tft.drawChar(int32_t x, int32_t y, uint16_t c, uint32_t color, uint32_t bg, uint8_t size);
tft.drawNumber(long num, int32_t x, int32_t y);
tft.drawFloat(float floatNumber, uint8_t decimal, int32_t x, int32_t y);
tft.print("text");   // 在 setCursor 位置打印
tft.println("text"); // 打印并换行
```

### 自定义字体

```cpp
#include "Free_Fonts.h"

// 设置字体 (使用后文字大小由字体决定, setTextSize 不再生效)
tft.setFreeFont(&FreeSansBold12pt7b);

// 字体命名规则: Free + [Sans/Serif/Mono] + [Bold] + [Oblique/Italic] + [9/12/18/24]pt7b
// 缩写: F + [SS/S/M] + [B] + [O/I] + [9/12/18/24]
// 例: FSSBO24 = FreeSansBoldOblique24pt7b

// 恢复默认字体
tft.setFreeFont(NULL);  // 或 tft.setTextFont(1);
```

### 文字对齐 (Datum)

```cpp
tft.setTextDatum(TC_DATUM);  // 设置文字对齐基准点
tft.drawString("居中文字", 160, 10);  // x=160 为屏幕水平中心
```

对齐常量: `TL_DATUM` (左上), `TC_DATUM` (上中), `TR_DATUM` (右上),
`ML_DATUM` (左中), `MC_DATUM` (正中), `MR_DATUM` (右中),
`BL_DATUM` (左下), `BC_DATUM` (下中), `BR_DATUM` (右下)

### Sprite (离屏缓冲, 防止闪烁)

```cpp
TFT_eSprite spr = TFT_eSprite(&tft);

void setup() {
    tft.begin();
    tft.setRotation(3);
    spr.createSprite(320, 240);  // 创建全屏 Sprite
}

void loop() {
    spr.fillSprite(TFT_BLACK);           // 清空 Sprite
    spr.setTextColor(TFT_WHITE);
    spr.drawString("Hello", 10, 10);
    spr.pushSprite(0, 0);                // 一次性推送到屏幕
}
```

---

## 按钮和摇杆

### 初始化和使用

```cpp
void setup() {
    Serial.begin(115200);
    // 3 个顶部按钮
    pinMode(WIO_KEY_A, INPUT_PULLUP);
    pinMode(WIO_KEY_B, INPUT_PULLUP);
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    // 5 向摇杆
    pinMode(WIO_5S_UP, INPUT_PULLUP);
    pinMode(WIO_5S_DOWN, INPUT_PULLUP);
    pinMode(WIO_5S_LEFT, INPUT_PULLUP);
    pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
    pinMode(WIO_5S_PRESS, INPUT_PULLUP);
}

void loop() {
    // 所有按钮按下时读取为 LOW
    if (digitalRead(WIO_KEY_A) == LOW) Serial.println("Button A");
    if (digitalRead(WIO_KEY_B) == LOW) Serial.println("Button B");
    if (digitalRead(WIO_KEY_C) == LOW) Serial.println("Button C");
    if (digitalRead(WIO_5S_UP) == LOW) Serial.println("Up");
    if (digitalRead(WIO_5S_DOWN) == LOW) Serial.println("Down");
    if (digitalRead(WIO_5S_LEFT) == LOW) Serial.println("Left");
    if (digitalRead(WIO_5S_RIGHT) == LOW) Serial.println("Right");
    if (digitalRead(WIO_5S_PRESS) == LOW) Serial.println("Press");
    delay(200);
}
```

---

## 内置传感器

### 加速度计 (LIS3DHTR)

```cpp
#include "LIS3DHTR.h"
LIS3DHTR<TwoWire> lis;

void setup() {
    Serial.begin(115200);
    lis.begin(Wire1);  // 注意: 使用 Wire1, 不是 Wire
    lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ);  // 1Hz - 5kHz
    lis.setFullScaleRange(LIS3DHTR_RANGE_2G);       // 2G, 4G, 8G, 16G
}

void loop() {
    float x = lis.getAccelerationX();
    float y = lis.getAccelerationY();
    float z = lis.getAccelerationZ();
    Serial.printf("X: %.2f, Y: %.2f, Z: %.2f\n", x, y, z);
    delay(50);
}
```

### 麦克风

```cpp
void setup() {
    pinMode(WIO_MIC, INPUT);
    Serial.begin(115200);
}

void loop() {
    int val = analogRead(WIO_MIC);
    Serial.println(val);
    delay(50);
}
```

### 光传感器

```cpp
void setup() {
    pinMode(WIO_LIGHT, INPUT);
    Serial.begin(115200);
}

void loop() {
    int light = analogRead(WIO_LIGHT);  // 位于板子背面, microSD 卡槽上方
    Serial.print("Light: ");
    Serial.println(light);
    delay(200);
}
```

### 蜂鸣器

```cpp
void setup() {
    pinMode(WIO_BUZZER, OUTPUT);
}

void loop() {
    analogWrite(WIO_BUZZER, 128);  // PWM 驱动, 0-255
    delay(1000);
    analogWrite(WIO_BUZZER, 0);
    delay(1000);
}

// 播放指定频率的音调 (手动 PWM)
void playTone(int tone_val, int duration) {
    long elapsed = 0;
    while (elapsed < duration * 1000L) {
        digitalWrite(WIO_BUZZER, HIGH);
        delayMicroseconds(tone_val);
        digitalWrite(WIO_BUZZER, LOW);
        delayMicroseconds(tone_val);
        elapsed += tone_val * 2;
    }
}
// tone_val: 956 (高音) ~ 1915 (低音 C), 单位微秒
```

### 红外发射器

```cpp
void setup() {
    pinMode(WIO_IR, OUTPUT);
}
void loop() {
    digitalWrite(WIO_IR, HIGH);  // 发射 940nm 红外
    delay(1000);
    digitalWrite(WIO_IR, LOW);
    delay(1000);
}
```

---

## Grove 端口

Wio Terminal 有 2 个 Grove 端口 (左侧和右侧):

### 左侧 Grove 端口 (I2C)

- 共享 I2C0 总线: `Wire` (SDA=46, SCL=45)
- 可用 `PIN_WIRE_SDA` 和 `PIN_WIRE_SCL` 宏
- 也可配置为数字引脚: `pinMode(PIN_WIRE_SCL, INPUT)`

### 右侧 Grove 端口 (Digital/Analog)

- 可作为模拟输入: `pinMode(A0, INPUT)`, `analogRead(A0)`
- 可作为数字引脚: `pinMode(D0, INPUT)`, `digitalRead(D0)`
- 可作为 UART: `Serial1`

---

## WiFi 网络

### 库和依赖

```cpp
#include "rpcWiFi.h"        // 主 WiFi 库 (替代旧版 AtWifi.h)
#include <WiFiClient.h>     // TCP 客户端
#include <WiFiClientSecure.h> // HTTPS 安全连接
#include <WiFiAP.h>         // AP 热点模式
#include <WiFiMulti.h>      // 多 AP 管理
#include <WiFiUdp.h>        // UDP 协议
```

> 前提: 必须先更新 RTL8720DN 固件至最新版本 (eRPC 架构)

### WiFi 连接示例

```cpp
#include "rpcWiFi.h"

const char* ssid = "your-ssid";
const char* password = "your-password";

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}
```

### 常用 WiFi 函数

```cpp
WiFi.mode(WIFI_STA);              // Station 模式
WiFi.mode(WIFI_AP);               // AP 热点模式
WiFi.begin(ssid, password);       // 连接
WiFi.disconnect();                // 断开
WiFi.status();                    // 连接状态 (WL_CONNECTED 等)
WiFi.localIP();                   // 本机 IP
WiFi.SSID(i);                     // 扫描到的网络名
WiFi.RSSI(i);                     // 信号强度
WiFi.softAP(ssid, password);      // 创建热点
```

---

## 折线图库 (Seeed_Arduino_Linechart)

```cpp
#include "seeed_line_chart.h"
TFT_eSPI tft;
TFT_eSprite spr = TFT_eSprite(&tft);
doubles data;  // 数据容器

void setup() {
    tft.begin();
    tft.setRotation(3);
    spr.createSprite(TFT_HEIGHT, TFT_WIDTH);
}

void loop() {
    spr.fillSprite(TFT_WHITE);

    if (data.size() > 50) data.pop();  // 保持最多 50 个数据点
    data.push(0.01 * random(1, 100));

    // 标题
    auto header = text(0, 0);
    header.value("Sensor Data").color(TFT_BLACK).draw(&spr);

    // 折线图
    auto content = line_chart(20, 20);
    content.height(spr.height() - 40)
           .width(spr.width() - 40)
           .based_on(0.0)
           .value(data)
           .color(TFT_PURPLE)
           .show_circle(false)
           .draw(&spr);

    spr.pushSprite(0, 0);
    delay(50);
}
```

---

## 模块分类

- **感知（输入）**: 光传感器 (`WIO_LIGHT`), 麦克风 (`WIO_MIC`), 加速度计 (LIS3DHTR via I2C1)
- **表达（输出）**: LCD 屏幕 (TFT_eSPI), 蜂鸣器 (`WIO_BUZZER`), LED (`LED_BUILTIN`), 红外 (`WIO_IR`)
- **交互（输入）**: 3 按钮 (`WIO_KEY_A/B/C`), 5 向摇杆 (`WIO_5S_*`)
- **通信**: WiFi (`rpcWiFi.h`), BLE 5.0, Grove I2C/UART/Analog
