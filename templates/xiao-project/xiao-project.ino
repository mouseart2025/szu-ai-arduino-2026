/**
 * XIAO ESP32S3 Sense 项目模板
 *
 * 请在 requirements.md 中描述你的需求，然后让 AI 生成代码。
 * AI 会读取 CLAUDE.md 获取硬件信息，读取 requirements.md 获取你的需求。
 *
 * 注意：
 * - 复制此模板时，文件夹名和 .ino 文件名必须一致
 * - 编译时必须启用 PSRAM：
 *   arduino-cli compile -b esp32:esp32:XIAO_ESP32S3 --build-property "build.extra_flags=-DBOARD_HAS_PSRAM" ./
 */

void setup() {
    Serial.begin(115200);
    while (!Serial) delay(100);

    Serial.println("XIAO ESP32S3 Sense 项目启动");

    // TODO: 由 AI 根据 requirements.md 生成初始化代码
}

void loop() {
    // TODO: 由 AI 根据 requirements.md 生成主逻辑代码
}
