#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2);

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Hello");
  delay(200);
}

void loop() {
  if(Serial.available()>0)
  switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'r':
      RecieveMessage();
      break;
  }
  if(mySerial.available()>0)
    Serial.write(mySerial.read());
}

void SendMessage()
{
  Serial.println("Sending SMS");
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGF=\"+918743053988\"\r");
  delay(1000);
  mySerial.println("I am SMS from GSM Module");
  delay(200);
  mySerial.println((char)26);
  delay(1000);
}

void RecieveMessage()
{
  Serial.println("Recieving SMS");
  mySerial.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
}
