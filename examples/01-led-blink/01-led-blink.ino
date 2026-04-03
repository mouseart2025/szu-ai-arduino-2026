/**
 * 示例 01：LED 闪烁
 *
 * 功能：Grove Beginner Kit 上的 LED (D4) 每隔 1 秒闪烁一次
 * 用途：验证 Arduino CLI 开发环境是否正常工作
 *
 * 编译上传：
 *   arduino-cli compile -b Seeeduino:avr:seeeduino_v4 -u -p <端口> ./
 */

// Grove Beginner Kit LED 引脚
const int LED_PIN = 4;

void setup() {
    // 初始化串口，用于调试输出
    Serial.begin(9600);

    // 设置 LED 引脚为输出模式
    pinMode(LED_PIN, OUTPUT);

    Serial.println("LED 闪烁示例启动");
}

void loop() {
    // 点亮 LED
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED: 亮");
    delay(1000);

    // 熄灭 LED
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED: 灭");
    delay(1000);
}
