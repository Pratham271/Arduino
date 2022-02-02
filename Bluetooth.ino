#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define OLED_RESET 5

Adafruit_SSD1306 display(OLED_RESET);
Servo servo;

int bulb_1 = 3;
int bulb_2 = 4;

int fan_1 = 6;
int fan_2 = 7;

void setup() {
  pinMode(bulb_1, OUTPUT);
  pinMode(bulb_2, OUTPUT);
  pinMode(fan_1, OUTPUT);
  pinMode(fan_2, OUTPUT);
  
  servo.attach(8);
  
  Serial.begin(9600);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay(); 
  display.setTextSize(1); 
  display.setTextColor(WHITE); 
  display.setCursor(0,28);
  display.println("*AUTOMATION*");
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  if (Serial.available() > 0)
  { 
    char c = Serial.read();
    if (c == '1')
    {
     digitalWrite(bulb_1,HIGH);
     digitalWrite(bulb_2,LOW);
     Serial.print("Bulb 1 HIGH");
     display.clearDisplay();
     display.setCursor(0, 28);
     display.println("BULB 1 ON");
     display.display();
    }
    
    if(c=='2')
    {
     digitalWrite(bulb_2,HIGH);
     digitalWrite(bulb_1,LOW);
     Serial.print("Bulb 2 HIGH");
     display.clearDisplay();
     display.setCursor(0, 28);
     display.println("BULB 2 ON");
     display.display();
    }
    
    if(c=='3')
    {
     digitalWrite(bulb_1,HIGH);
     digitalWrite(bulb_2,HIGH);
     Serial.print("Bulb 1 & Bulb 2 HIGH");
     display.clearDisplay();
     display.setCursor(0, 28);
     display.println("BULB 1 & BULB 2 ON");
     display.display();
    }
    
    if(c=='4')
    {
     digitalWrite(bulb_1,LOW);
     digitalWrite(bulb_2,LOW);
     Serial.print("Bulb 1 & Bulb 2 LOW");
     display.clearDisplay();
     display.setCursor(0, 28);
     display.println("BULB 1 & BULB 2 OFF");
     display.display();
    }

    if(c=='5')
    {
     digitalWrite(fan_1,HIGH);
     digitalWrite(fan_2,LOW);
     Serial.print("Fan 1 HIGH");
     display.clearDisplay();
     display.setCursor(0, 28);
     display.println("FAN 1 ON");
     display.display();
    }

    if(c=='6')
    {
     digitalWrite(fan_1,LOW);
     digitalWrite(fan_2,HIGH);
     Serial.print("Fan 2 HIGH");
     display.clearDisplay();
     display.setCursor(0, 28);
     display.println("FAN 2 ON");
     display.display();
    }

    if(c=='7')
    {
     digitalWrite(fan_1,HIGH);
     digitalWrite(fan_2,HIGH);
     Serial.print("Fan 1 & FAN 2 HIGH");
     display.clearDisplay();
     display.setCursor(0, 28);
     display.println("FAN 1 & FAN 2 ON");
     display.display();
    }

    if(c=='8')
    {
     digitalWrite(fan_1,LOW);
     digitalWrite(fan_2,LOW);
     Serial.print("Fan 1 & Fan 2 LOW");
     display.clearDisplay();
     display.setCursor(0, 28);
     display.println("FAN 1 & FAN 2 OFF");
     display.display();
    }

    if(c=='9')
    {
     servo.write(90);
     Serial.print("Door open");
     display.clearDisplay();
     display.setCursor(0, 28);
     display.println("DOOR OPEN");
     display.display();
    }

    if(c=='z')
    {
     servo.write(0);
     Serial.print("Door closed");
     display.clearDisplay();
     display.setCursor(0, 28);
     display.println("DOOR CLOSED");
     display.display();
    }
  }
}
