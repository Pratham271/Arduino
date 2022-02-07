#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

char auth[] = "";
char ssid[] = "Who_Killed_Knight_King";
char pass[] = "Arya Stark";
SimpleTimer timer;

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

int redColor = 0;
int greenColor = 0;
int blueColor = 0;

int gas=A0;
int gasval = 0;

void setup() 
{
  Serial.begin(9600);
  Blynk.begin(auth,ssid,pass);
  pinMode(gas,INPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  timer.setInterval(2000,sendUptime);
}

void  sendUptime()
{
  gasval = analogRead(gas);
  Serial.print("Gas value : "); 
  Serial.print(gasval);
  Blynk.virtualWrite(V0,gasval);  
  
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  redFrequency = pulseIn(sensorOut, LOW);
  redColor = map(redFrequency,70,120,255,0);
  Serial.print("R = ");
  Serial.print(redColor);
  Blynk.virtualWrite(V1,redColor);
  delay(100);
  
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  greenFrequency = pulseIn(sensorOut, LOW);
  greenColor = map(greenFrequency, 109,199,255,0);
  Serial.print("G=");
  Serial.print(greenColor);
  Blynk.virtualWrite(V1,greenColor);
  delay(100);

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  blueFrequency = pulseIn(sensorOut, LOW);
  blueColor = map(blueFrequency, 38,84,255,0);
  Serial.print("B = ");
  Serial.print(blueColor);
  Blynk.virtualWrite(V1,blueColor);
  delay(100);

  if(redColor > greenColor && redColor > blueColor){
  Serial.println(" - RED detected!");
}
if(greenColor > redColor && greenColor > blueColor){
  Serial.println(" - GREEN detected!");
}
  if(blueColor > redColor && blueColor > greenColor){
  Serial.println(" - BLUE detected!");
}
}

void loop() {
  // put your main code here, to run repeatedly:
    Blynk.run();
    timer.run();
    
}
