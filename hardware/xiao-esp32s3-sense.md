# XIAO ESP32S3 Sense 硬件参考手册

> 柴火创客学院 · M0 零基础智能硬件入门 · "AI 视觉"阶段

## 概述

XIAO ESP32S3 Sense 是 Seeed Studio 推出的拇指大小开发板（21×17.8mm），集成摄像头、麦克风、SD 卡槽，支持 WiFi/BLE 和 TinyML 边缘 AI 推理。

## 硬件规格

| 项目 | 规格 |
|------|------|
| MCU | ESP32-S3R8 (Xtensa LX7 双核, 240MHz) |
| Flash | 8MB |
| PSRAM | 8MB |
| 摄像头 | OV3660 (最高 2048×1536)，兼容 OV2640/OV5640 |
| 麦克风 | PDM 数字麦克风 |
| 存储 | microSD 卡槽 (最大 32GB FAT32) |
| 无线 | WiFi 802.11 b/g/n (2.4GHz) + BLE 5.0/Mesh |
| GPIO | 11 个用户引脚 (D0-D10)，均支持 PWM |
| ADC | 9 路（D0-D5, D8-D10），注意 GPIO41/42 不支持 ADC |
| I2C | SDA=GPIO5 (D4), SCL=GPIO6 (D5) |
| SPI | SCK=GPIO7 (D8), MISO=GPIO8 (D9), MOSI=GPIO9 (D10) |
| UART | TX=GPIO43 (D6), RX=GPIO44 (D7) |
| 用户 LED | GPIO21（低电平点亮，与 SD 卡 CS 共用） |
| 供电 | USB 5V 或 3.7V 锂电池 |
| 尺寸 | 21 × 17.8 × 15mm（含 Sense 扩展板） |

---

## 引脚定义

### 用户可用引脚

| XIAO 引脚 | GPIO | 模拟 | 触摸 | PWM | 特殊功能 |
|-----------|------|------|------|-----|----------|
| D0 | GPIO1 | A0 | TOUCH1 | 可 | |
| D1 | GPIO2 | A1 | TOUCH2 | 可 | |
| D2 | GPIO3 | A2 | TOUCH3 | 可 | |
| D3 | GPIO4 | A3 | TOUCH4 | 可 | |
| D4 | GPIO5 | A4 | TOUCH5 | 可 | I2C SDA |
| D5 | GPIO6 | A5 | TOUCH6 | 可 | I2C SCL |
| D6 | GPIO43 | — | — | 可 | UART TX |
| D7 | GPIO44 | — | — | 可 | UART RX |
| D8 | GPIO7 | A6 | TOUCH7 | 可 | SPI SCK / SD SCK |
| D9 | GPIO8 | A7 | TOUCH8 | 可 | SPI MISO / SD MISO |
| D10 | GPIO9 | A8 | TOUCH9 | 可 | SPI MOSI |

### Sense 扩展板占用引脚

以下引脚默认已被 Sense 扩展板连接，不可作普通 GPIO 使用：

| 功能 | GPIO | 说明 |
|------|------|------|
| 麦克风 CLK | GPIO42 (D11) | 切割 J1 焊盘可释放 |
| 麦克风 DATA | GPIO41 (D12) | 切割 J2 焊盘可释放 |
| SD 卡 CS | GPIO21 | 同时也是用户 LED 引脚 |
| SD 卡 SCK | GPIO7 | 与 SPI SCK 共用 |
| SD 卡 MISO | GPIO8 | 与 SPI MISO 共用 |
| SD 卡 MOSI | GPIO10 | 注意：不是 GPIO9 |

### 摄像头引脚（通过 B2B 连接器，不占用户引脚）

| 功能 | GPIO |
|------|------|
| XMCLK | GPIO10 |
| DVP_Y2-Y9 | GPIO15, 17, 18, 16, 14, 12, 11, 48 |
| DVP_VSYNC | GPIO38 |
| DVP_HREF | GPIO47 |
| DVP_PCLK | GPIO13 |
| CAM_SDA | GPIO40 |
| CAM_SCL | GPIO39 |

---

## 开发环境

### Arduino CLI 配置

```bash
# 添加 ESP32 板卡包 URL（中国大陆走乐鑫官方镜像）
arduino-cli config add board_manager.additional_urls https://jihulab.com/esp-mirror/espressif/arduino-esp32/-/raw/gh-pages/package_esp32_index_cn.json

# 更新索引并安装（带 -cn 后缀自动走 dl.espressif.cn，含工具链）
arduino-cli core update-index
arduino-cli core install esp32:esp32@2.0.17-cn
```

> 装不上？见 `CLAUDE.md` 中「ESP32 板卡包装不上？（中国大陆网络兜底方案）」—— 硬规则 + 5 步验证流程，2026/4 深职大 40 位教师验证通过。

### FQBN

```
esp32:esp32:XIAO_ESP32S3
```

### 编译上传命令

```bash
# 编译（必须启用 PSRAM）
arduino-cli compile -b esp32:esp32:XIAO_ESP32S3 --build-property "build.extra_flags=-DBOARD_HAS_PSRAM" ./项目文件夹

# 编译并上传
arduino-cli compile -b esp32:esp32:XIAO_ESP32S3 --build-property "build.extra_flags=-DBOARD_HAS_PSRAM" -u -p <端口> ./项目文件夹

# 串口监视器
arduino-cli monitor -p <端口> -c baudrate=115200
```

### 内置库（无需额外安装）

- `esp_camera` — 摄像头驱动
- `WiFi.h` — WiFi 连接
- `BLEDevice.h` — BLE 蓝牙
- `FS.h` / `SD.h` / `SPI.h` — SD 卡文件系统
- `I2S.h` — 麦克风 PDM 录音

