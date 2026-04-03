/**
 * 示例 03：传感器数据 + OLED 显示
 *
 * 功能：读取光线传感器 (A6)，在 OLED 上实时显示
 * 需要安装库：arduino-cli lib install "U8g2"
 */

#include <Wire.h>
#include <U8g2lib.h>

// OLED 显示屏初始化（I2C，地址 0x3C）
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// 光线传感器引脚
const int LIGHT_PIN = A6;

void setup() {
    Serial.begin(9600);

    // 初始化 OLED
    u8g2.begin();
    u8g2.setFont(u8g2_font_6x13_tf);

    Serial.println("传感器 + OLED 示例启动");
}

void loop() {
    // 读取光线值
    int light = analogRead(LIGHT_PIN);

    // 串口输出
    Serial.print("光线: ");
    Serial.println(light);

    // OLED 显示
    u8g2.clearBuffer();
    u8g2.drawStr(0, 12, "== Sensor Data ==");

    char lightStr[20];
    snprintf(lightStr, sizeof(lightStr), "Light: %d", light);
    u8g2.drawStr(0, 30, lightStr);

    // 画一个简单的条形图
    int barWidth = map(light, 0, 1023, 0, 120);
    u8g2.drawFrame(0, 42, 122, 12);
    u8g2.drawBox(1, 43, barWidth, 10);

    u8g2.sendBuffer();

    delay(500);
}
