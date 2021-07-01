#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <DS3231.h>
#include <SD.h>
#include <SPI.h>
#include <dht.h>
#include <ArduinoJson.h>

//masukin pin input sama declare variable
//sensor arus
const int arus = A4 ;
int nilai = 0;
//int sense = 30; //20
//int offset = 2500;
float adcvol = 0;
float current = 0;

//sensor tegangan
const int voltage = A1;
float vout = 0.0;
float vin = 0.0;
int volt = 0;

//SD Card
int pinCS = 53;

//Temperature DHT
dht DHT; 
float hum;
float temp;

//Buat object dari classes (OOP)
TinyGPSPlus gps;
DS3231 rtc(SDA, SCL); 
File myFile;

unsigned long previousMillis=0;

LiquidCrystal_I2C lcd(0x27,16,4);  // set the LCD address

void setup() {
//mulai

  //bagian LCD
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  
Serial.begin(9600);
  lcd.begin(16,4);
  rtc.begin();

SD.begin();

  //set waktu
    //rtc.setTime(23,14,00); // format: hour, min, sec
    //rtc.setDate(18,1,2021); //format: date, mon, year
    //rtc.setDOW(1); //1 monday - 7 sunday
}


void loop() {
  // put your main code here, to run repeatedly:
  //arus
  nilai = analogRead(arus);
  adcvol = (nilai/1023.0)*5;
  current = adcvol - 2.5; //Nilai 2.5 ini merupakan nilai offset
  current = adcvol * 200;
  
  
  //voltage
  volt = analogRead(voltage);
  vout = constrain(volt, 714, 1023); //range terendah 38.4
  vout = (volt / 1023.0)*5.0;
  vin = vout * 10.999;
  //Coba pake fungsi constrain() sama map()

  int chk = DHT.read22 (2);
  temp= DHT.temperature;

 while(Serial.available())
  {
    gps.encode(Serial.read());
  }

 if (SD.begin())
  {
    lcd.setCursor(10,0); 
    lcd.print("OK"); 
  } 
    if ((unsigned long)(millis() - previousMillis) >= 1000){
        myFile = SD.open("coba2.txt", FILE_WRITE);
    if (myFile) {
    myFile.print(F("Date: "));    
    myFile.print(rtc.getDateStr());
    myFile.print(F(" , ")); 
    myFile.print(F("Time: "));    
    myFile.print(rtc.getTimeStr());
    myFile.print(F(" , ")); 
    myFile.print(F("MPH: "));     
    myFile.print(gps.speed.kmph());
    myFile.print(F(" , "));
    myFile.print(F("Latitude: "));
    myFile.print(gps.location.lat(), 10);
    myFile.print(F(" , "));
    myFile.print(F("Longitude: "));
    myFile.print(gps.location.lng(), 10);
    myFile.print(F(" , "));
    myFile.print(F("Satellite Connect: "));
    myFile.print(gps.satellites.value());
    myFile.print(F(" , "));
    myFile.print(F("Humidity: "));
    myFile.print(hum);
    myFile.print(F(" , "));
    myFile.print(F("Temperature: "));
    myFile.println(temp);
    myFile.print(F(" , "));
    myFile.print(F("Current: "));
    myFile.print(current);
    myFile.print(F(" , "));
    myFile.print(F("Voltage: "));
    myFile.print(vin);
    myFile.print(F(" , "));
    myFile.print(F("Power: "));
    myFile.print(F(" , "));
    myFile.print(vin*current);
    myFile.print(F(" , "));
    myFile.print(F("Raw Current: "));
    myFile.println(nilai);
    myFile.close();  
  }
  else {
    lcd.setCursor(10,0); 
    lcd.print("ER");
}
}
  //line 1
  lcd.setCursor(0,0); 
  lcd.print("ITS MSBT"); 
  lcd.setCursor(14,0);
  lcd.print(gps.satellites.value());

  //line 2
  lcd.setCursor(0,1);
  lcd.print((vin*current),1);
  lcd.setCursor(6,1);
  lcd.print("W");
  lcd.setCursor(8,1);
  lcd.print(rtc.getTimeStr());

  //line 3 SAMA line 4 POSISI 0 NYA DI -4
  //line 3
  lcd.setCursor(-4,2);
  lcd.print(vin,1);
  lcd.setCursor(2,2);
  lcd.print("V");
  lcd.setCursor(4,2);
  lcd.print((gps.speed.kmph()),1);
  lcd.setCursor(9,2);
  lcd.print("kph");
  
  //line 4
  lcd.setCursor(-4,3);
  lcd.print(current,1);
  lcd.setCursor(2,3);
  lcd.print("A");
  lcd.setCursor(4,3);
  lcd.print(temp,1);
  lcd.setCursor(10,3);
  lcd.print("C");
  lcd.setCursor(9,3);
  lcd.print((char)223);

  //buatJson(vin, current, temp);
}

