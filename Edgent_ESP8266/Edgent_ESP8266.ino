#define BLYNK_TEMPLATE_ID "TMPL3QviO3U7A"
#define BLYNK_TEMPLATE_NAME "SmartPillDispencer"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
#include <Wire.h>
#include <RtcDS3231.h>
#include <Servo.h>

RtcDS3231<TwoWire> Rtc(Wire);

Servo s1,s2;

int alarm1,alarm2;

void setup()
{
  Serial.begin(115200);
  delay(100);
  s1.attach(12); 
  //s2.attach(16);
  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Rtc.SetDateTime(compiled);
  RtcDateTime now = Rtc.GetDateTime();

  pinMode(16,OUTPUT);

  BlynkEdgent.begin();
}

BLYNK_WRITE(V0)
{
    int value = param.asInt();
    if(value == 1){
      s1.write(180);
      tone(16,1000);
      delay(1000);
      noTone(16);
      s1.write(0);
      delay(1000);
      Serial.println(Rtc.GetDateTime().Hour());
      Serial.println("Servo1 activated");
    }
}

// BLYNK_WRITE(V1)
// {
//     int value = param.asInt();
//     if(value == 1){
//       s2.write(180);
//       delay(1000);
//       s2.write(0);
//       delay(1000);
//       Serial.println("Servo2 activated");
//     }
// }

BLYNK_WRITE(V2){
 alarm1 = param[0].asInt();
 if(alarm1 == 0)
 {
  alarm1 = 999999;
 }
}

// BLYNK_WRITE(V3){
//  alarm2 = param[0].asInt();
//  if(alarm2 == 0)
//  {
//   alarm2 = 999999;
//  }
//}

void loop() {
  BlynkEdgent.run();
   RtcDateTime now = Rtc.GetDateTime();
   int currentTime = 3600*(now.Hour())+60*(now.Minute());

   if(alarm1 == currentTime){
     s1.write(180);
     tone(16,1000);
     delay(1000);
     noTone(16);
     s1.write(0);
     delay(1000);
     Serial.println("Alarm1 Triggered");
     Serial.println(Rtc.GetDateTime().Hour());

   }
  //  if(alarm2 == currentTime){
  //    s2.write(180);
  //    delay(1000);
  //    s2.write(0);
  //    delay(1000);
  //    Serial.println("Alarm2 Triggered");
  //    Serial.println(Rtc.GetDateTime().Hour());
  //  }
   
}