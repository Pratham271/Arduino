#include <ESP8266WiFi.h>
const char* ssid ="whokilledknightking"; 
const char* password = "Arya Stark"; 
const int speed_control = D8;
const int motpinl =D3; 
const int motpin2 = D6;
int value = LOW;
uint8_t speed_parameter = 255;
WiFiServer server(80);
void setup() {
Serial.begin (115200);
delay(10);
pinMode (motpinl, OUTPUT);
pinMode (motpin2, OUTPUT); pinMode (speed_control, OUTPUT);
digitalWrite (motpinl, LOW);
digitalWrite (motpin2, LOW);
// Connect to WiFi network
Serial.print("Connecting to ");
Serial.println (ssid);
WiFi.begin (ssid, password);
while (WiFi.status() !=WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println(""); 
Serial.println("WiFi connected");
// Start the server
server.begin();
Serial.println("Server started");
// Print the IP address Serial.print ("Use this URL to connect: ");
Serial.print ("http://");
Serial.print (WiFi.localIP());
Serial.println("/");

}
void loop() {

// Check it a client has connected 
WiFiClient client = server.available();
if (!client) {
return;
}
// Wait until the client sends some data 
Serial.println("new client");
while (!client.available()) {
  delay (1);
}
// Read the first line of the request 
String request = client.readStringUntil('\r'); 
Serial.println(request);
client.flush();
//Waits until all outgoing characters in buffer have been sent.
if (request.indexOf("/CLOCKWISE") != -1) 
{ digitalWrite (motpinl, LOW);
digitalWrite (motpin2, HIGH);
value=HIGH;
}
if (request.indexOf("/ANTICLOCKWISE") != -1) 
{ 
  digitalWrite (motpinl, HIGH); 
  digitalWrite (motpin2, LOW); 
  value=LOW;
}

if (request.indexOf("/SLOW") != -1) { 
  speed_parameter=speed_parameter-25; 
  analogWrite (speed_control, speed_parameter);
  Serial.println (speed_parameter);
}
if (request.indexOf("/FAST") != -1) {
  speed_parameter=speed_parameter+25;
  analogWrite (speed_control, speed_parameter);
  Serial.println (speed_parameter);
}
// Return the response
client.println ("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); // do not forget this one 
client.println("<!DOCTYPE HTML>"); 
client.println("<html>");
client.print ("Motor speed and direction: ");
if (value == HIGH) {
client.print("clockwise");
client.print (speed_parameter);
} 
else 
{
  client.print ("anticlockwise"); 
  client.print (speed_parameter);
}
client.println("<br><br>");
client.println("<a href=\"/CLOCKWISE\"\"><button>Clockwise </button></a>"); 
client.println("<a href=\"/ANTICLOCKWISE\"\"><button>Anticlockwine </button></a><br/>");
client.println("<br><br>");
client.println("<a href=\"/SLOW\"\"><button>slow </button></a>");
client.println("<a href=\"/FAST\"\"><button>fast </button></a><br />");
client.println("</html>");
delay (1);
Serial.println("Client disonnected");
Serial.println("");
}
