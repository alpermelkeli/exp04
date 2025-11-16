/*
 * UNO_2 (ALICI - SADECE BİRİKTİRİR) - BÖLÜM 1: DONANIMSAL
 *
 * Gelen veriyi 1 saniye boyunca biriktirir ve terminale basar.
 * Hata sayımı kaldırıldı.
 */

#include <SoftwareSerial.h>
#include <Arduino.h>

// BU DEĞERİ TEST İÇİN DEĞİŞTİRİN (UNO_1 ile aynı olmalı)
const long BAUD_RATE = 9600;

// Raporlama için bir yazılımsal port oluşturuyoruz (Pin 10 RX, Pin 11 TX)
SoftwareSerial reportSerial(10, 11); 

long lastReportTime = 0;

// Gelen veriyi biriktirmek için bir String
String receivedData = "";

void setup() {
  // UNO_1'den veri almak için Donanımsal Port
  Serial.begin(BAUD_RATE);
  
  // PC'ye (Virtual Terminal) raporlama yapmak için Yazılımsal Port
  reportSerial.begin(9600); // Raporlama hızı sabit kalabilir
  reportSerial.println("--- BÖLÜM 1: DONANIMSAL ALICI BAŞLADI ---");
  reportSerial.print("Dinleme Hızı (Baud Rate): ");
  reportSerial.println(BAUD_RATE);
}


void loop() {
  // UNO_1'den (Hardware Serial) veri geldi mi?
  if (Serial.available()) {
    char c = Serial.read();
    
    // Gelen karakteri String'e ekle
    receivedData += c;
  }
  
  // Her 1 saniyede bir Virtual Terminal'e rapor yazdır
  if (millis() - lastReportTime > 1000) {
    reportSerial.print("--- 1 Saniyelik Rapor (");
    reportSerial.print(BAUD_RATE);
    reportSerial.print(" baud) --- \n");
    
    // Biriken veriyi bas
    reportSerial.print("Alınan Veri: ");
    reportSerial.println(receivedData);
    reportSerial.println("------------------------------------");
    
    // Sayaçları ve String'i sıfırla
    lastReportTime = millis();
    receivedData = "";
  }
}