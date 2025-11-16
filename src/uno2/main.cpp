/*
 * UNO_2 (RECEIVER AND REPORTER) - PART 1: HARDWARE
 *
 * CONNECTION (Proteus/Wokwi):
 * - Connect this board's Pin 0 (RX) -> to UNO_1's Pin 1 (TX).
 * - FOR REPORTING TO US:
 * - Connect this board's Pin 11 (TX) -> to the "Virtual Terminal's" RX pin.
 */

#include <SoftwareSerial.h>
#include <Arduino.h>

// CHANGE THIS VALUE FOR TESTING (Must be same as UNO_1)
const long BAUD_RATE = 9600;

// We are creating a software serial port for reporting (Pin 10 RX, Pin 11 TX)
SoftwareSerial reportSerial(10, 11); 

char expectedChar = 'a';
long errorCount = 0;
long successCount = 0;
long lastReportTime = 0;

void setup() {
  // Hardware Serial Port for receiving data from UNO_1
  Serial.begin(BAUD_RATE);
  
  // Software Serial Port for reporting to PC (Virtual Terminal)
  reportSerial.begin(9600); // Reporting speed can remain constant
  reportSerial.println("--- PART 1: HARDWARE TEST STARTED ---");
  reportSerial.print("Listening Speed (Baud Rate): ");
  reportSerial.println(BAUD_RATE);
}


void loop() {
  // Is data available from UNO_1 (Hardware Serial)?
  if (Serial.available()) {
    char c = Serial.read();
    
    // Is the incoming data what we expected?
    if (c == expectedChar) {
      successCount++;
    } else {
      errorCount++;
      // If there is an error, reset the expected sequence
      expectedChar = c; 
    }
    
    // Advance the expected character to the next one
    expectedChar++;
    if (expectedChar > 'z') {
      expectedChar = 'a';
    }
  }
  
  // Print a report to the Virtual Terminal every 1 second
  if (millis() - lastReportTime > 1000) {
    reportSerial.print("--- 1 Second Report (");
    reportSerial.print(BAUD_RATE);
    reportSerial.print(" baud) --- \n");
    reportSerial.print("Successful Bytes: ");
    reportSerial.println(successCount);
    reportSerial.print("Failed Bytes: ");
    reportSerial.println(errorCount);
    reportSerial.println("------------------------------------");
    
    // Reset counters
    lastReportTime = millis();
    successCount = 0;
    errorCount = 0;
  }
}