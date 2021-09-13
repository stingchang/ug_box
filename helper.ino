void checkAutoControl(){

  
  if(dwc1.isAutoControl){ 
    if( dwc1.coolerIsOn && dwc1.isTempLow) {
      digitalWrite(SWITCH_5_COOLER1, HIGH);
      dwc1.coolerIsOn = false;
    }
    if( !dwc1.coolerIsOn && dwc1.isTempHigh){
      digitalWrite(SWITCH_5_COOLER1, LOW);
      dwc1.coolerIsOn = true;
    }
  }
  if(dwc2.isAutoControl){ 
    if( dwc2.coolerIsOn && dwc2.isTempLow) {
      digitalWrite(SWITCH_7_PUMP2, HIGH);
      digitalWrite(SWITCH_8_COOLER2, HIGH);
      dwc2.coolerIsOn = false;
    }
    if( !dwc2.coolerIsOn && dwc2.isTempHigh){
      digitalWrite(SWITCH_7_PUMP2, LOW);
      delay(3 * time._SECOND);
      digitalWrite(SWITCH_8_COOLER2, LOW);
      dwc2.coolerIsOn = true;
    }
  }
  if(room.isAutoControl) {
     // light
    if(!room.isLight1On && (time.getHour() >= room.light1OnHour && time.getMinute() >= room.light1OnMinute)) {
        digitalWrite(SWITCH_1_LIGHT1, LOW);
        room.isLight1On = true;
    }
    if(room.isLight1On && (time.getHour() > room.light1OffHour && time.getMinute() >= room.light1OffMinute)) {
        digitalWrite(SWITCH_1_LIGHT1, HIGH);
        room.isLight1On = false;
    }
    if(!room.isLight2On && (time.getHour() >= room.light2OnHour && time.getMinute() >= room.light2OnMinute)) {
        digitalWrite(SWITCH_2_LIGHT2, LOW);
        room.isLight2On = true;
    }
    if(room.isLight2On && (time.getHour() >= room.light2OffHour && time.getMinute() >= room.light2OffMinute)) {
        digitalWrite(SWITCH_2_LIGHT2, HIGH);
        room.isLight2On = false;
    }
  
    if(room.isHumidifierOn && room.humidityHigh() || (time.getMinute() > 40)) {
      digitalWrite(SWITCH_3_MIST, HIGH);
      room.isHumidifierOn = false;
    }
    if(!room.isHumidifierOn && room.humidityLow() &&  (time.getMinute() <= 40)) {
      digitalWrite(SWITCH_3_MIST, LOW);
      room.isHumidifierOn = true;
    }
  }
  updateLCD();  
}
void updateMessage() {


  String msg;
  
  msg = "";
  
  msg = msg + "Room auto" +(room.isAutoControl ? " on" : "off") ;
  msg = msg + "Light1 : " +(room.isLight2On ? "on":"off");
  msg = msg + ", auto time: "+String(room.light1OnHour)+":"+String(room.light1OnMinute)+"~"+String(room.light1OffHour)+":"+String(room.light1OffMinute);
  msg = msg + "; Light2 : " +(room.isLight2On ? "on":"off");
  msg = msg + ", auto time: "+String(room.light1OnHour)+":"+String(room.light1OnMinute)+"~"+String(room.light1OffHour)+":"+String(room.light1OffMinute);
  msg = msg + "\n";
  msg = msg + "Humidity "+room.humidity+", humidifier : " +(room.isHumidifierOn ? "on":"off");
  msg = msg + "; Temperature : " + String(room.tempC) +"'C";
  msg = msg + "; CO2:x" + ", TVOC:x"+", heatIndex : " + String(room.heatIndex) ;
  Serial.println(msg);

  msg = "";
  msg = msg + "DWC 1 auto"+(dwc1.isAutoControl? " ON ":" OFF ");
//  msg = msg + "\n";
  msg = msg + ", TempC: " + String(dwc1.getTempC()) + "'C, threshold = " + String(dwc1.tempLowThreshold) + "'C ~ "+String(dwc1.tempHighThreshold)+"'C";
  msg = msg + ", cooler " + (dwc1.coolerIsOn ? "on":"off") + ", pump" +(dwc1.pumpIsOn ? "on":"off");
  msg = msg + ", TDS = " + String(dwc1.getTds()) + " PPM ";
  msg = msg + ", pH = " + String(dwc1.getPh());
  msg = msg + ", level = " + String(digitalRead(11));
  Serial.println(msg);

  msg = "";
  msg = msg + "DWC 2 auto"+(dwc2.isAutoControl? " ON ":" OFF ");
//  msg = msg + "\n";
  msg = msg + ", TempC: " + String(dwc2.getTempC()) + "'C, threshold = " + String(dwc2.tempLowThreshold) + "'C ~ "+String(dwc2.tempHighThreshold)+"'C";
  msg = msg + ", cooler " + (dwc2.coolerIsOn ? "on":"off") + ", pump" +(dwc2.pumpIsOn ? "on":"off");
  msg = msg + ", TDS = " + String(dwc2.getTds()) + " PPM ";
  msg = msg + ", pH = " + String(dwc2.getPh());
  msg = msg + ", level = " + String(digitalRead(12));

  msg = msg + "\n";
  Serial.println(msg);

  msg = "";
  msg = msg + 
  
  Serial.println();
}
/*
08:04:24.331 -> CO2/PPMC Data is not ready!
08:04:25.353 -> Room auto on, dwc1  on, dwc2  on
08:04:25.388 -> DWC 1 temperature : 20.50, tds : 6.87, level = 0, ph = 6.42
08:04:25.430 -> DWC 2 temperature : 21.50, tds : 6.72, level = 0, ph = 24.79
08:04:25.495 -> Room : 21.80'C / 71.24'F , humidity : 65.00, CO2:x, TVOC:x, heatIndex : 71.12
08:04:25.567 -> Light1 : off; Light2 : off; Humidifier : off; CO2Controller : off
08:04:25.642 -> DWC 1 Cooler : off; DWC 1 Pump : off; DWC 2 Cooler : off; DWC 2 Pump : off
08:04:25.749 -> Light 1 on time : 4:0, off time: 22:0, Light 2 on time : 4:0, off time: 22:0
08:04:25.822 -> Humidity : 65.00 threshold = 40.00'C ~ 80.00'CCO2 : 0.00  threshold = 0.00 PPM ~ 850.00 PPM
08:04:25.893 -> DWC1 temp threshold = 17.00'C ~ 25.00'C, DWC2 temp threshold = 17.00'C ~ 25.00'C

*/

