#include "LedControlMS.h"
#include <MPU6050.h>

#define NBR_MTX 1 
LedControl lc = LedControl(D0,D2,D1, NBR_MTX);

MPU6050 mpu;

int gas = A0;
int pir = D3;

void setup()
{
 
  Serial.begin(9600);
  Serial.println("MPU6050 Starting");
  
  for (int i=0; i< NBR_MTX; i++)
  {
    lc.shutdown(i,false);
  
    lc.setIntensity(i,8);
  
    lc.clearDisplay(i);
                delay(100);
  }

  while(mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {
    Serial.println("Couldn't find valid MPU6050 sensor");
    delay(500);
    
  }

mpu.calibrateGyro();
mpu.setThreshold(3);
}

void loop()
{
    float temp = mpu.readTemperature();
     

    if (digitalRead(pir) ==HIGH){
                  lc.writeString(0,"INTRUDER ALERT");
                  
                  delay(1000);}
    if (temp >35){
                  lc.writeString(1,"TEMPERATURE ALERT");
                 
                  delay(1000);}
    if (analogRead(gas) > 600){
                  lc.writeString(2,"DANGER");
                  
                  delay(1000);}

    else {
                    lc.writeString(3,"COOL DOWN");
                    delay(3000);
                    lc.clearAll();} 
                    lc.clearAll();
                  }
