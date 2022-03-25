#include <NMEAGPS.h>
#include <GPSport.h>

NMEAGPS gps;
gps_fix fix;

//Global Variabel
float kecepatan;
int satelit;


void GPSloop()
{
  while (gps.available( gpsPort )) {
    fix = gps.read();
    Serial.print(F("  Kecepatan: "));
    if (fix.valid.speed){
      kecepatan = fix.speed_kph();
      Serial.print(kecepatan);
    }

    Serial.print(F(" Satelit: "));
    satelit = fix.satellites;
    Serial.println(satelit);
    
  }

}


void setup() {
  // put your setup code here, to run once:
  gpsPort.begin(9600);
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  GPSloop();

  //GPS speed
  Serial2.print("t0.txt=\""); // Changing the value of box n1
        Serial2.print(kecepatan);
        Serial2.print("\"");
        Serial2.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial2.write(0xff);
        Serial2.write(0xff);

   //Satelit
   Serial2.print("t10.txt=\""); // Changing the value of box n1
        Serial2.print(satelit);
        Serial2.print("\"");
        Serial2.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial2.write(0xff);
        Serial2.write(0xff);


}
