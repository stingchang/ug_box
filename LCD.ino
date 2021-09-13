// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).
//   D0 connects to digital pin 22
//   D1 connects to digital pin 23
//   D2 connects to digital pin 24
//   D3 connects to digital pin 25
//   D4 connects to digital pin 26
//   D5 connects to digital pin 27
//   D6 connects to digital pin 28
//   D7 connects to digital pin 29
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define SOME_COLOR   0xAF3F

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;

void initLCD(void) {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

  #ifdef USE_ADAFRUIT_SHIELD_PINOUT
    Serial.println(F("Using Adafruit 2.8\" TFT Arduino Shield Pinout"));
  #else
    Serial.println(F("Using Adafruit 2.8\" TFT Breakout Board Pinout"));
  #endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  

  uint16_t identifier = tft.readID();

  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    return;
  }

  tft.begin(identifier);
//
//  Serial.println(F("Benchmark                Time (microseconds)"));
//
//  Serial.print(F("Screen fill              "));
//  Serial.println(testFillScreen());
//  delay(500);
//
//  Serial.print(F("Text                     "));
//  Serial.println(testText());
//  delay(3000);
//
//  Serial.print(F("Lines                    "));
//  Serial.println(testLines(CYAN));
//  delay(500);
//
//  Serial.print(F("Horiz/Vert Lines         "));
//  Serial.println(testFastLines(RED, BLUE));
//  delay(500);
//
//  Serial.print(F("Rectangles (outline)     "));
//  Serial.println(testRects(GREEN));
//  delay(500);
//
//  Serial.print(F("Rectangles (filled)      "));
//  Serial.println(testFilledRects(YELLOW, MAGENTA));
//  delay(500);
//
//  Serial.print(F("Circles (filled)         "));
//  Serial.println(testFilledCircles(10, MAGENTA));
//
//  Serial.print(F("Circles (outline)        "));
//  Serial.println(testCircles(10, WHITE));
//  delay(500);
//
//  Serial.print(F("Triangles (outline)      "));
//  Serial.println(testTriangles());
//  delay(500);
//
//  Serial.print(F("Triangles (filled)       "));
//  Serial.println(testFilledTriangles());
//  delay(500);
//
//  Serial.print(F("Rounded rects (outline)  "));
//  Serial.println(testRoundRects());
//  delay(500);
//
//  Serial.print(F("Rounded rects (filled)   "));
//  Serial.println(testFilledRoundRects());
//  delay(500);

  Serial.println(F("Done!"));
}

void updateLCD() {
  static int page = 0;

  tft.setRotation(3);
  tft.fillScreen(BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);  tft.setTextSize(3);
  tft.println("UrbanGro!");
  tft.setTextColor(SOME_COLOR);  tft.setTextSize(2);
  tft.println(String(time.getMonth())+"/"+String(time.getDay())+"/"+String(time.getYear())+" "+(time.getHour()<10 ? "0":"")+String(time.getHour())+":"+(time.getMinute()<10 ? "0":"")+String(time.getMinute()));

  if(page == 0) {
    printRoom();
  } else if(page == 1) {
    printDWC1();
  } else if(page == 2) {
    printDWC2();
  }
  page = (page+1)%3;
  
}

