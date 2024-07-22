#include <Servo.h>
#include <Braccio.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;
int _baseAngle = 20;
int _shoulderAngle = 90;
int _elbowAngle = 90;
int _wrist_verAngle = 90;
int _wrist_rotAngle = 90;
int _gripperAngle =73; //closed

const int BUFFER_SIZE = 12;
byte buf[BUFFER_SIZE]={20,90,90,90,90,73};

void setup()
{ 
  //Initialzie the Braccio Arm and Serial Port : Bit rate 115200 to match with ROS2 default
  Braccio.begin();
  Serial.begin(115200);
  Braccio.ServoMovement(20,_baseAngle,_shoulderAngle,_elbowAngle,_wrist_verAngle,_wrist_rotAngle,_gripperAngle);
}

void loop()
{  
  //Check if the Serial Port is available to read data
  if (Serial.available())
  {
      //Read data from Serial port and assign to buf memory
      Serial.readBytes(buf, BUFFER_SIZE);
      _baseAngle      = (int(0)|buf[0]) <<8 | buf[1];
      _shoulderAngle  = (int(0)|buf[2]) <<8 | buf[3];
      _elbowAngle     = (int(0)|buf[4]) <<8 | buf[5];
      _wrist_verAngle = (int(0)|buf[6]) <<8 | buf[7];
      _wrist_rotAngle = (int(0)|buf[8]) <<8 | buf[9];
      _gripperAngle   = (int(0)|buf[10]) <<8 | buf[11];

      //Move the Braccio Arm with the input angles
      Braccio.ServoMovement(20,_baseAngle,_shoulderAngle,_elbowAngle,_wrist_verAngle,_wrist_rotAngle,_gripperAngle);
  }

  Serial.flush();
  //delay(200);
  
}
