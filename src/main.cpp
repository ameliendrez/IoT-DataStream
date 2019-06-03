#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#include <Sensor.h>

static char *urlBE="http://ec2-34-214-123-200.us-west-2.compute.amazonaws.com:8080/devices/";
static char postUrl[100] = "";

//Sensores reales
static HCSR04Sensor sensor(D4,D2);
// static DHTSensor sensor(D4, DHT::DHT11);
// static DHTSensor sensor(D4, DHT::AM2302);

// Sensores Simulados
// static THRSensor sensor;
// static DRSensor sensor;

void waitConnection();

void setup() {
  Serial.begin(115200);                 //Serial connection

  WiFi.begin("Antares", "");   //WiFi connection

  strcpy(postUrl, urlBE);
  strcat(postUrl, WiFi.macAddress().c_str() );

  Serial.print("POST url: ");
  Serial.println(postUrl);

  waitConnection();

}

void loop() {
 if(WiFi.status()== WL_CONNECTED){

   HTTPClient http;
   String data = sensor.getJSON();

   http.begin(postUrl);
   http.addHeader("Content-Type", "application/json");
   int httpCode = http.POST( data );


   Serial.print("Msg: ");
   Serial.println(data);
   Serial.print("HTTP response: ");
   Serial.println(httpCode);

   http.end();

   delay( sensor.wait() );
 }
 else {
    waitConnection();
 }
}


void waitConnection(){
  Serial.println("Esperando conexion");
  do {
    delay(1000);
    Serial.print(".");
  } while (WiFi.status() != WL_CONNECTED);
  Serial.println(" OK");
}
