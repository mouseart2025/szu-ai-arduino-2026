/**
 * 示例 04：Wio Terminal 屏幕验证
 *
 * 功能：在 320×240 彩色屏幕上显示欢迎信息 + 按钮状态
 * 用途：验证 Wio Terminal 开发环境是否正常工作
 *
 * 编译上传：
 *   arduino-cli compile -b Seeeduino:samd:seeed_wio_terminal -u -p <端口> ./
 */

#include "TFT_eSPI.h"

TFT_eSPI tft;

void setup() {
    Serial.begin(115200);

    // 初始化屏幕
    tft.begin();
    tft.setRotation(3);  // 横屏，按钮在上
    digitalWrite(LCD_BACKLIGHT, HIGH);
    tft.fillScreen(TFT_BLACK);

    // 初始化按钮
    pinMode(WIO_KEY_A, INPUT_PULLUP);
    pinMode(WIO_KEY_B, INPUT_PULLUP);
    pinMode(WIO_KEY_C, INPUT_PULLUP);

    // 显示欢迎信息
    tft.setTextColor(TFT_YELLOW);
    tft.drawString("AI Maker Camp", 60, 40, 4);

    tft.setTextColor(TFT_WHITE);
    tft.drawString("Wio Terminal Ready!", 55, 100, 4);

    tft.setTextColor(TFT_CYAN);
    tft.drawString("Press A / B / C buttons", 30, 180, 2);

    Serial.println("Wio Terminal 屏幕验证启动");
}

void loop() {
    // 检测按钮，按下时在屏幕底部显示
    tft.fillRect(0, 210, 320, 30, TFT_BLACK);
    tft.setTextColor(TFT_GREEN);

    if (digitalRead(WIO_KEY_A) == LOW) {
        tft.drawString("Button A Pressed!", 80, 215, 2);
        Serial.println("Button A");
    } else if (digitalRead(WIO_KEY_B) == LOW) {
        tft.drawString("Button B Pressed!", 80, 215, 2);
        Serial.println("Button B");
    } else if (digitalRead(WIO_KEY_C) == LOW) {
        tft.drawString("Button C Pressed!", 80, 215, 2);
        Serial.println("Button C");
    }

    delay(100);
}
