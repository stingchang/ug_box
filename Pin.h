#include <Arduino.h>
#ifndef H_Pin
#define H_Pin

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin


#define SENSOR_ROOM_HUMI_TEMP 13 // DHT 11

#define SENSOR_DWC_TEMP 8  // Mutiple DS18B20 sensors share same pin  

#define SENSOR_DWC1_PH A8
#define SENSOR_DWC1_TDS A10
#define SENSOR_DWC1_LEVEL 11

#define SENSOR_DWC2_PH A9
#define SENSOR_DWC2_TDS A11
#define SENSOR_DWC2_LEVEL 12

#define SWITCH_1_LIGHT1   46
#define SWITCH_2_LIGHT2   47
#define SWITCH_3_MIST     48
#define SWITCH_4_CO2      49
#define SWITCH_5_COOLER1  50 // small cooler 
#define SWITCH_6_PUMP1    51 // used for water change
#define SWITCH_7_PUMP2    52 // outside cooler, need to rurn on pump then cooler
#define SWITCH_8_COOLER2  53


/* These 'DATA_INDEX_' variable list mas to match MEGA */
// Convert 2 bytes to 4 digits number, ex: byte1 = '/00000011/, byte2 = '/00100000/=> 0000001100100000 =>2^10 + 2^9 + 2^6 = 1600
#define DATA_INDEX_LIGHT1 0        /* eg: 1430 = turn on at 14:30 */
#define DATA_INDEX_LIGHT1_ON_TIME 1        /* eg: 1430 = turn on at 14:30 */
#define DATA_INDEX_LIGHT1_OFF_TIME 2       /* eg: 1030 = turn off at 10:30 */
#define DATA_INDEX_LIGHT2 3        /* eg: 1430 = turn on at 14:30 */
#define DATA_INDEX_LIGHT2_ON_TIME 4
#define DATA_INDEX_LIGHT2_OFF_TIME 5
#define DATA_INDEX_ROOM_AUTO 6      /* 00 = off, 01 = on */

#define DATA_INDEX_CO2 8              /* ex: 1500 = 1500 PPM, transffered in 15.00 */
#define DATA_INDEX_CO2_AUTO_HIGH 10    /* ex: 1500 = 1500 PPM */
#define DATA_INDEX_CO2_AUTO_LOW 11     /* ex: 500 = 500 PPM */
#define DATA_INDEX_HUMIDITY 12        /* ex: 4510 = 45.1% */

#define DATA_INDEX_HUMIDITY_AUTO_HIGH 14
#define DATA_INDEX_HUMIDITY_AUTO_LOW 15
#define DATA_INDEX_TEMPERATUREC 16    /* ex: 2570 = 25.7'c */
#define DATA_INDEX_TEMPERATUREF 17    /* ex: 1050 = 105.0'f */

#define DATA_INDEX_DWC1_TDS 18         /* ex: 0656 = 6.56   */
#define DATA_INDEX_DWC1_TEMPERATURE_AUTO_STATUS 19
#define DATA_INDEX_DWC1_TEMPERATURE_AUTO_HIGH 20
#define DATA_INDEX_DWC1_TEMPERATURE_AUTO_LOW 21
#define DATA_INDEX_DWC1_TEMPERATURE 22
#define DATA_INDEX_DWC1_LEVEL 23  /* 00 = low, 01 = high */
#define DATA_INDEX_DWC1_PH 24  

#define DATA_INDEX_DWC2_TDS 25
#define DATA_INDEX_DWC2_TEMPERATURE_AUTO_STATUS 26
#define DATA_INDEX_DWC2_TEMPERATURE_AUTO_HIGH 27
#define DATA_INDEX_DWC2_TEMPERATURE_AUTO_LOW 28
#define DATA_INDEX_DWC2_TEMPERATURE 29
#define DATA_INDEX_DWC2_LEVEL 30
#define DATA_INDEX_DWC2_PH 31

// array size data
#define DATA_INDEX_DWC1_TEMPERATURE_24HOUR 33 // 33-56 , use 48 bytes
#define DATA_INDEX_DWC1_TEMPERATURE_7DAY 57   // 57-63 , use 14 bytes
#define DATA_INDEX_DWC1_PPM_24HOUR 64 // 64-87
#define DATA_INDEX_DWC1_PPM_7DAY 88   // 88-94

#define DATA_INDEX_DWC2_TEMPERATURE_24HOUR 89 // 89-112 , use 48 bytes
#define DATA_INDEX_DWC2_TEMPERATURE_7DAY 113   // 113-126 , use 14 bytes
#define DATA_INDEX_DWC2_PPM_24HOUR 127 // 127-151 , use 48 bytes
#define DATA_INDEX_DWC2_PPM_7DAY 152   // 152-165 , use 14 bytes

#endif
