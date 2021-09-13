#include <Arduino.h>
#include "Pin.h"
#ifndef H_DWC
#define H_DWC


#include <OneWire.h>    // water temp
#include <DallasTemperature.h>

static OneWire oneWire(SENSOR_DWC_TEMP);  // Water temp: Setup a oneWire instance to communicate with any OneWire devices(not just Maxim/Dallas temperature ICs)
static DallasTemperature waterTempSensors(&oneWire);  // Pass our oneWire reference to Dallas Temperature.
static DeviceAddress tempDeviceAddress;  // We'll use this variable to store a found device DeviceAddress
#include "GravityTDS.h"


#define TEMPERATURE_PRECISION 9
static int increment;
class DWC {
  private:
    float tempC;
    float ppm;
    int id;
    float ph;
    GravityTDS gravityTds;


    
    void initTemperatureSensor();
    void initPPMSensor();
    void updateTemperature();
    void updatePPM();
    void updateLevel();
    void updatePh();

    int getMedianNum(int[], int);

    byte tdsPin;
    byte phPin;
    byte levelPin;
    byte coolerPin;
    byte pumpPin;

  public :
    DWC(int phPin, int tdsPin, int levelPin, int coolerPin, int pumpPin) {
      this->phPin = phPin;
      this->tdsPin = tdsPin;
      this->levelPin = levelPin;
      
      id = id + increment;
      increment++;
    }
    void setTempThreshold(float, float);
    void init();
    void update();
    bool check();// TODO
    float getTds();
    float getPh();
    float getTempC();
//    void updateSetting();
    
    bool isAutoControl = true;
    bool isTempLow;
    bool isTempHigh;
    bool isLevelLow;
    bool coolerIsOn = false;
    bool pumpIsOn = false;
    float tempLowThreshold = 17.0;
    float tempHighThreshold = 22.0;

    
};

#endif
