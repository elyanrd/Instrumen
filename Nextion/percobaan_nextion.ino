#include <dht.h>

dht DHT;
int temp;

void setup() {

  Serial.begin(9600);           //The default baud rate of the Nextion TFT is 9600.
  Serial1.begin(9600);
  pinMode(A1, INPUT);           //Define that pin as input

}

void loop() {
  // put your main code here, to run repeatedly:
  while (!Serial1.available()) {
    Serial.println("Nextion ngk nyambung");
  }
  int chk = DHT.read22 (2);
  temp = DHT.temperature;
  Serial1.write("t2.val=");              //We print the variable we want to cahnge on the screen
  Serial1.write(temp);                        //Print the value we want to be displayed
  Serial1.write(0xff);                         //Selesai ngrim
  Serial1.write(0xff);
  Serial1.write(0xff);

}
