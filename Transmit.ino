#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <MPU6050.h>
const int MPU_addr=0x68; 
int16_t axis_X,axis_Y,axis_Z,AcX,AcY,AcZ; 
int minVal=265; 
int maxVal=402;
double x;
double y;
double z;
int temp;
RH_ASK driver;
const char *msg;
#define period 10000
void setup()
{
    Serial.begin(9600);    // Debugging only
    Wire.begin();
    Wire.beginTransmission (MPU_addr);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission (true);
    if (!driver.init())
         Serial.println("init failed");
}
void loop()
{    
       Wire.beginTransmission (MPU_addr);
       Wire.write(0x3B);
       Wire.endTransmission(false);
       Wire.requestFrom(MPU_addr,14,true);
       long st=millis();
       axis_X=Wire.read()<<8|Wire.read();
       axis_Y=Wire.read()<<8|Wire.read();
       axis_Z=Wire.read()<<8|Wire.read();
       int xAng = map(axis_X,minVal,maxVal,-90,90);
       int yAng = map(axis_Y,minVal,maxVal,-90,90);
       int zAng = map(axis_Z,minVal,maxVal,-90,90);
       x = RAD_TO_DEG*(atan2(-yAng, -zAng)+PI);
       y = RAD_TO_DEG*(atan2(-xAng, -zAng)+PI);
       z = RAD_TO_DEG*(atan2(-yAng, -xAng) +PI);
       AcX=Wire.read()<<8|Wire.read(); //Acccelration along X axis
       AcY=Wire.read()<<8|Wire.read(); //Acccelration along Y axis
       AcZ=Wire.read()<<8|Wire.read(); //Acccelration along Z axis
       temp = Wire.read()<<8|Wire.read();
       int t = temp;
       int tempc = t/340 + 36.53;
       int tempf = (tempc*9/5) + 32;
       int temperature = map(tempc,-100,100,15,20);
       delay(250); 
       while(millis()<st+period)
       {
       if(AcX>=65 && AcX<=80)
       { 
          
          Serial.println("The value of accelerometer is between 65 and 80");
          msg="The value of accelerometer is between 65 and 80";
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          delay(1000);
          
       }
       else if(AcY<=-10 && AcY>=-35)
          {
            Serial.println("The value of accelerometer is between -10 and -35");
            msg="The value of accelerometer is between -10 and -35";
            driver.send((uint8_t *)msg, strlen(msg));
            driver.waitPacketSent();
            delay(1000);
          }
       else if(AcY>=10 && AcY<=35)
          {
            Serial.println("The value of accelerometer is between 10 and 35");
            msg="The value of accelerometer is between 10 and 35";
            driver.send((uint8_t *)msg, strlen(msg));
            driver.waitPacketSent();
            delay(1000);
          }
       else if(AcZ<=-10 && AcX>=-80)
        {
          Serial.println("The value of accelerometer is between -10 and -80");
          msg="The value of accelerometer is between -10 and -80";
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          delay(1000);
        }
       else
        {
          Serial.println("error reading values");
          msg="error reading values";
        }
      }
        delay(1000);
       while(millis()<st+period)
       {
        if(x>=0 && x<=90 )
       {
          Serial.println("The angle read by gyro in x direction is between 0 and 90");
          msg="The angle read by gyro in x direction is between 0 and 90"; 
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          delay(1000);  
       }
       else if(x>90 && x<=180)
       {
          Serial.println("The angle read by gyro in x direction is between 90 and 180");
          msg="The angle read by gyro in x direction is between 90 and 180"; 
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          delay(1000);  
       }
       else if(x>180 && x<=270)
       {
          Serial.println("The angle read by gyro in x direction is between 180 and 270");
          msg="The angle read by gyro in x direction is between 180 and 270"; 
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          delay(1000);  
       }
       else if(x>270 && x<=360)
       {
          Serial.println("The angle read by gyro in x direction is between 270 and 360");
          msg="The angle read by gyro in x direction is between 270 and 360";  
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          delay(1000); 
       }
       if(y>=0 && y<=90 )
       {
          Serial.println("The angle read by gyro in y direction is between 0 and 90");
          msg="The angle read by gyro in y direction is between 0 and 90";   
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          delay(1000);
       }
       else if(y>90 && y<=180)
       {
          Serial.println("The angle read by gyro in y direction is between 90 and 180");
          msg="The angle read by gyro in y direction is between 90 and 180";  
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          delay(1000); 
       }
       else if(y>180 && y<=270)
       {
          Serial.println("The angle read by gyro in y direction is between 180 and 270");
          msg="The angle read by gyro in y direction is between 180 and 270"; 
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          delay(1000);  
       }
       else if(y>270 && y<=360)
       {
          Serial.println("The angle read by gyro in y direction is between 270 and 360");
          msg="The angle read by gyro in y direction is between 270 and 360";   
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          delay(1000);
       }
       }
       while(millis()<st+period)
       {
          if(temperature == 15){
             Serial.println("15.00 C");
             msg = "15.00";
             driver.send((uint8_t *)msg, strlen(msg));
             driver.waitPacketSent();
             delay(1000);   
          }
          else if(temperature == 16){
             Serial.println("16.00 C");
             msg = "16.00";
             driver.send((uint8_t *)msg, strlen(msg));
             driver.waitPacketSent();
             delay(1000);   
          }
          else if(temperature == 17){
             Serial.println("17.00 C");
             msg = "17.00";
             driver.send((uint8_t *)msg, strlen(msg));
             driver.waitPacketSent();
             delay(1000);   
          }
          else if(temperature == 18){
             Serial.println("18.00 C");
             msg = "18.00";
             driver.send((uint8_t *)msg, strlen(msg));
             driver.waitPacketSent();
             delay(1000);   
          }
          if(temperature == 19){
             Serial.println("19.00 C");
             msg = "19.00";
             driver.send((uint8_t *)msg, strlen(msg));
             driver.waitPacketSent();
             delay(1000);   
          }
          else if(temperature == 20){
             Serial.println("20.00 C");
             msg = "20.00";
             driver.send((uint8_t *)msg, strlen(msg));
             driver.waitPacketSent();
             delay(1000);   
          }
       }
        delay(1000);        
} 
