#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"

MAX30105 particleSensor;

#c:\Users\Yoga\Downloads\max30105-master1.rardefine MAX_BRIGHTNESS 255

void setup() {
  Serial.begin(115200);
  
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("Sensor tidak terdeteksi. Periksa koneksi!");
    while (1);
  }

  Serial.println("Sensor ditemukan!");

  particleSensor.setup(); // Konfigurasi sensor dengan setelan default
  particleSensor.setPulseAmplitudeRed(0x0A); // Atur amplitudo pulsa LED merah
  particleSensor.setPulseAmplitudeGreen(0); // Atur amplitudo pulsa LED hijau
}

void loop() {
  // Baca data dari sensor
  if (particleSensor.available()) {
    int32_t irValue = particleSensor.getIR();
    int32_t redValue = particleSensor.getRed();
    int32_t spo2Value = particleSensor.getSpO2();
    int32_t heartRate = particleSensor.getHeartRate();

    Serial.print("Detak Jantung: ");
    Serial.print(heartRate);
    Serial.print(" bpm\tKadar Oksigen: ");
    Serial.print(spo2Value);
    Serial.println(" %");

    // Jeda sejenak sebelum membaca data lagi
    delay(1000);
  }
}
