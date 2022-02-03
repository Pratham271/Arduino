#include <ESP8266WiFi.h>
#include <Servo.h>
Servo myservo;

const char* ssid= "Rahul";
const char* password="hello@1234";
WiFiServer server(80);

const int rain=4;
const int ldr=A0;
int relay=D8;
int headlight=LOW;
int wiper=LOW;

void setup() {
// put your setup code here, to run once:
pinMode(rain,INPUT);
pinMode(ldr,INPUT);
Serial.begin(115200);
myservo.attach(D6);
Serial.println();
Serial.print("Connecting to: ");
Serial.println(ssid);
WiFi.begin(ssid,password);
while(WiFi.status() !=WL_CONNECTED){
 delay(500);
 Serial.print(".");
}
Serial.println();
Serial.println("WiFi Connected");
server.begin();
Serial.println("Server started");
Serial.println("Use this URL to connect:");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println("/");
}

void loop() {
// put your main code here, to run repeatedly:
WiFiClient client= server.available();
if(!client){
return;
}
Serial.println("New client");
while(!client.available()){
delay(1);
}
if(digitalRead(rain)==LOW){
myservo.write(60);
delay(1000);
myservo.write(-60);
wiper=HIGH;
}
else{
delay(1000);
wiper=LOW;
}
if(analogRead(ldr)>800){
digitalWrite(relay,HIGH);
delay(1000);
headlight=HIGH;
}
else{
digitalWrite(relay,LOW);
delay(1000);
headlight=LOW;
}

client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println();
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<h1> Smart Car </h1>");
client.println("Wiper status:");
if(wiper==HIGH){
client.print("On");
}
else{
client.print("Off");
}
client.println("<br><br>");
client.println("Headlight status:");
if(headlight==HIGH){
client.print("On");
}
else{
client.print("Off");
}
client.println("</html>");
delay(1);
Serial.println("Client disconnected");
Serial.println("");
}