---

## 摄像头使用

### 引脚宏定义

```cpp
#include "esp_camera.h"

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
```

### 初始化配置

```cpp
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
config.jpeg_quality = 12;               // 0-63, 数字越小质量越高
config.fb_count = 1;

esp_err_t err = esp_camera_init(&config);
```

### 拍照并保存到 SD 卡

```cpp
camera_fb_t *fb = esp_camera_fb_get();
if (fb) {
    File file = SD.open("/photo.jpg", FILE_WRITE);
    file.write(fb->buf, fb->len);
    file.close();
    esp_camera_fb_return(fb);
}
```

### 分辨率选项

| 枚举值 | 分辨率 |
|--------|--------|
| FRAMESIZE_QVGA | 320×240 |
| FRAMESIZE_CIF | 400×296 |
| FRAMESIZE_VGA | 640×480 |
| FRAMESIZE_SVGA | 800×600 |
| FRAMESIZE_XGA | 1024×768 |
| FRAMESIZE_SXGA | 1280×1024 |
| FRAMESIZE_UXGA | 1600×1200 |

---

## 麦克风使用

PDM 数字麦克风，引脚 CLK=GPIO42, DATA=GPIO41。

### ESP32 板卡包 2.x

```cpp
#include <I2S.h>

void setup() {
    Serial.begin(115200);
    I2S.setAllPins(-1, 42, 41, -1, -1);
    if (!I2S.begin(PDM_MONO_MODE, 16000, 16)) {
        Serial.println("I2S init failed!");
        return;
    }
}

void loop() {
    int sample = I2S.read();
    if (sample && sample != -1 && sample != 1) {
        Serial.println(sample);
    }
}
```

### ESP32 板卡包 3.x

```cpp
#include "ESP_I2S.h"

I2SClass I2S;

void setup() {
    Serial.begin(115200);
    I2S.setPinsPdmRx(42, 41);
    if (!I2S.begin(I2S_MODE_PDM_RX, 16000, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO)) {
        Serial.println("I2S init failed!");
        return;
    }
}
```

> 采样率固定 16000Hz，位深 16-bit，单声道。2.x 和 3.x 的 API 不同，注意区分。

---

## SD 卡使用

CS 引脚为 GPIO21。最大 32GB，必须格式化为 FAT32。

```cpp
#include "FS.h"
#include "SD.h"
#include "SPI.h"

void setup() {
    Serial.begin(115200);
    if (!SD.begin(21)) {
        Serial.println("SD Card Mount Failed!");
        return;
    }

    // 写文件
    File file = SD.open("/test.txt", FILE_WRITE);
    if (file) {
        file.println("Hello XIAO!");
        file.close();
    }

    // 读文件
    file = SD.open("/test.txt");
    if (file) {
        while (file.available()) {
            Serial.write(file.read());
        }
        file.close();
    }
}
```

---

## WiFi 使用

### 连接路由器（STA 模式）

```cpp
#include <WiFi.h>

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin("YOUR_SSID", "YOUR_PASSWORD");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.print("\nIP: ");
    Serial.println(WiFi.localIP());
}
```

### 创建热点（AP 模式）

```cpp
#include <WiFi.h>

WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    WiFi.softAP("XIAO_AP", "password");
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());
    server.begin();
}
```

---

## BLE 蓝牙

仅支持 BLE 5.0，不支持蓝牙经典（Classic Bluetooth）。

```cpp
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

void setup() {
    Serial.begin(115200);
    BLEDevice::init("XIAO_BLE");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
    BLECharacteristic *pChar = pService->createCharacteristic(
        "beb5483e-36e1-4688-b7f5-ea07361b26a8",
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
    );
    pChar->setValue("Hello");
    pService->start();
    BLEDevice::getAdvertising()->start();
    Serial.println("BLE server started");
}

void loop() { delay(2000); }
```

---

## 注意事项

1. **PSRAM 必须启用**：编译时必须加 `--build-property "build.extra_flags=-DBOARD_HAS_PSRAM"`，否则摄像头和录音功能会失败
2. **用户 LED 反逻辑**：`digitalWrite(LED_BUILTIN, LOW)` 点亮，`HIGH` 熄灭
3. **GPIO41/42 不支持 ADC**：虽标记为模拟引脚但被麦克风占用
4. **SD 卡与 SPI 冲突**：Sense 版 SD 卡槽占用了 SPI 总线，不能同时使用外部 SPI 设备
5. **上传失败**：按住 Boot 按钮再按 Reset 进入 BootLoader 模式
6. **天线必须安装**：不接天线可能无法连接 WiFi
7. **散热**：长时间运行摄像头/WiFi 时芯片会发热
8. **ESP32 板卡包版本**：需要 >= 2.0.8；2.x 和 3.x 的 I2S API 不同

---

## Wiki 参考链接

| 主题 | 链接 |
|------|------|
| 入门指南 | https://wiki.seeedstudio.com/xiao_esp32s3_getting_started/ |
| 引脚复用 | https://wiki.seeedstudio.com/xiao_esp32s3_pin_multiplexing/ |
| 摄像头使用 | https://wiki.seeedstudio.com/xiao_esp32s3_camera_usage/ |
| 麦克风录音 | https://wiki.seeedstudio.com/xiao_esp32s3_sense_mic/ |
| WiFi 使用 | https://wiki.seeedstudio.com/xiao_esp32s3_wifi_usage/ |
| 常见问题 | https://wiki.seeedstudio.com/XIAO_FAQ/ |
