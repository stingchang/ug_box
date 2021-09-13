#include <Arduino.h>
#include "Pin.h"

#ifndef H_ROOM
#define H_ROOM

#include "DHT.h"    // air humid/temp
#define DHTTYPE DHT11     // AIR humid/temp
DHT dht(SENSOR_ROOM_HUMI_TEMP, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino

#include <CCS811.h> // air ppm
CCS811 airPPMSensor; // AIR PPM CCS811 airPPMSensor(&Wire, /*IIC_ADDRESS=*/0x5A);


class Room {
  private:
    void readHimidityTemerature();
    void readCO2();
    void initAirPPMSensor();
    boolean isAirPPMSensorReady;

    
  public:
    Room(){}

    void init();
    void update();
    void check();
//    void updateSetting();

    float CO2;
    float TVOC;
    float humidity;
    float tempC;
    float tempF;
    float heatIndex;

    bool isAutoControl = true;
    
    int light1OnHour = 5;
    int light1OnMinute = 0;
    int light1OffHour = 23;
    int light1OffMinute = 0;
    bool isLight1On = true;
    int light2OnHour = 5;
    int light2OnMinute = 0;
    int light2OffHour = 23;
    int light2OffMinute = 0;
    bool isLight2On = true;
    
    bool isHumidifierOn = true;
    bool CO2ControllerOn = true;

    bool humidityHigh();
    bool humidityLow();
    bool CO2High();
    bool CO2Low();
    float co2LowThreshold = 0;
    float co2HighThreshold = 850;
    float humidityHighThreshold = 80;
    float humidityLowThreshold = 55;
};
void Room::init(){

  initAirPPMSensor();
  dht.begin();
  Serial.println("Room sensors init complete");
}
void Room::initAirPPMSensor(){
    /*Wait for the chip to be initialized completely, and then exit*/
    static int tryTimeCount = 0;

    while (!isAirPPMSensorReady && tryTimeCount < 10) {
        if(airPPMSensor.begin() != 0) {
            tryTimeCount ++;
        } else {
            isAirPPMSensorReady = true;
        }
    } 

    if(isAirPPMSensorReady) {
        /**
         * @brief Set measurement cycle
         * @param cycle:in typedef enum{
         *                  eClosed,      //Idle (Measurements are disabled in this mode)
         *                  eCycle_1s,    //Constant power mode, IAQ measurement every second
         *                  eCycle_10s,   //Pulse heating mode IAQ measurement every 10 seconds
         *                  eCycle_60s,   //Low power pulse heating mode IAQ measurement every 60 seconds
         *                  eCycle_250ms  //Constant power mode, sensor measurement every 250ms
         *                  }eCycle_t;
         */
        airPPMSensor.setMeasCycle(airPPMSensor.eCycle_250ms);
        // Serial.println("Init Air PPM Sensor completed");
    }
}

void Room::update(){
  readHimidityTemerature();
  readCO2();
  Serial.println("Room update finished");
}
//
//void Room::updateSetting() {
//
//
//  light2OnHour = getDataByIndex("DATA_INDEX_LIGHT2_ON_TIME");
//  light2OnMinute = getDataByIndex("DATA_INDEX_LIGHT2_ON_TIME");
//  light2OffHour = getDataByIndex("DATA_INDEX_LIGHT2_OFF_TIME");
//  light2OffMinute = getDataByIndex("DATA_INDEX_LIGHT2_OFF_TIME");
//  
//  humidityLowThreshold = ((float)getDataByIndex("DATA_INDEX_HUMIDITY_AUTO_LOW") ) /100;
//  humidityHighThreshold = ((float)getDataByIndex("DATA_INDEX_HUMIDITY_AUTO_HIGH") ) /100;
//
//  co2LowThreshold = ((float)getDataByIndex("DATA_INDEX_HUMIDITY_AUTO_LOW") ) ;
//  co2HighThreshold = ((float)getDataByIndex("DATA_INDEX_HUMIDITY_AUTO_HIGH") ) ;
//}

void Room::readHimidityTemerature(){
  humidity = dht.readHumidity();
  tempC = dht.readTemperature(); // Read temperature as Celsius
  tempF = dht.readTemperature(true); // Read temperature as Fahrenheit

//Serial.println("Room humidity updating finished");
Serial.println(" DHT read humidity = "+String(humidity)+", tempC = "+String(tempC));
  if (isnan(humidity)) {
    humidity = -1;
  }
  if (isnan(tempC)) {
    tempC = -1;
  }
  if (isnan(tempF)) {
    tempF = -1;
  }
  if(humidity>0 && tempF>0){
    heatIndex = dht.computeHeatIndex(tempF, humidity);
  }
  
//  Serial.println("Room humidity updated finished");
}
void Room::readCO2(){
  if(!isAirPPMSensorReady) {
    Serial.println(" CO2 Sensor not ready");
    return;
  }
  Serial.println("Room CO2 updating");
//  if(airPPMSensor.checkDataReady() == true){
  CO2 = airPPMSensor.getCO2PPM();    //Unit: ppm  
  TVOC = airPPMSensor.getTVOCPPB();  //Unit: ppb
  

/*!
   * @brief Set baseline
   * @param get from getBaseline.ino
   */
  airPPMSensor.writeBaseLine(0x847B);
//  Serial.println("Room CO2 updated");
}

bool Room::humidityHigh(){
  return humidity >= humidityHighThreshold;
}
bool Room::humidityLow() {
  return humidity <= humidityLowThreshold;
}
bool Room::CO2High(){
  return CO2 >= co2HighThreshold;
}
bool Room::CO2Low() {
  return CO2 <= co2LowThreshold;
}
#endif