void updateData() {
  
  setDataByIndex(DATA_INDEX_LIGHT1, (room.isLight1On ? 1: 0));
  
  setDataByIndex(DATA_INDEX_LIGHT1_ON_TIME, room.light1OnHour*100+room.light1OnMinute);
  setDataByIndex(DATA_INDEX_LIGHT1_OFF_TIME, room.light1OffHour*100+room.light1OffMinute);
  setDataByIndex(DATA_INDEX_LIGHT2, (room.isLight2On ? 1: 0));
  setDataByIndex(DATA_INDEX_LIGHT2_ON_TIME, room.light2OnHour*100+room.light2OnMinute);
  setDataByIndex(DATA_INDEX_LIGHT2_OFF_TIME, room.light2OffHour*100+room.light2OffMinute);
  setDataByIndex(DATA_INDEX_ROOM_AUTO, room.isAutoControl);

  setDataByIndex(DATA_INDEX_CO2, room.CO2 );              /* 8 ex: 1500 = 1500 PPM */
  setDataByIndex(DATA_INDEX_CO2_AUTO_HIGH, room.co2HighThreshold );    /* ex: 1500 = 1500 PPM */
  setDataByIndex(DATA_INDEX_CO2_AUTO_LOW, room.co2LowThreshold );     /* ex: 500 = 500 PPM */
  setDataByIndex(DATA_INDEX_HUMIDITY, room.humidity *100);      /* ex: 4510 = 45.1% */
  setDataByIndex(DATA_INDEX_HUMIDITY_AUTO_HIGH, room.humidityHighThreshold *100);
  setDataByIndex(DATA_INDEX_HUMIDITY_AUTO_LOW, room.humidityLowThreshold *100);
  setDataByIndex(DATA_INDEX_TEMPERATUREC, room.tempC * 100);   /* ex: 2570 = 25.7'c */
  setDataByIndex(DATA_INDEX_TEMPERATUREF, room.tempF * 100);    /* ex: 1050 = 105.0'f */

  setDataByIndex(DATA_INDEX_DWC1_PH, dwc1.getPh() * 100);        /* ex: 0656 = 6.56   */
  setDataByIndex(DATA_INDEX_DWC1_TEMPERATURE_AUTO_STATUS, (dwc1.isAutoControl ? 1: 0));
  setDataByIndex(DATA_INDEX_DWC1_TEMPERATURE_AUTO_HIGH, dwc1.tempHighThreshold * 100);
  setDataByIndex(DATA_INDEX_DWC1_TEMPERATURE_AUTO_LOW, dwc1.tempLowThreshold * 100);
  setDataByIndex(DATA_INDEX_DWC1_TEMPERATURE, dwc1.getTempC() * 100);
  setDataByIndex(DATA_INDEX_DWC1_LEVEL, (dwc1.isLevelLow ? 1: 0) );  /* 00 = low, 01 = high */
  setDataByIndex(DATA_INDEX_DWC1_TDS, dwc1.getTds() );  /* 00 = low, 01 = high */
  
  setDataByIndex(DATA_INDEX_DWC2_PH, dwc2.getPh() * 100);        /* ex: 0656 = 6.56   */
  setDataByIndex(DATA_INDEX_DWC2_TEMPERATURE_AUTO_STATUS, (dwc2.isAutoControl ? 1: 0));
  setDataByIndex(DATA_INDEX_DWC2_TEMPERATURE_AUTO_HIGH, dwc2.tempHighThreshold * 100);
  setDataByIndex(DATA_INDEX_DWC2_TEMPERATURE_AUTO_LOW, dwc2.tempLowThreshold * 100);
  setDataByIndex(DATA_INDEX_DWC2_TEMPERATURE, dwc2.getTempC() * 100);
  setDataByIndex(DATA_INDEX_DWC2_LEVEL, (dwc2.isLevelLow ? 1: 0) );  /* 00 = low, 01 = high */
  setDataByIndex(DATA_INDEX_DWC2_TDS, dwc2.getTds() );  /* 00 = low, 01 = high */

// array size data
//  setDataByIndex(DATA_INDEX_DWC1_TEMPERATURE_24HOUR 33 // 33-56 , use 48 bytes
//  setDataByIndex(DATA_INDEX_DWC1_TEMPERATURE_7DAY 57   // 57-63 , use 14 bytes
//  setDataByIndex(DATA_INDEX_DWC1_PPM_24HOUR 64 // 64-87
//  setDataByIndex(DATA_INDEX_DWC1_PPM_7DAY 88   // 88-94
//
//  setDataByIndex(DATA_INDEX_DWC2_TEMPERATURE_24HOUR 89 // 89-112 , use 48 bytes
//  setDataByIndex(DATA_INDEX_DWC2_TEMPERATURE_7DAY 113   // 113-126 , use 14 bytes
//  setDataByIndex(DATA_INDEX_DWC2_PPM_24HOUR 127 // 127-151 , use 48 bytes
//  setDataByIndex(DATA_INDEX_DWC2_PPM_7DAY 152   // 152-165 , use 14 bytes


  for(int i =0; i< 32; i++) {

//    Serial.print("Data set to "+String(getDataByIndex(i))+" ");
//    if(i%2 == 1)
//      Serial.print(" ");
//    if(i%8 == 7)
//      Serial.println(" ");
  }
  Serial.println();

}

