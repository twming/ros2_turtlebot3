#include <SoftwareSerial.h>
#include "Ultrasonic.h"

SoftwareSerial mySerial(4, 3); // RX, TX
Ultrasonic ultrasonic(12);

char cmd='s';
int speedTime=0;
// int totalTime=50;
long rangeInCentimeters;
long counter=0;
char buf[3];

void setup() {
  pinMode(5, OUTPUT);    // ENA
  pinMode(6, OUTPUT);    // ENB
  pinMode(7, OUTPUT);    // M1 -> M1A
  pinMode(9, OUTPUT);    // M2 -> M1B
  pinMode(10, OUTPUT);   // M3 -> M2B
  pinMode(11, OUTPUT);   // M4 -> M2A

  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Welcome to HC-06 Bluetooth Mobile Robot!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Port OK!");
}

void loop() { // run over and over
  if (mySerial.available()) {
    mySerial.readBytes(buf,3);
  }

  if (buf[0]=='0') {
    cmd=buf[1];
  }
  else
  {
    cmd=buf[0];
  }

  switch (cmd) {
  case 'N':
    //Forward
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    delay(25+speedTime);
    
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(25-speedTime);
    break;
  case 'S':
    //Backward
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    delay(25+speedTime);
    
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(25-speedTime);
    break;
  case 'W':
    //Left
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    delay(25+speedTime);
    
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(25-speedTime);
    break;
  case 'E':
    //Right
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    delay(25+speedTime);
    
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(25-speedTime);
    break;
  case 'A':
    //NE
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    delay(10+speedTime);

    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    delay(30-speedTime);

    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(10);
    break;
  case 'D':
    //NW
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    delay(10+speedTime);

    digitalWrite(7, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(30-speedTime);

    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(10);
    break;
  case 'B':
    //SE
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    delay(10+speedTime);
    
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    delay(30-speedTime);

    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(10);
    break;
  case 'C':
    //SW
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    delay(10+speedTime);
    
    digitalWrite(7, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(30-speedTime);

    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(10);
    break;
  case '1':
    speedTime=-5;
    delay(50);
    break;
  case '2':
    speedTime=0;
    delay(50);
    break;
  case '3':
    speedTime=5;
    delay(50);
    break;
  case '4':
    speedTime=10;
    delay(50);
  case '0':
    // Stop
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(50);
    break;
  default:
    break;
  }

  counter=counter+1;
  if (counter==20)
  {
    rangeInCentimeters = ultrasonic.MeasureInCentimeters();
    // mySerial.print("Obstacle in front is : ");
    // mySerial.println(rangeInCentimeters);
    counter=0;
  }
  //delay(1000);
}


  // if (Serial.available()) {
  //   mySerial.write(Serial.read());
  // }

