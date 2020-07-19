#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <SD.h>

SoftwareSerial mySerial(D1,D2);

const char* ssid = "ilham";
const char* password = "bismillah";
#define CS_PIN  D8;
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  if (!SD.begin(CS_PIN)) {
    return;
  }
  delay(10);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  server.begin();
  Serial.println("Server started");

  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {

  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

 
  int motor = 0;
  if (request.indexOf("/MOTOR=lambat") != -1) {
    motor = 55;
  } 
  if (request.indexOf("/MOTOR=sedang") != -1) {
    motor = 125;
  } 
  if (request.indexOf("/MOTOR=kencang") != -1) {
    motor = 200;
  }
  if (request.indexOf("/MOTOR=ngebut") != -1) {
    motor = 255;
  }

  if(s.available()>0)
  {
    mySerial.write(motor);
    }
  
 
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 
  if(motor == 0) {
    client.print(" Welcome ");  
  }
  if(motor == 55) {
    client.print(" Motor dalam kecepatan lambat / 55 ");  
  }
  if(motor == 125) {
    client.print(" Motor dalam kecepatan sedang / 125 ");  
  }
  if(motor == 200) {
    client.print(" Motor dalam kecepatan kencang / 200 ");  
  }
  if(motor == 255) {
    client.print(" Motor dalam kecepatan ngebut / 255 ");  
  }
  
  client.println("<br><br>");
  client.println("Click <a href=\"/MOTOR=lambat\">here</a> Motor dalam kecepatan lambat / 55<br>");
  client.println("Click <a href=\"/MOTOR=sedang\">here</a> Motor dalam kecepatan sedang / 125<br>");
  client.println("Click <a href=\"/MOTOR=kencang\">here</a> Motor dalam kecepatan kencang / 200<br>");
  client.println("Click <a href=\"/MOTOR=ngebut\">here</a> Motor dalam kecepatan ngebut / 255<br>");
  client.println("</html>");

  File dataFile = SD.open("motor.txt", FILE_WRITE);
  if (dataFile) {
      dataFile.print(motor);
      dataFile.close();
  else {
    Serial.println("");
  }
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
