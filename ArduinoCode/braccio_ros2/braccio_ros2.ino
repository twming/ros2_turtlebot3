#include <Servo.h>
#include <Braccio.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;
unsigned int _baseAngle = 90;
unsigned int _shoulderAngle = 90;
unsigned int _elbowAngle = 90;
unsigned int _wrist_verAngle = 90;
unsigned int _wrist_rotAngle = 90;
unsigned int _gripperAngle =120; //closed

const int BUFFER_SIZE = 6;
char buf[BUFFER_SIZE]={90,90,90,90,90,120};

void setup()
{ 
  //Initialzie the Braccio Arm and Serial Port : Bit rate 115200 to match with ROS2 default
  Braccio.begin();
  Serial.begin(115200);
}

void loop()
{  
  //Check if the Serial Port is available to read data
  if (Serial.available())
  {
      //Read data from Serial port and assign to buf memory
      Serial.readBytes(buf, BUFFER_SIZE);
      _baseAngle      =buf[0];
      _shoulderAngle  =buf[1];
      _elbowAngle     =buf[2];
      _wrist_verAngle =buf[3];
      _wrist_rotAngle =buf[4];
      _gripperAngle   =buf[5];

      //Move the Braccio Arm with the input angles
      Braccio.ServoMovement(20,_baseAngle,_shoulderAngle,_elbowAngle,_wrist_verAngle,_wrist_rotAngle,_gripperAngle);
  }

  Serial.flush();
  //delay(200);
  
}

