#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "Snowflakes912";
const char* password = "snowflakes2304";
const char* thingSpeakApiKey = "O8453160W1HONWYD";
const unsigned long channelId = 2476636;
const int strainGaugePin = A0;        // Analog pin to which the strain gauge sensor is connected
const int vibrationThreshold = 50;    // Adjust this threshold according to your sensor and application
const int buzzerPin = 1;             // Digital pin to which the buzzer is connected

WiFiClient client;

void setup() {
  Serial.begin(9600);
  delay(100);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Initialize ThingSpeak client
  ThingSpeak.begin(client);

  // Set buzzer pin as output
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(strainGaugePin); // Read the analog sensor value
  
  Serial.print("Sensor value: ");
  Serial.println(sensorValue);

  if (sensorValue > vibrationThreshold) {
    Serial.println("Vibration detected!");

    // Activate buzzer
    digitalWrite(buzzerPin, HIGH);
    delay(500); // Buzzer on duration (adjust as needed)
    digitalWrite(buzzerPin, LOW); // Turn off buzzer

    // Send data to ThingSpeak
    ThingSpeak.writeField(channelId, 1, sensorValue, thingSpeakApiKey);
    delay(2000); // Delay to allow ThingSpeak to process data (15-second update interval for free accounts)
  }

  delay(1000); // Adjust delay as needed
}
