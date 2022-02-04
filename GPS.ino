#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd (12,11,5,4,3,2);
// Choose two Arduino pins to use for software serial

int RXPin = 2;

int TXPin = 3;

int GPSBaud = 9600;

// Create a TinyGPS++ object

TinyGPSPlus gps;

// Create a software serial port called "gpsSerial" 
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup()

{
 lcd.begin(16,2);
// Start the Arduino hardware serial port at 9600 baud 
Serial.begin(9600);

// Start the software serial port at the GPS's default baud 
gpsSerial.begin(GPSBaud);

}

void loop() {


 
// This sketch displays information every time a new sentence 15 correctly encoded.

while (gpsSerial.available() > 0) 
if (gps.encode(gpsSerial.read()))
{
displayInfo();
}
// If 5000 milliseconds pass and there are no characters coming in // over the software serial port, show a "No GPS detected" error 
if (millis() > 5000 && gps.charsProcessed() < 10)
{
Serial.println("No GPS detected");
while(true);
}
}

void displayInfo()
{
lcd.clear();

if (gps.location.isValid())

{
Serial.print("Latitude: "); 
Serial.println(gps.location.lat(), 6);
lcd.setCursor(0,0); 
lcd.print("LAT = ");
lcd.setCursor(7,0);
lcd.print(gps.location.lat(), 6);
delay(1000);
lcd.clear();
Serial.print("Longitude: "); 
Serial.println(gps.location.lng(), 6); 
lcd.setCursor(0,0); 
lcd.print("LON = ");
lcd.setCursor(7,0);
lcd.print(gps.location.lng(), 6);
delay(1000);
lcd.clear();
Serial.print("Altitude: "); 
Serial.println(gps.altitude.meters());
lcd.setCursor(0,0); 
lcd.print("ALT = ");
lcd.setCursor(7,0);
lcd.print(gps.altitude.meters(), 6);
delay(1000);
lcd.clear();

}

else

{ 
  Serial.println("Location: Not Available");
}

Serial.print("Date: "); 
if (gps.date.isValid())
{

Serial.print(gps.date.month());
Serial.print("/");
lcd.setCursor(0,0); 
lcd.print("MONTH = ");
lcd.setCursor(8,0);
lcd.print(gps.date.month());
delay(1000);
lcd.clear();
Serial.print(gps.date.day()); 
Serial.print("/");
lcd.setCursor(0,0); 
lcd.print("DAY = ");
lcd.setCursor(6,0);
lcd.print(gps.date.day());
delay(1000);
lcd.clear();
Serial.println(gps.date.year());
lcd.setCursor(0,0); 
lcd.print("Year = ");
lcd.setCursor(8,0);
lcd.print(gps.date.year());
delay(1000);
lcd.clear();
}

else

{
Serial.println("Not Available");
}

Serial.print("Time: "); 
if (gps.time.isValid())
{

if (gps.time.hour() < 10) Serial.print(F("0"));

Serial.print(gps.time.hour());

Serial.print(":");

if (gps.time.minute() < 10) Serial.print(F("0")); 
Serial.print(gps.time.minute()); 
Serial.print(":");

if (gps.time.second() < 10) Serial.print(F("0")); 
Serial.print(gps.time.second()); 
Serial.print(".");

if (gps.time.centisecond() < 10) Serial.print(F("0"));

Serial.println(gps.time.centisecond());
}
else
{
Serial.println("Not Available");
}
Serial.println();
Serial.println(); 
delay(1000);
}