void printRoom() {

  String msg;
  tft.setTextColor(BLUE); tft.setTextSize(2);
  msg=msg+"\nGrow Room";
  tft.println(msg);
  
  

  tft.setTextColor(CYAN); tft.setTextSize(2);
  msg="";
  msg=msg+"Auto control " +(room.isAutoControl ? "ON" : "OFF");
  tft.println(msg);
  
  msg="";
  msg = msg+"Light1 " +(room.isLight1On ? "on":"off");
  msg = msg+", "+String(room.light1OnHour)+":"+(room.light1OnMinute<10 ? "0":"")+String(room.light1OnMinute)+" ~ "+String(room.light1OffHour)+":"+(room.light1OffMinute<10 ? "0":"")+String(room.light1OffMinute)+"";
  tft.println(msg);
  
  msg = "";
  msg = msg+"Light2 " +(room.isLight2On ? "on":"off");
  msg = msg+", "+String(room.light2OnHour)+":"+(room.light2OnMinute<10 ? "0":"")+String(room.light2OnMinute)+" ~ "+String(room.light2OffHour)+":"+(room.light2OffMinute<10 ? "0":"")+String(room.light2OffMinute);
  tft.println(msg);
  
  msg = "";
  msg = msg+"Humidity: "+String(room.humidity)+"%, 加濕 " +(room.isHumidifierOn ? "on":"off") +" , "+String(room.humidityLowThreshold)+"~"+String(room.humidityHighThreshold);
  tft.println(msg);
  msg="";
  msg = msg+"Temperature: " + String(room.tempC) +"'C";
  tft.println(msg);
  msg="";
  msg = msg+"CO2: x" + ", TVOC: x"+"\nheatIndex: " + String(room.heatIndex) ;
  tft.println(msg);

}
void printDWC1() {
  String msg;

   tft.setTextColor(GREEN); tft.setTextSize(2);
  msg = "";
  msg = msg+"\nDWC 1";
  tft.println(msg);
  
  msg = "";
  tft.setTextColor(YELLOW); tft.setTextSize(2);
  msg = msg+"Auto control " + (dwc1.isAutoControl? " ON ":" OFF ");
  tft.println(msg);
  msg="";
  msg =msg+ "Temp: " + String(dwc1.getTempC()) + "'C, \nRange: " + String(dwc1.tempLowThreshold) + "'C~"+String(dwc1.tempHighThreshold)+"'C";
  tft.println(msg);
  msg="";
  msg =msg+ "Cooler: " + (dwc1.coolerIsOn ? "on":"off") + ", Pump " +(dwc1.pumpIsOn ? "on":"off");
  tft.println(msg);

  
  msg = "";
  msg = "TDS: " + String(dwc1.getTds()) + " PPM ";
  tft.println(msg);
  msg = "";
  msg = msg+ "pH: " + String(dwc1.getPh());
  tft.println(msg);
  msg = "";
  msg = msg+ "Level: " + String(digitalRead(11));
  tft.println(msg);
}
void printDWC2() {
  String msg;

  tft.setTextColor(RED); tft.setTextSize(2);
  msg="";
  msg=msg+"\nDWC 2";
  tft.println(msg);
  tft.setTextColor(MAGENTA); tft.setTextSize(2);

  msg="";
  msg = msg+"Auto control "+(dwc2.isAutoControl? " ON ":" OFF ");
  tft.println(msg);
  msg = "";
  msg =msg+ "Temp: " + String(dwc2.getTempC()) + "'C, \nRange: " + String(dwc2.tempLowThreshold) + "'C ~ "+String(dwc2.tempHighThreshold)+"'C";
  tft.println(msg);
  msg = "";
  msg =msg+ "Cooler: " + (dwc2.coolerIsOn ? "on":"off") + ", Pump " +(dwc2.pumpIsOn ? "on":"off");
  tft.println(msg);
  msg = "";
  msg =msg+ "TDS: " + String(dwc2.getTds()) + " PPM ";
  tft.println(msg);
  msg = "";
  msg = msg + "pH: " + "NA";
  tft.println(msg);
  msg = "";
  msg =msg+ "Level: " + String(digitalRead(12));
  tft.println(msg);
}

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(BLACK);
  tft.fillScreen(RED);
  tft.fillScreen(GREEN);
  tft.fillScreen(BLUE);
  tft.fillScreen(BLACK);
  return micros() - start;
}

unsigned long testText() {
  tft.fillScreen(BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;
}









unsigned long testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(BLACK);

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  tft.fillScreen(BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);

  return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(BLACK);
  start = micros();
  for(y=0; y<h; y+=5) tft.drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(BLACK);
  n     = min(tft.width(), tft.height());
  start = micros();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    tft.drawRect(cx-i2, cy-i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  n = min(tft.width(), tft.height());
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx-i2, cy-i2, i, i, color2);
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = tft.width()  + radius,
                h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = tft.width()  / 2 - 1,
                      cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  n     = min(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(0, 0, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(0, i, i));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(i, i, 0));
  }

  return t;
}

unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    tft.drawRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(i, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  start = micros();
  for(i=min(tft.width(), tft.height()); i>20; i-=6) {
    i2 = i / 2;
    tft.fillRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(0, i, 0));
  }

  return micros() - start;
}