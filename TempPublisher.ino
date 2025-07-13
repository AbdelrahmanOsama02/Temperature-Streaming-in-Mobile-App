#include <OneWire.h>             
#include <DallasTemperature.h>   
#include <WiFi.h>                
#include <PubSubClient.h>        

/************* DS18B20 Sensor Configuration *************/
#define ONE_WIRE_BUS 4                // DS18B20 data pin is connected to GPIO4
OneWire oneWire(ONE_WIRE_BUS);        // Create a OneWire object for communication
DallasTemperature sensors(&oneWire);  // Create a DallasTemperature object using OneWire

/****************** LED Configuration *******************/
#define LED_PIN 2
/************* Wi-Fi Network Configuration *************/
const char* ssid = "Wokwi-GUEST";      // Wi-Fi SSID
const char* password = "";            // Wi-Fi password (empty for Wokwi-GUEST)

/************* MQTT Broker Configuration *************/
const char* mqtt_broker = "broker.mqtt.cool";    // MQTT broker address
const char* mqtt_topic_temp = "sensor/temp";     // MQTT topic to publish temperature
const char* mqtt_topic_lamp = "ctrl/led";
const int mqtt_port = 1883;                      // MQTT broker port (default: 1883)

WiFiClient espClient;              // Create a WiFi client
PubSubClient client(espClient);    // Create an MQTT client using the WiFi client

/************* Reconnect to MQTT Broker if Disconnected *************/
void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Try to connect to the broker with a client ID
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state()); 
      Serial.println(" Retrying in 5 seconds...");
      delay(2000); // Wait before retrying
    }
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  // Convert the message to a string
  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  Serial.print("Message: ");
  Serial.println(messageTemp);

  // Check if the topic is for the LED control
  if (String(topic) == mqtt_topic_lamp) {
    if (messageTemp == "on") {
      digitalWrite(LED_PIN, HIGH);
    }else if (messageTemp == "off") {
      digitalWrite(LED_PIN, LOW);
    }
  }
  
}

/************* Setup Function *************/
void setup() {
  Serial.begin(9600);         
  sensors.begin();                // Initialize the DS18B20 sensor

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);     // Start connecting to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");            
  }
  
  //LED initialization 
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Set MQTT broker and connect
  client.setServer(mqtt_broker, mqtt_port); // Set the MQTT broker address and port
  client.setCallback(callback);
  reconnect(); // Connect to the MQTT broker
  client.subscribe(mqtt_topic_lamp);
}

/************* Main Loop Function *************/
void loop() {
  // Check MQTT connection and reconnect if needed
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); // Maintain MQTT connection and handle incoming messages (if any)

  // Request temperature from DS18B20
  sensors.requestTemperatures();  
  float temperature = sensors.getTempCByIndex(0); // Read temperature in Celsius from the first sensor

  // Check if reading failed
  if (temperature == DEVICE_DISCONNECTED_C) {
    Serial.println("Failed to read from DS18B20!");
    return;
  }

  // Convert temperature float to string to publish via MQTT
  char tempString[8];
  dtostrf(temperature, 6, 2, tempString); // Format: 6 characters wide, 2 decimals

  // Publish temperature to MQTT topic
  client.publish(mqtt_topic_temp, tempString);

  // Print temperature to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(2000); // Wait 5 seconds before the next reading
}
