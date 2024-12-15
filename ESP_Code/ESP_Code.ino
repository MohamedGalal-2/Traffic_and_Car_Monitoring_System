#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Define WiFi credentials
const char* ssid = "Galal";
const char* password = "6000070005";

// Initialize the server on port 80
AsyncWebServer server(80);

// Define the UART communication port and baud rate
HardwareSerial UARTSerial(1); // Use Serial1 (UART1) for communication with STM32
const int RX_PIN = 16;        // ESP32 RX pin (connect to STM32 TX)
const int TX_PIN = 17;        // ESP32 TX pin (connect to STM32 RX)
const int BAUD_RATE = 9600;   // UART baud rate

// Setup WiFi
void setup() 
{
  Serial.begin(115200); // Initialize serial communication (default UART)
  UARTSerial.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN); // Initialize UART1


  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println("IP address: " + WiFi.localIP().toString());

  // Serve a basic web page to confirm connection
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    String html = "<html><body><h2>ESP32 WiFi Connection Established!</h2>"
                  "<p>IP Address: " + WiFi.localIP().toString() + "</p>"
                  "</body></html>";
    request->send(200, "text/html", html);
  });

  // Define the command route to handle incoming commands from the web
  server.on("/command", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    // Get the 'cmd' parameter from the URL
    String command = request->getParam("cmd")->value();
    
    // Print the command received on ESP32 Serial Monitor
    Serial.print("Received Command: ");
    Serial.println(command);
    
    // Send the command to STM32 via UART
    UARTSerial.println(command);  // Send the command to STM32

    // Respond with the received command
    String html = "<html><body><h2>ESP32 Command Sent to Arduino: " + command + "</h2></body></html>";
    request->send(200, "text/html", html);
  });

  // Start server
  server.begin();
}

// Main loop
void loop() 
{
  
}