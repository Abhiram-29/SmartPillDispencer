#include <Wire.h>
#include <RtcDS3231.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
RtcDS3231<TwoWire> Rtc(Wire);
ESP8266WebServer server(80);

const char* ssid = "Guava";
const char* password =  "2351redapple";

int alarm1[] = {19,46},alarm2[] = {19,45};
 Servo s1,s2;

void setup () 
{
    s1.attach(0); 
    s2.attach(16);

    Serial.begin(115200);
    Rtc.Begin();
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
      Serial.println("RTC lost confidence in the DateTime!");
      Rtc.SetDateTime(compiled);
    RtcDateTime now = Rtc.GetDateTime();
    Serial.println(now.Year());
    Serial.println(compiled.Year());
    //Controlling the WIFI
    // WiFi.begin(ssid, password);
    // while (WiFi.status() != WL_CONNECTED) {
    //   delay(500);
    //   Serial.println("Waiting to connect...");
    // }
    // Serial.print("IP address: ");
    // Serial.println(WiFi.localIP());
    // server.on("/", handle_index);
    // server.begin();
}

void loop () 
{
    server.handleClient();
    RtcDateTime now = Rtc.GetDateTime();
    if(now.Hour() == alarm1[0] && now.Minute() == alarm1[1]){
      s1.write(180);
      delay(1000);
      s1.write(0);
    } 
    if(now.Hour() == alarm2[0] && now.Minute() == alarm2[1]){
      s2.write(180);
      delay(1000);
      s2.write(0);
    }
    Serial.println(now.Hour());
    Serial.println(now.Minute());
    delay(10000);
}

void handle_index() {
  server.send(200, "text/plain", "This is an index page.");
}