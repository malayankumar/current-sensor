#include <ESP8266WiFi.h>
#include <ESP8266Firebase.h>
#include <ArduinoJson.h>

#define FIREBASE_HOST "https://current-and-voltage-sens-99766-default-rtdb.firebaseio.com/"
#define WIFI_SSID "Techknowspro_Office"
#define WIFI_PASSWORD "@Techknowspro"

// bytes data
byte initbyte = 0x77;
byte hederbyte = 0x01;
byte endbyte = 0x88;

//sensor data
float voltage = 0;
float current = 0;

Firebase firebase(FIREBASE_HOST);

unsigned long prevTime  = 0;
unsigned long interval = 5000; // ittirate every interval

void dataParsing() {
  if (Serial.read() == initByte) {
    serialHelper();
    voltage = serialHelper();
    current = serialHelper();
    serialHelper();
  }
  else {
    Serial.println("Error Data");
    while (Serial.available()) {
      Serial.read();
    }
  }
}

byte serialHelper() {
  while (!Serial.available());
  return Serial.read();
}

void uploadToServer() {
  prevTime = millis();
  Serial.println("Received Data:");
  Serial.print("    Voltage: ");
  Serial.println(voltage);
  Serial.print("    Current: ");
  Serial.println(current);
  Serial.println();
  firebase.setFloat("esp/voltage", voltage);
  firebase.setFloat("esp/current", current);
  //delay(10000);
}

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());                               //prints local IP address
  //  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop() {
  if (Serial.available()) dataParsing();
  if (millis() - prevTime > interval) uploadToServer();
}
