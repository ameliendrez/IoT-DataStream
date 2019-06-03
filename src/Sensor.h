#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <Arduino.h>

#include <DHT.h>
#include <Ultrasonic.h>

class Sensor{
public:
  String getJSON();
  int wait();
};

class DHTSensor : public Sensor {
public:
  DHTSensor( int pin, DHT::DHT_MODEL_t model = DHT::DHT11 ){
    dht.setup(pin, model);
  }
  int wait(){
    return dht.getMinimumSamplingPeriod();
  }
  String getJSON(){
    String reply;
    reply = "{ ";
    reply += "\"temperature\": ";
    reply += dht.getTemperature();
    reply += ",";
    reply += " \"humidity\": ";
    reply += dht.getHumidity();
    reply += " }";
    return reply;
  }
private:
  DHT dht;
};

class THRSensor : public Sensor {
public:
  THRSensor( ){
  }
  int wait(){
    return 2000;
  }
  String getJSON(){
    float T = random(200,300)/10.0;
    float H = random(200,1000)/10.0;
    String reply;
    reply = "{ ";
    reply += "\"temperature\": ";
    reply += T;
    reply += ",";
    reply += " \"humidity\": ";
    reply += H;
    reply += " }";
    return reply;
  }
};


class HCSR04Sensor : public Sensor, public Ultrasonic {
public:
  HCSR04Sensor( int trig, int echo ) : Ultrasonic(trig, echo ){

  }
  int wait( ){
    return 1000;
  }
  String getJSON(){
    String reply;
    reply = "{ ";
    reply += "\"distance\": ";
    reply += Ultrasonic::Ranging(CM);
    reply += " }";
    return reply;
  }
};

class DRSensor : public Sensor {
public:
  DRSensor( ){

  }
  int wait( ){
    return 1500;
  }
  String getJSON(){
    float D = random(10,500)/10.0;
    String reply;
    reply = "{ ";
    reply += "\"distance\": ";
    reply += D;
    reply += " }";
    return reply;
  }
};

#endif
