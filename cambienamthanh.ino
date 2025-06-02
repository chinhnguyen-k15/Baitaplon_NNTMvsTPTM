#include <nguyenrin-project-1_inferencing.h>
#include <Arduino.h>

#define MIC_PIN 34
#define LED_PIN 23

unsigned long lastClapTime = 0;
int clapCount = 0;
const int CLAP_TIMEOUT = 1500;

// Lấy tín hiệu âm thanh từ cảm biến
int get_signal_data(size_t offset, size_t length, float *out_ptr) {
  for (size_t i = 0; i < length; i++) {
    int sample = analogRead(MIC_PIN);
    out_ptr[i] = (float)sample / 4096.0f; // Chuẩn hóa cho ESP32
    delayMicroseconds(100);
  }
  return 0;
}

void setup() {
  Serial.begin(115200);
  pinMode(MIC_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.println("🎬 Bắt đầu nhận diện AI vỗ tay...");
}

void loop() {
  signal_t signal;
  signal.total_length = EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;
  signal.get_data = &get_signal_data;

  ei_impulse_result_t result = { 0 };
  EI_IMPULSE_ERROR rc = run_classifier(&signal, &result, false);

  if (rc != EI_IMPULSE_OK) {
    Serial.println("❌ Lỗi mô hình AI");
    return;
  }

  bool isClap = false;
  for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
    ei_impulse_result_classification_t r = result.classification[ix];
    Serial.print("⏺ Label: "); Serial.print(r.label);
    Serial.print(" | Xác suất: "); Serial.println(r.value);

    if (strcmp(r.label, "Clap") == 0 && r.value > 0.4) {
      isClap = true;
    }
  }

  if (isClap) {
    clapCount++;
    lastClapTime = millis();
    Serial.print("👏 Phát hiện vỗ tay số: ");
    Serial.println(clapCount);
  }

  if (clapCount > 0 && millis() - lastClapTime > CLAP_TIMEOUT) {
    Serial.print("🎯 Tổng vỗ tay phát hiện: ");
    Serial.println(clapCount);

    if (clapCount == 1) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("💡 LED BẬT");
    } else if (clapCount == 2) {
      digitalWrite(LED_PIN, LOW);
      Serial.println("💡 LED TẮT");
    } else if (clapCount == 3) {
      Serial.println("💡 LED NHÁY");
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(200);
        digitalWrite(LED_PIN, LOW);
        delay(200);
      }
    }

    clapCount = 0;
  }

  delay(100);
}
