#include <TinyGPS++.h>

RTC_DATA_ATTR int bootCount = 0;

//Declare the Hardware Serial to be used by the GPS
HardwareSerial gpsSerial(2);

void setup() {
  //Deepsleep setup
  ++bootCount;

  Serial.begin(115200);
  while (!Serial)
    ;           // wait for serial to be initalised
  delay(2000);  // give time to switch to the serial monitor
  Serial.println(F("\nSetup"));

  //Start the hardware serial (rx2,tx2) to read data from gps device
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);
  delay(10);

  while (!gpsSerial)
    ;           // wait for serial to be initalised

  //Display on Serial Monitor
  Serial.println("Serials are Connected.");
  Serial.println("Waiting For GPS Data...");
  Serial.println("#################");
}
//End void setup()

bool isUpdated(TinyGPSPlus& gps) {
  return  gps.location.isValid() && gps.date.isValid() && gps.time.isValid() && gps.satellites.isValid() && gps.altitude.isValid() && gps.speed.isValid() && gps.course.isValid() && gps.hdop.isValid();
}

bool isValid(TinyGPSPlus& gps) {
  return  gps.location.isUpdated() && gps.date.isUpdated() && gps.time.isUpdated() && gps.satellites.isUpdated() && gps.altitude.isUpdated() && gps.speed.isUpdated() && gps.course.isUpdated() && gps.hdop.isUpdated();
}


void loop() {
  TinyGPSPlus gps;

  unsigned long start = millis();
  while (millis() - start < 2000 && !isValid(gps)) {
    while (gpsSerial.available() > 0) {
      gps.encode(gpsSerial.read());
    }
  }

  if (isValid(gps)) {
    Serial.println("###################################");
    Serial.print("LAT = ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("LONG = "); 
    Serial.println(gps.location.lng(), 6);
    Serial.print("Date in UTC = ");
    Serial.println(String(gps.date.year()) + "/" + String(gps.date.month()) + "/" + String(gps.date.day()));
    Serial.print("Time in UTC = ");
    Serial.println(String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second()) + "." + String(gps.time.centisecond()));
    Serial.print("Satellites = "); 
    Serial.println(gps.satellites.value());
    Serial.print("ALT (min) = "); 
    Serial.println(gps.altitude.meters());
    Serial.print("SPEED (km/h) = "); 
    Serial.println(gps.speed.kmph());
    Serial.print("COURSE = "); 
    Serial.println(gps.course.deg());
    Serial.print("HDOP = "); 
    Serial.println(gps.hdop.value() / 100.0);
  } else {
    Serial.println("GPS positioning data not valid");
  }

  Serial.println("---------------------------------");
}
//End void loop()
