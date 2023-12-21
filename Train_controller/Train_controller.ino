#include <Encoder.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

// WiFi credentials
const char* ssid = "TrainAP";
const char* password = "12345678";

// Rotary encoder pins
const int pinA = D5;  // CLK
const int pinB = D6;  // DT
const int pinSW = D7; // SW (Button)

// LED pins
const int ledWifi = D0;    // WiFi status LED
const int ledForward = D1; // Forward direction LED
const int ledReverse = D2; // Reverse direction LED

// Initialize PJRC Encoder
Encoder myEnc(pinA, pinB);
long oldPosition  = -999;

// Direction state
bool directionForward = true;

void setup() {
  Serial.begin(9600);

  pinMode(pinSW, INPUT_PULLUP);
  pinMode(ledWifi, OUTPUT);
  pinMode(ledForward, OUTPUT);
  pinMode(ledReverse, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(ledWifi, HIGH);
  Serial.println("Connected to WiFi");
}

void loop() {
  handleEncoder();
  handleButton();
}

void handleEncoder() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.print("Encoder Value: ");
    Serial.println(newPosition);
    sendSpeedCommand(newPosition);
  }
}

void handleButton() {
  static unsigned long lastDebounceTime = 0;
  static int lastButtonState = HIGH;
  int reading = digitalRead(pinSW);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > 50) {
    if (reading == LOW) {
      toggleDirection();
    }
  }

  lastButtonState = reading;
}

void sendSpeedCommand(long speed) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    String serverPath = "http://192.168.4.1/speed";  // URL for the speed control
    
    http.begin(client, serverPath);  // Start the HTTP request
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");  // Specify the content type for form data
    
    String httpRequestData = "speed=" + String(speed);  // Prepare the form data
    int httpResponseCode = http.POST(httpRequestData);  // Send a POST request
    
    if (httpResponseCode > 0) {
      Serial.print("Speed Command HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Speed Command HTTP Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
}


void toggleDirection() {
  directionForward = !directionForward;
  digitalWrite(ledForward, directionForward);
  digitalWrite(ledReverse, !directionForward);

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    String serverPath = "http://192.168.4.1/setDirection?value=" + String(directionForward ? "forward" : "reverse");
    
    http.begin(client, serverPath);  // Updated to use the new API
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      Serial.print("Direction Command HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Direction Command HTTP Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }

  Serial.print("Direction: ");
  Serial.println(directionForward ? "Forward" : "Reverse");
}


