#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 3); // RX, TX
char cmd='s';
int delayTime=10;
int totalTime=50;

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
    cmd=(char)mySerial.read();
  }

  switch (cmd) {
  case 'w':
    //Forward
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    delay(delayTime);
    
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(totalTime-delayTime);
    break;
  case 'x':
    //Backward
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    delay(delayTime);
    
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(totalTime-delayTime);
    break;
  case 'a':
    //Left
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    delay(delayTime);
    
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(totalTime-delayTime);
    break;
  case 'd':
    //Right
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    delay(delayTime);
    
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(totalTime-delayTime);
    break;
  case '1':
    delayTime=15;
    break;
  case '2':
    delayTime=25;
    break;
  case '3':
    delayTime=40;
    break;
  default:
    // Stop
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    break;
  }

  //delay(1000);
}


  // if (Serial.available()) {
  //   mySerial.write(Serial.read());
  // }

