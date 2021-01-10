#include <ArduinoJson.h>
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <Firebase.h>  
#include <FirebaseError.h>  
#include <FirebaseHttpClient.h>  
#include <FirebaseObject.h>  
#include <ESP8266WiFi.h>  
#include <FirebaseArduino.h>  

//Firebase Database details
#define FIREBASE_HOST ""  
#define FIREBASE_AUTH ""  

//WiFi details
#define WIFI_SSID ""  
#define WIFI_PASSWORD ""  
const int sensor_pin = A0; 

void setup() {  
  Serial.begin(9600);  
  // connect to wifi.  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  
  Serial.print("connecting");  
  while (WiFi.status() != WL_CONNECTED) {  
    Serial.print(".");  
    delay(500);  
  }  
  Serial.println();  
  Serial.print("connected: ");  
  Serial.println(WiFi.localIP());  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  
}  

int readSensor() { 
  delay(10);              
  int val = analogRead(sensor_pin);  
  return val;         
}
  
void loop() {  
  int moisture = readSensor();
  
  //value from analog pin read directly
  Serial.print("Analog Output: ");
  Serial.println(moisture);
  
  //converted to moisture percentage
  
  //A value of 1023 would indicate a mositure level of 0%
  //While a moisture level of 1023 would indicate a moisture level of 100%
  float moisture_percentage;
  float value_read;
  moisture_percentage = (100.00 - ((moisture/1023.00) * 100.00 ));
  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(value_read);
  Serial.println("%");
  
  //Analog output sent to firebase
  Firebase.setInt("number", moisture);  
  String moist = Firebase.pushInt("Soil moisture", moisture);
}  
