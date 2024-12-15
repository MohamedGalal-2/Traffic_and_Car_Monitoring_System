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
  // Check if data is received from ESP32 via SoftwareSerial
  if (ESPSerial.available()) 
  {
    // Read data from ESP32
    String receivedData = ESPSerial.readStringUntil('\n');

    // Print received data to Serial Monitor
    Serial.println("Data received from ESP32: " + receivedData);

    // Optional: Respond back to ESP32
    ESPSerial.println("Received: " + receivedData);
  }

  if (Serial.available()) 
  {
    String receivedData = Serial.readStringUntil('\n');
    Serial.println("Data received from ESP32: " + receivedData);
  }
}
