#include <Arduino.h>

/*
 * UNO_1 (GÖNDERİCİ) - BÖLÜM 1: DONANIMSAL
 *
 * BAĞLANTI (Proteus/Wokwi):
 * - Bu kartın Pin 1 (TX) pinini -> UNO_2'nin Pin 0 (RX) pinine bağlayın.
 */
 
// BU DEĞERİ TEST İÇİN DEĞİŞTİRİN (UNO_2 ile aynı olmalı)
const long BAUD_RATE = 9600;

void setup() {
  // Donanımsal portu başlat. Bu port doğrudan UNO_2'ye bağlı.
  Serial.begin(BAUD_RATE);
}

void loop() {
  // 'a'dan 'z'ye kadar olan karakterleri sürekli gönder.
  for (char c = 'a'; c <= 'z'; c++) {
    Serial.write(c);
  }
  // Yüksek hızlarda (baud rate) bu gecikmeyi kaldırmayı deneyin
  // veya SoftSerial'in yetişmesi için küçük bir gecikme bırakın.
  delay(1); 
}