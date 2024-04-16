#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <ESP8266WiFi.h>                                      

#include <DHT.h>                                                            


#define FIREBASE_HOST "iot-weather-station-8c8f7-default-rtdb.firebaseio.com"                          

#define FIREBASE_AUTH "IUiPqOaVZc1KMzqp5mwv5ATvvXhSgPFNMvXpa2hD"            


#define WIFI_SSID "ZLATAN"                                              

#define WIFI_PASSWORD "vespa123"                                    
 

#define DHTPIN D4                                                         

#define DHTTYPE DHT11                                                       



DHT dht(DHTPIN, DHTTYPE);                                                     


void setup() {

  Serial.begin(115200);

  delay(1000);                

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                    

  Serial.print("Connecting to ");

  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");

    delay(500);

  }

  Serial.println();

  Serial.print("Connected to ");

  Serial.println(WIFI_SSID);

  Serial.print("IP Address is : ");

  Serial.println(WiFi.localIP());                                            

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              

  dht.begin(); 
         
  pinMode(LED_BUILTIN, OUTPUT);                                                       

}
void loop() { 
   
  float h = dht.readHumidity();                                             

  float t = dht.readTemperature();    

  const String& path="/Ispit/value";

  bool var=Firebase.getBool(path);
  if(var)
  {
     Serial.println(F("Preuzeto"));
     digitalWrite(LED_BUILTIN,HIGH);                    //ne radi nesto 
  }
  else
    {
      Serial.println(F("Ne radi preuzimanje"));
    }
    

  if (isnan(h) || isnan(t)) {                                                

    Serial.println(F("Failed to read from DHT sensor!"));

    return;

  }

  

  Serial.print("Humidity: ");  Serial.print(h);

  String fireHumid = String(h) + String("%");                                         

  Serial.print("%  Temperature: ");  Serial.print(t);  Serial.println("°C ");

  String fireTemp = String(t) + String("°C");                                                     


  delay(4000);

  

  Firebase.setString("/DHT11/Humidity/value", fireHumid);                                 

  Firebase.setString("/DHT11/Temperature/value", fireTemp);         

  //Firebase.setBool("/Ispit/value", false);       
 

   

}
