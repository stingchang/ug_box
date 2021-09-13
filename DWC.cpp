#include "DWC.h"

void DWC::init() {
  initTemperatureSensor();
  initPPMSensor();
  Serial.println("DWC "+String(id)+" sensord init complete");
}

//void ::DWC::updateSetting() {
//  isAutoControl = getDataByIndex("DATA_INDEX_DWC1_TEMPERATURE_AUTO_STATUS") > 0;
//  tempLowThreshold = ((float)getDataByIndex("DATA_INDEX_DWC1_TEMPERATURE_AUTO_LOW") ) /100;
//  tempHighThreshold = ((float)getDataByIndex("DATA_INDEX_DWC1_TEMPERATURE_AUTO_HIGH") ) /100;
//}

float DWC::getTempC() {
  return tempC;
}
float DWC::getTds() {
  return ppm;
}
float DWC::getPh() {
  return ph;
}
void DWC::update() {
//  Serial.println("Readingupdate dwc"+String(id)+"temp");
  updateTemperature();
//  Serial.println("Reading dwc"+String(id)+"ppm");
  updatePPM();
//  Serial.println("Reading dwc"+String(id)+"ph");
  updatePh();
//  Serial.println("Reading dwc"+String(id)+"level");
  updateLevel();
  Serial.println("DWC "+String(id)+" update finished");
}
void DWC::initTemperatureSensor() {
  Serial.print("Init water temperature sensor " +String(id));
     // Start up the library
  waterTempSensors.begin();

  if(waterTempSensors.getAddress(tempDeviceAddress, id))    {
     waterTempSensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
     Serial.println(", resolution set to: " + String(waterTempSensors.getResolution(tempDeviceAddress), DEC));
  } else {
    Serial.println("... Could not detect address. Check power and cabling");
  }
}

void DWC::initPPMSensor(){
  gravityTds.setPin(tdsPin);
  gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();  //initialization
}

void DWC::updateTemperature() {
  waterTempSensors.requestTemperatures();
  if(waterTempSensors.getAddress(tempDeviceAddress, id))
  {
    tempC = waterTempSensors.getTempC(tempDeviceAddress);
    // Get Degree F from Degree C: DallasTemperature::toFahrenheit(waterTemp)
    // Read again from sensor: waterTempSensors.getTempF(tempDeviceAddress);
  }
  isTempLow = tempC <= tempLowThreshold;
  isTempHigh = tempC >= tempHighThreshold;
}

const float VREF = 5.0; // analog reference voltage(Volt) of the ADC
const int SAMPLE_COUNT = 30; // sum of sample point
void DWC::updatePPM() {
    gravityTds.setTemperature(tempC);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate 
    ppm = gravityTds.getTdsValue();  // then get the value
}
void DWC::updatePh() {
  unsigned long int avgValue; 
  int buf[10],temp;
  for(int i=0;i<10;i++) 
  { 
    buf[i]=analogRead(phPin);
    delay(10);
  }
  for(int i=0;i<9;i++)
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)
    avgValue+=buf[i];
  float pHVol=(float)avgValue*5.0/1024/6;
  ph = -5.70 * pHVol + 29.6;// adjust: put ph sensor in a ph 7.0 water, read output ph and update 29.6, for example, output 6.8, then update 29.6 to 29.6 - (7-6.8)

}
void DWC::updateLevel() {
  isLevelLow = digitalRead(levelPin)<1;
}


int DWC::getMedianNum(int bArray[], int iFilterLen) 
{
      int bTab[iFilterLen];
      for (byte i = 0; i<iFilterLen; i++)
      bTab[i] = bArray[i];
      int i, j, bTemp;
      for (j = 0; j < iFilterLen - 1; j++) 
      {
      for (i = 0; i < iFilterLen - j - 1; i++) 
          {
        if (bTab[i] > bTab[i + 1]) 
            {
        bTemp = bTab[i];
            bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
         }
      }
      }
      if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
      else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
      return bTemp;
}

void DWC::setTempThreshold(float tempLowThreshold, float tempHighThreshold){
  this->tempLowThreshold = tempLowThreshold;
  this->tempHighThreshold = tempHighThreshold;
}
