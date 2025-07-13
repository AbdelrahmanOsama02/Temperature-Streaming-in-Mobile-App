# Temperature-Streaming-in-Mobile-App
The system consisted of ESP32 wiring with Temperature sensor (DS18B20) take its reading and publish it to MQTT broker then Mobil app subscribe on it to sream the data


<img width="748" height="567" alt="image" src="https://github.com/user-attachments/assets/3b64bb01-e7cd-4729-9e86-8a2d23cc1f3b" />

<img width="646" height="412" alt="image" src="https://github.com/user-attachments/assets/ab9c6b57-f620-4f29-8858-1730c0dd70ab" />

<img width="1080" height="480" alt="image" src="https://github.com/user-attachments/assets/0c940906-58dc-4267-83ed-f4f106554406" />
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
