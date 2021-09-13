
#include <Wire.h>
#include "Pin.h"
#include "DWC.h"
#include "Room.h"

#define dataBufferArraySize 2
#define I2C_TRANSMISSION_SIZE 32
int data[dataBufferArraySize][I2C_TRANSMISSION_SIZE];
int tempData[dataBufferArraySize][I2C_TRANSMISSION_SIZE];
int bufferIndex = 0;
const int16_t I2C_SLAVE = 0x08;

class Time {
  private:
    int day=1;
    int month=6;
    int year=2021;
  public:
    Time(int hour, int minute){
     setNow(hour, minute);
    }
    void setNow(int hour, int minute) {
        midNight = millis() - _HOUR * hour - _MINUTE * minute;
    }
    void setYearMonthDay(int year, int month, int day) {
      this->year = year;
      this->month = month;
      this->day = day;
    }
    int getYear() {
       return year;
    }
    int getMonth() {
       return month;
    }
    int getDay() {
       return day;
    }
    int getHour() {
        return (getNow() / _HOUR)%24;
    }
    int getMinute() {
        return (getNow() / _MINUTE)%60;
    }

    void updateDay() {
      
      if(month == 2 && day == 28) {
        if(year%4 != 0) {
          month++;
          day = 1;
        }
      } else if (month == 2 && day == 29) {
        if(year%4 == 0) {
          month++;
          day = 1;
        }
      } else if (day == 30) {
        if(month == 2 ||month == 4 ||month == 6 ||month == 9 ||month == 11)   {
          month++;
          day = 1;
        }
      } else if (day == 31) {
        if(month == 1 ||month == 3 ||month == 5 ||month == 7 ||month == 8||month == 10||month == 12)   {
          month++;
          day = 1;
        }  
      }
      if(month == 13) {
        month =1;
        year++;
      }
    }

    // milli second from mid night
    long getNow() {
      return millis() - midNight ;
    }
    const long _SECOND = 1000;
    const long _MINUTE = 60 * _SECOND;
    const long _HOUR = 60 * _MINUTE;
    const long _DAY = 24 * _HOUR;
    
    long midNight = 0;
};


DWC dwc1(SENSOR_DWC1_PH, SENSOR_DWC1_TDS, SENSOR_DWC1_LEVEL, SWITCH_5_COOLER1, SWITCH_6_PUMP1);
DWC dwc2(SENSOR_DWC2_PH, SENSOR_DWC2_TDS, SENSOR_DWC2_LEVEL, SWITCH_8_COOLER2, SWITCH_7_PUMP2);
Room room;

Time time(0,0);

void setup() {
  Wire.begin(I2C_SLAVE); 
  Wire.onReceive(receiveEvent);  
  Wire.onRequest(requestEvent); 
  Serial.begin(9600);
  
  initData();
  initLCD();
  dwc1.init();
  dwc2.init();
  room.init();

  

 delay(3000);
  initControl();
  
  delay(100);
}


void initControl() {

  pinMode(SWITCH_1_LIGHT1,OUTPUT);
  pinMode(SWITCH_2_LIGHT2, OUTPUT);
  pinMode(SWITCH_3_MIST, OUTPUT);
  pinMode(SWITCH_4_CO2, OUTPUT);
  
  pinMode(SWITCH_5_COOLER1, OUTPUT);
  pinMode(SWITCH_6_PUMP1, OUTPUT);
  pinMode(SWITCH_7_PUMP2, OUTPUT);
  pinMode(SWITCH_8_COOLER2, OUTPUT);

  digitalWrite(SWITCH_1_LIGHT1, (room.isLight1On ? LOW:HIGH));
  digitalWrite(SWITCH_2_LIGHT2, (room.isLight2On ? LOW:HIGH));
  digitalWrite(SWITCH_3_MIST, (room.isHumidifierOn ? LOW:HIGH));
  digitalWrite(SWITCH_4_CO2, (room.CO2ControllerOn ? LOW:HIGH));
  
  digitalWrite(SWITCH_5_COOLER1, (dwc1.coolerIsOn ? LOW:HIGH));
  digitalWrite(SWITCH_6_PUMP1, LOW);
  digitalWrite(SWITCH_7_PUMP2, (dwc2.coolerIsOn ? LOW:HIGH));
  digitalWrite(SWITCH_8_COOLER2, (dwc2.coolerIsOn ? LOW:HIGH));
}

void loop() {
  static long lastUpdateSecond = millis()-30 * time._SECOND-1;
  if(millis() - lastUpdateSecond > 10 * time._SECOND) {
    Serial.println("Read env params....");
    dwc1.update();
    dwc2.update();
    room.update();
    Serial.println("Auto Control check start....");
    checkAutoControl();
    delay(100);
    
    Serial.println("Update data start....");
    updateData();
    Serial.println();
    Serial.println("Update Message start....");
    updateMessage();

    lastUpdateSecond = millis();

    Serial.println("Update LCD start....");
    
  }
  
  static long lastUpdateLCDSecond = millis()-30 * time._SECOND-1;
  if(millis() - lastUpdateLCDSecond > 8 * time._SECOND) {
    updateLCD();
    lastUpdateLCDSecond = millis();
  }
  
  static long lastUpdateDay = millis()- time._DAY - 1;
  if(millis() - lastUpdateDay >= 1 * time._DAY) {
    time.updateDay();
    lastUpdateDay = millis();
  }
  
}
