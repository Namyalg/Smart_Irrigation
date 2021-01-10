#include <ArduinoJson.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <Firebase.h>  
#include <FirebaseCloudMessaging.h>  
#include <FirebaseError.h>  
#include <FirebaseHttpClient.h>  
#include <FirebaseObject.h>  
#include <ESP8266WiFi.h>  
#include <FirebaseArduino.h>
  
#define LED 5
#define LED1 12

//database   
#define FIREBASE_HOST ""  
#define FIREBASE_AUTH ""

//WiFi
#define WIFI_SSID ""  
#define WIFI_PASSWORD ""  

void setup() {  
  Serial.begin(9600);
  pinMode(LED, OUTPUT);  
  pinMode(LED1, OUTPUT);   
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

void loop() {  
  int x = 15000;
  while(x--);
  int moisture = Firebase.getInt("/number");
  if(Firebase.failed()){
    Serial.println(Firebase.error());
  }
  else{
     if(moisture > 700){
      digitalWrite(LED1, HIGH); 
      digitalWrite(LED, LOW);
      Serial.println("Greater");
    }
    else{
         // Turn the LED on (Note that LOW is the voltage level
      // but actually the LED is on; this is because
      // it is active low on the ESP-01)
      delay(1000);                      // Wait for a second
      digitalWrite(LED1, LOW); 
      digitalWrite(LED, HIGH);  // Turn the LED off by making the voltage HIGH
      delay(2000);    
      Serial.println("Lesser");
    }
     Serial.println(moisture);
  }
  delay(1000);
} 