void requestEvent() {
  Serial.println("----- Respond data request to ESP8266 -----");


  for(int i =0; i< 32; i++) {
    Wire.write((byte)data[bufferIndex][i]);
    Serial.print((byte)data[bufferIndex][i]);
    if(i%2 == 1)
      Serial.print(" ");
  }
  Serial.println();
}
// TODO
void receiveEvent(int howMany) {
    
  Serial.println("----- Received "+String(howMany)+" bytes from ESP8266-----");
  
  if(howMany == 1) 
    updateIndex();
  else if(howMany == 2)
    updateTime();
  else if(howMany == 4) // yy m d
    updateYearMonthDay();
  else if(howMany == 3)
    updateEnvControl();
  else if(howMany = 32)
    updateEnvironmentSetting();
  Serial.println();
}

void updateIndex() {
  bufferIndex = Wire.read();
  Serial.println("Set index to "+String(bufferIndex));  
}

void updateEnvControl() {
  int index = Wire.read()%32;
  int h = Wire.read();
  int m = Wire.read();
  setDataByIndex(index, h*100+m);
  Serial.println("Set index "+String(index)+" to "+String(getDataByIndex(index))+"("+String(h*100+m)+")");  

  updateControl();
}


void updateTime() {
  int hour = Wire.read()%24;
  int minute = Wire.read()%60;
  time.setNow(hour, minute);
  Serial.println("Set time to "+String(hour)+":"+String(minute));
}
void updateYearMonthDay() {
  int y1 = Wire.read();
  int y2 = Wire.read();
  int m = Wire.read();
  int d = Wire.read();
  
  time.setYearMonthDay(y1*100+y2, m, d);
  Serial.println("Set Year/Month/Day to "+String(time.getYear())+":"+String(time.getMonth())+":"+String(time.getDay()));
}


