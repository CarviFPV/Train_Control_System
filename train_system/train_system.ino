#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Network credentials
const char *ssid = "TrainAP";
const char *password = "12345678";

ESP8266WebServer server(80);

// Motor pins for L9110s motor driver
const int motor1A = D1; // Motor 1 Input A
const int motor1B = D2; // Motor 1 Input B
const int motor2A = D4; // Motor 2 Input A
const int motor2B = D3; // Motor 2 Input B

// LED pins
const int ledWhite = D5; // White LED
const int ledRed = D6;   // Red LED

void setup() {
  // Initialize motor and LED pins as outputs
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(ledWhite, OUTPUT);
  pinMode(ledRed, OUTPUT);

  // Start the WiFi Access Point
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.begin(9600);
  Serial.println("AP IP address: " + myIP.toString());

  // Define URL Handlers
  server.on("/", handleRoot);
  server.on("/speed", handleSpeed);
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {

    String html = "<!DOCTYPE html>"
                  "<html><head><title>Train Control</title>"
                  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                  "<style>"
                  "body { font-family: Arial, sans-serif; text-align: center; margin: 0; padding: 0; background-color: #f3f3f3; }"
                  "h1 { color: #333; }"
                  "form { margin: 20px; }"
                  "input[type=range] { width: 80%; -webkit-appearance: none; margin: 10px 0; }"
                  "input[type=range]:focus { outline: none; }"
                  "input[type=submit] { border: none; padding: 10px 20px; background-color: #4CAF50; color: white; cursor: pointer; }"
                  "input[type=submit]:hover { background-color: #45a049; }"
                  "</style>"
                  "</head><body>"
                  "<h1>Train Speed Control</h1>"
                  "<form action=\"/speed\" method=\"POST\">"
                  "<input type=\"range\" name=\"speed\" min=\"-100\" max=\"100\" value=\"0\">"
                  "<input type=\"submit\" value=\"Set Speed\">"
                  "</form>"
                  "<h1>PWM Speed Control</h1>"
                  "<form action=\"/speed\" method=\"POST\">"
                  "<input type=\"text\" name=\"speed\" placeholder=\"Enter PWM (-100 to 100)\">"
                  "<input type=\"submit\" value=\"Set PWM\">"
                  "</form>"
                  "<h2>System Information</h2>"
                  "<p><b>MAC Address:</b> " + WiFi.macAddress() + "</p>"
                  "<p><b>Local IP:</b> " + WiFi.localIP().toString() + "</p>"
                  "<p><b>Wi-Fi RSSI:</b> " + WiFi.RSSI() + " dBm</p>"
                  "<p><b>CPU Frequency:</b> " + ESP.getCpuFreqMHz() + " MHz</p>"
                  "<p><b>Flash Chip Size:</b> " + ESP.getFlashChipSize() + " bytes</p>"
                  "<p><b>Free Heap Memory:</b> " + ESP.getFreeHeap() + " bytes</p>"
                  "<p><b>Flash Chip ID:</b> " + ESP.getFlashChipId() + "</p>"
                  "</body></html>";
    server.send(200, "text/html", html);
}

void handleSpeed() {
  if (server.hasArg("speed")) {
    int speed = server.arg("speed").toInt();
    controlTrain(speed);
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void controlTrain(int speed) {
  int pwmValue = map(abs(speed), 0, 100, 0, 1023); // Convert speed to PWM value

  if (speed > 0) {
    // Moving forward with variable speed
    analogWrite(motor1A, pwmValue);
    analogWrite(motor1B, 0);
    analogWrite(motor2A, pwmValue);
    analogWrite(motor2B, 0);
    digitalWrite(ledWhite, HIGH);
    digitalWrite(ledRed, LOW);
  } else if (speed < 0) {
    // Moving backward with variable speed
    analogWrite(motor1A, 0);
    analogWrite(motor1B, pwmValue);
    analogWrite(motor2A, 0);
    analogWrite(motor2B, pwmValue);
    digitalWrite(ledWhite, LOW);
    digitalWrite(ledRed, HIGH);
  } else {
    // Stopped
    analogWrite(motor1A, 0);
    analogWrite(motor1B, 0);
    analogWrite(motor2A, 0);
    analogWrite(motor2B, 0);
    digitalWrite(ledWhite, LOW);
    digitalWrite(ledRed, LOW);
  }
}

