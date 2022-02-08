#include<Wire.h>
#include<Servo.h>

Servo servo_1; 
Servo servo_2;
Servo servo_3; 
Servo servo_4;

const int MPU_addr=0x68; 
int16_t axis_X,axis_Y,axis_Z; 
int minVal=265; 
int maxVal=402;

double x;
double y;
double z;

void setup()
{ 
Serial.begin(9600);
Wire.begin();

//Initilize 12C Communication 
Wire.beginTransmission(MPU_addr); //Start communication

Wire.write(0x6B);

Wire.write(0);

//Writes to Register 6B

Wire.endTransmission(true); //Ends 12C transmission

servo_1.attach(2); // Forward/Reverse_Motor 
servo_2.attach(3); // Up/Down_Motor 
servo_3.attach(4); // Gripper Motor 
servo_4.attach(5); // Left/Right Motor
}

void loop()
{
Wire.beginTransmission(MPU_addr); 
Wire.write(0x3B); //Start with regsiter 0x3B
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true); //Read 14 Registers
axis_X=Wire.read()<<8|Wire.read(); //Reads the MPU6050 X,Y,Z AXIS
axis_Y=Wire.read()<<8|Wire.read();
axis_Z=Wire.read()<<8|Wire.read(); 
int xAng = map(axis_X,minVal,maxVal,-90,90); // Maps axis values in terms of -90 to +90
int yAng=map(axis_Y,minVal,maxVal,-90,90);
int zAng=map(axis_Z,minVal,maxVal,-90,90);

x=RAD_TO_DEG*(atan2(-yAng, -zAng)+PI);
y=RAD_TO_DEG*(atan2(-xAng, -zAng)+PI);
z= RAD_TO_DEG*(atan2(-yAng, -xAng)+PI);


int gripper;
int flex_sensorip = analogRead(A0);

if(flex_sensorip > 750)
{
//Reads flex sensor output

gripper = 0;

}

else {

gripper = 180;

}

servo_3.write(gripper);

if(x >=0 && x <=60)
{
int mov1=map(x,0,60,0,90);
Serial.print("Movement in F/R = ");
Serial.print(mov1);
Serial.println((char)176); 
servo_1.write(mov1); 
}

else if(x >=300 && x <= 360)
{
int mov2= map(x,360,250,0,180);
Serial.print("Movement in Up/Down = "); 
Serial.print(mov2);
Serial.println((char)176); 
servo_2.write(mov2);
}

if(y >= 0 && y <=60)
{
int mov3= map(y,0,60,90,180);
Serial.print("Movement in Left =");
Serial.print(mov3);
Serial.println((char)176);
servo_4.write(mov3);

}

else if(y >=300 && y <=360)
{
int mov3= map(y,360,300,90,0); 
Serial.print("Movement in Right = "); 
Serial.print(mov3); 
servo_4.write(mov3);
}
}