void updateRequestData(int dataIndex) {
  int val = tempData[bufferIndex][(dataIndex%16) * 2]*100+tempData[bufferIndex][(dataIndex%16) * 2+1];
  setDataByIndex(dataIndex, val);
  
}
void updateEnvironmentSetting(){
  int num =0;
//  Serial.println("Update buffer "+String(bufferIndex) + " : ");
  
  for(int i =0; i< I2C_TRANSMISSION_SIZE; i++) {

    tempData[bufferIndex][i] = Wire.read();
    Serial.print("("+String(i)+" "+String(i)+","+String(tempData[bufferIndex][i])+")");
  }

  if(bufferIndex == 0){
    
    updateRequestData(DATA_INDEX_ROOM_AUTO);
    updateRequestData(DATA_INDEX_LIGHT1_ON_TIME);
    updateRequestData(DATA_INDEX_LIGHT1_OFF_TIME);
    updateRequestData(DATA_INDEX_LIGHT2_ON_TIME);
    updateRequestData(DATA_INDEX_LIGHT2_OFF_TIME);
    updateRequestData(DATA_INDEX_HUMIDITY_AUTO_HIGH);
    updateRequestData(DATA_INDEX_HUMIDITY_AUTO_LOW);
    
  } else if(bufferIndex == 1){
    updateRequestData(DATA_INDEX_DWC1_TEMPERATURE_AUTO_STATUS);
    updateRequestData(DATA_INDEX_DWC1_TEMPERATURE_AUTO_HIGH);
    updateRequestData(DATA_INDEX_DWC1_TEMPERATURE_AUTO_LOW);
    updateRequestData(DATA_INDEX_DWC2_TEMPERATURE_AUTO_STATUS);
    updateRequestData(DATA_INDEX_DWC2_TEMPERATURE_AUTO_HIGH);
    updateRequestData(DATA_INDEX_DWC2_TEMPERATURE_AUTO_LOW);
  }
  
  updateControl();
  Serial.println();
//
//  room.updateSetting;
//Serial.print("Update buffer "+String(bufferIndex) + " : ");

}

