/*
 * UNO_2 (RECEIVER AND REPORTER) - PART 1: HARDWARE
 *
 * YENİ BAĞLANTI (Proteus/Wokwi):
 * - Bu kartın Pin 0 (RX) pinini -> UNO_1'in Pin 1 (TX) pinine bağlayın.
 * - RAPORLAMA İÇİN:
 * - Bu kartın Pin 1 (TX) pinini -> "Virtual Terminal"in RX pinine bağlayın.
 */

// SoftwareSerial kütüphanesine artık gerek yok
// #include <SoftwareSerial.h> 
#include <Arduino.h>

// CHANGE THIS VALUE FOR TESTING (Must be same as UNO_1)
const long BAUD_RATE = 9600;

// reportSerial objesine gerek kalmadı
// SoftwareSerial reportSerial(10, 11); 

char expectedChar = 'a';
long errorCount = 0;
long successCount = 0;
long lastReportTime = 0;

void setup() {
  // Donanımsal Portu başlat.
  // Bu port hem UNO_1'den veri almak (RX) hem de
  // PC'ye rapor basmak (TX) için kullanılacak.
  Serial.begin(BAUD_RATE);
  
  // reportSerial.begin(9600); // Buna gerek kalmadı
  
  Serial.println("--- PART 1: HARDWARE TEST STARTED ---");
  Serial.print("Listening/Reporting Speed (Baud Rate): ");
  Serial.println(BAUD_RATE);
}

void loop() {
  // UNO_1'den (Hardware Serial) veri geldi mi?
  if (Serial.available()) {
    char c = Serial.read();
    
    // Gelen veri beklediğimiz veri mi?
    if (c == expectedChar) {
      successCount++;
    } else {
      errorCount++;
      // Hata olursa, beklenen sıraya geri dön
      expectedChar = c; 
    }
    
    // Beklenen karakteri bir sonrakine ilerlet
    expectedChar++;
    if (expectedChar > 'z') {
      expectedChar = 'a';
    }
  }
  
  // Her 1 saniyede bir Virtual Terminal'e (Hardware Serial) rapor yazdır
  if (millis() - lastReportTime > 1000) {
    Serial.print("--- 1 Second Report (");
    Serial.print(BAUD_RATE);
    Serial.print(" baud) --- \n");
    Serial.print("Successful Bytes: ");
    Serial.println(successCount);
    Serial.print("Failed Bytes: ");
    Serial.println(errorCount);
    Serial.println("------------------------------------");
    
    // Sayaçları sıfırla
    lastReportTime = millis();
    successCount = 0;
    errorCount = 0;
  }
}