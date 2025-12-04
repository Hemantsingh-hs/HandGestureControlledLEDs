#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "TestESP";
const char* password = "12345678";

// Web server on port 80
WebServer server(80);

// LED pins
const int thumbLedPin = 27;
const int indexLedPin = 26;
const int middleLedPin = 25;
const int ringLedPin = 33;
const int pinkyLedPin = 32;

// Handler functions
void handleThumbOn()  { digitalWrite(thumbLedPin,HIGH); server.send(200,"text/plain","Thumb LED ON"); }
void handleThumbOff() { digitalWrite(thumbLedPin,LOW); server.send(200,"text/plain","Thumb LED OFF"); }

void handleIndexOn()  { digitalWrite(indexLedPin,HIGH); server.send(200,"text/plain","Index LED ON"); }
void handleIndexOff() { digitalWrite(indexLedPin,LOW); server.send(200,"text/plain","Index LED OFF"); }

void handleMiddleOn()  { digitalWrite(middleLedPin,HIGH); server.send(200,"text/plain","Middle LED ON"); }
void handleMiddleOff() { digitalWrite(middleLedPin,LOW); server.send(200,"text/plain","Middle LED OFF"); }

void handleRingOn()  { digitalWrite(ringLedPin,HIGH); server.send(200,"text/plain","Ring LED ON"); }
void handleRingOff() { digitalWrite(ringLedPin,LOW); server.send(200,"text/plain","Ring LED OFF"); }

void handlePinkyOn()  { digitalWrite(pinkyLedPin,HIGH); server.send(200,"text/plain","Pinky LED ON"); }
void handlePinkyOff() { digitalWrite(pinkyLedPin,LOW); server.send(200,"text/plain","Pinky LED OFF"); }

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize LEDs
  pinMode(thumbLedPin, OUTPUT);
  pinMode(indexLedPin, OUTPUT);
  pinMode(middleLedPin, OUTPUT);
  pinMode(ringLedPin, OUTPUT);
  pinMode(pinkyLedPin, OUTPUT);

  digitalWrite(thumbLedPin, LOW);
  digitalWrite(indexLedPin, LOW);
  digitalWrite(middleLedPin, LOW);
  digitalWrite(ringLedPin, LOW);
  digitalWrite(pinkyLedPin, LOW);

  // Connect to WiFi
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Setup server routes
  server.on("/led/thumb/on", handleThumbOn);
  server.on("/led/thumb/off", handleThumbOff);

  server.on("/led/index/on", handleIndexOn);
  server.on("/led/index/off", handleIndexOff);

  server.on("/led/middle/on", handleMiddleOn);
  server.on("/led/middle/off", handleMiddleOff);

  server.on("/led/ring/on", handleRingOn);
  server.on("/led/ring/off", handleRingOff);

  server.on("/led/pinky/on", handlePinkyOn);
  server.on("/led/pinky/off", handlePinkyOff);

  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient(); // Must be called frequently in loop
}