void updateControl(){
  room.isAutoControl = getDataByIndex("DATA_INDEX_ROOM_AUTO") > 0;
  room.light1OnHour = getDataByIndex("DATA_INDEX_LIGHT1_ON_TIME")/100;
  room.light1OnMinute = getDataByIndex("DATA_INDEX_LIGHT1_ON_TIME")%100;
  room.light1OffHour = getDataByIndex("DATA_INDEX_LIGHT1_OFF_TIME")/100;
  room.light1OffMinute = getDataByIndex("DATA_INDEX_LIGHT1_OFF_TIME")%100;
  room.light2OnHour = getDataByIndex("DATA_INDEX_LIGHT2_ON_TIME")/100;
  room.light2OnMinute = getDataByIndex("DATA_INDEX_LIGHT2_ON_TIME")%100;
  room.light2OffHour = getDataByIndex("DATA_INDEX_LIGHT2_OFF_TIME")/100;
  room.light2OffMinute = getDataByIndex("DATA_INDEX_LIGHT2_OFF_TIME")%100;

  dwc1.isAutoControl = getDataByIndex("DATA_INDEX_DWC1_TEMPERATURE_AUTO_STATUS") > 0;
  dwc1.tempLowThreshold = ((float)getDataByIndex("DATA_INDEX_DWC1_TEMPERATURE_AUTO_LOW") ) /100;
  dwc1.tempHighThreshold = ((float)getDataByIndex("DATA_INDEX_DWC1_TEMPERATURE_AUTO_HIGH") ) /100;
  dwc2.isAutoControl = getDataByIndex("DATA_INDEX_DWC2_TEMPERATURE_AUTO_STATUS") > 0;
  dwc2.tempLowThreshold = ((float)getDataByIndex("DATA_INDEX_DWC2_TEMPERATURE_AUTO_LOW") ) /100;
  dwc2.tempHighThreshold = ((float)getDataByIndex("DATA_INDEX_DWC2_TEMPERATURE_AUTO_HIGH") ) /100;  

Serial.print("ESP8166 request Update : ");
Serial.println("room auto "+String((room.isAutoControl ? "ON" : "OFF")));
Serial.println("Light1 on from " + String(room.light1OnHour) + ":" +String(room.light1OnMinute) + " to " +String(room.light1OffHour) + ":" +String(room.light1OffMinute));
Serial.println("Light2 on from " + String(room.light2OnHour) + ":" +String(room.light2OnMinute) + " to " +String(room.light2OffHour) + ":" +String(room.light2OffMinute));

Serial.println("DWC 1 auto "+String((dwc1.isAutoControl ? "ON" : "OFF")));
Serial.print("DWC 1 temperature threshold : " + String(dwc1.tempLowThreshold) + "% ~ " +String(dwc1.tempHighThreshold) + "%");
Serial.println("DWC 2 auto "+String((dwc2.isAutoControl ? "ON" : "OFF")));
Serial.print("DWC 2 temperature threshold : " + String(dwc2.tempLowThreshold) + "% ~ " +String(dwc2.tempHighThreshold) + "%");  
}

//
int getDataByIndex(int dataIndex ) {
  int a = dataIndex*2/I2C_TRANSMISSION_SIZE;
  int b = dataIndex*2%I2C_TRANSMISSION_SIZE;
//  String val;
  int val = 
        (int)data[a][b] * 100 +
        (int)data[a][b+1];
  
  return val;
}
void setDataByIndex(int dataIndex, int val) {
  
  data[(dataIndex*2)/I2C_TRANSMISSION_SIZE][(dataIndex*2)%I2C_TRANSMISSION_SIZE] = val/100;
  data[(dataIndex*2)/I2C_TRANSMISSION_SIZE][(dataIndex*2)%I2C_TRANSMISSION_SIZE+1] = val%100;
}

//
//String toBinary(char c) {
//  String str;
//  
//  for(int i =0; i< 8; i++) {
//    str = ((c >> i) & 1 > 0 ? "1" : "0") + str;
//  }
//
//  return str;
//}
//String toBinaryFromInt(int c) {
//  String str;
//  
//  for(int i =0; i< 16; i++) {
//    str = ((c >> i) & 1 > 0 ? "1" : "0") + str;
//    if(i == 15) str = " "+  str;
//  }
//
//  return str;
//}


void initData() {
  for(int curBuffer = 0; curBuffer< dataBufferArraySize; curBuffer++) {
    for(int currentData = 0; currentData< I2C_TRANSMISSION_SIZE; currentData++) {
      data[curBuffer][currentData] = -1;
    }
  }
}
