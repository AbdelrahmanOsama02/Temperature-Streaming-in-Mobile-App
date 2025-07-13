# Temperature-Streaming-in-Mobile-App
The system consisted of ESP32 wiring with Temperature sensor (DS18B20) take its reading and publish it to MQTT broker then Mobil app subscribe on it to sream the data and app can send Feadback to broker then ESP can subscribe on it 


<img width="762" height="618" alt="image" src="https://github.com/user-attachments/assets/ca3b6146-1b80-4490-a220-5112711f429a" />

<img width="646" height="412" alt="image" src="https://github.com/user-attachments/assets/ab9c6b57-f620-4f29-8858-1730c0dd70ab" />

<img width="1170" height="540" alt="image" src="https://github.com/user-attachments/assets/3be4e683-76bf-4900-b976-28363e4b8461" />

description:

The DS18B20 sensor was connected to the ESP32 and 
correctly initialized using the DallasTemperature and 
OneWire libraries. 
Then ESP32 connects to the specified Wi-Fi network and 
maintains a stable connection. 
Using the PubSubClient library, the ESP32 publishes 
temperature readings to a specified MQTT topic on a public 
MQTT broker (broker.mqtt.cool) through the default port 
(1883). To ensure communication reliability, the system continuously checks the broker connection 
and attempts to reconnect automatically if the connection is lost. 
Now we have Publisher (ESP32 Module ) and Broker (MQTT Explorer) then we need subscriber to 
this topic and stream the Temperature Value it is the Mobile app,

<img width="798" height="298" alt="image" src="https://github.com/user-attachments/assets/35dfdb46-e18e-4fa1-984c-9c45b8317b0a" />

Using MIT App Inventor and adding MQTT extension create user interface app to subscribe to this 
topic and stream data.  

real-world applications: 

WHER YOU CAN USE THIS APPLICATION?? 

  • Smart temperature monitoring 

  • Home automation 

  • HVAC systems 

  • Remote data logging
