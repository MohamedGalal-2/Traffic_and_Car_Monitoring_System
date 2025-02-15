#include <SoftwareSerial.h>

// Define SoftwareSerial pins
const int RX_PIN = D7; // NodeMCU RX (connect to ESP32 TX)
const int TX_PIN = D8; // NodeMCU TX (connect to ESP32 RX)

// Create SoftwareSerial instance
SoftwareSerial ESPSerial(RX_PIN, TX_PIN); // RX, TX

// UART configuration
const int BAUD_RATE = 9600; // Match this with ESP32 baud rate

void setup() {
  // Initialize Serial (UART0) for debugging
  Serial.begin(BAUD_RATE);

  // Initialize SoftwareSerial for communication with ESP32
  ESPSerial.begin(BAUD_RATE);
  
  delay(1000);
  Serial.println("NodeMCU ESP8266 UART Initialized");
}

void loop() 
{
  if (ESPSerial.available()) 
  {
    uint8_t receivedData = ESPSerial.read();
    
    // If data is valid, process it
    if (receivedData != 0) 
    {
      Serial.println("Data received from ESP32: " + (String) receivedData);
    }
    

    if (receivedData == (uint8_t) 'F') 
    {
      ESPSerial.write('X');
    }
    else if (receivedData == (uint8_t)'R')
    {
      ESPSerial.write('Y');
    }
    else if (receivedData == (uint8_t) 'B')
    {
      ESPSerial.write('Z');
    }
    else 
    {
      Serial.println("Unknown command received: " + (String) receivedData);
    }
  }
}
