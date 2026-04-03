/**
 * 示例 02：按钮控制 LED
 *
 * 功能：按住按钮 (D6) LED (D4) 亮，松开 LED 灭
 * 概念：数字输入 → 逻辑判断 → 数字输出
 */

const int LED_PIN = 4;     // LED 引脚
const int BUTTON_PIN = 6;  // 按钮引脚

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);  // 按钮设为输入
    Serial.println("按钮控制 LED 示例启动");
}

void loop() {
    // 读取按钮状态（按下为 LOW，松开为 HIGH）
    int buttonState = digitalRead(BUTTON_PIN);

    if (buttonState == LOW) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("按钮按下 → LED 亮");
    } else {
        digitalWrite(LED_PIN, LOW);
    }

    delay(50);  // 消抖延迟
}
