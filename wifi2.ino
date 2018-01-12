#include <ESP8266WiFi.h>


#define LDR   A0

const char* ssid = "Satlan_Logistyka";//type your ssid
const char* password = "s@tl@N_22112017";//type your password
 
int ledPin = 2; // inside LED
int ledB = 12; // blue Led
int ledG = 13; // green Led
int ledR = 15; // red Led
int button = 4; // button
WiFiServer server(80);//Service Port
 
void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(LDR, INPUT);
  pinMode(button, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  pinMode(ledB, OUTPUT);
  digitalWrite(ledB, LOW);
  
    pinMode(ledG, OUTPUT);
  digitalWrite(ledG, LOW);

    pinMode(ledR, OUTPUT);
  digitalWrite(ledR, LOW);
   
  // Connect to WiFi network
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
   
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
   
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
   
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
   
  // Match the request
 
  int value = LOW;
  int valueR = LOW;
  int valueG = LOW;
  int valueB = LOW;
  if (request.indexOf("/LED=ON_LEDR=ON_LEDG=OFF_LEDB=OFF") != -1) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledR, HIGH);
    digitalWrite(ledG, LOW);
    digitalWrite(ledB, LOW);
    value = HIGH;
    valueR = HIGH;
    valueG = LOW;
    valueB = LOW;
  } 
  if (request.indexOf("/LED=OFF_LEDR=OFF_LEDG=OFF_LEDB=OFF") != -1){
    digitalWrite(ledPin, LOW);
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, LOW);
    digitalWrite(ledB, LOW);
    value = LOW;
    valueR = LOW;
    valueG = LOW;
    valueB = LOW;
  }
  if (request.indexOf("/LED=OFF_LEDR=OFF_LEDG=OFF_LEDB=ON") != -1){
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, LOW);
    digitalWrite(ledB, HIGH);
    value = LOW;
    valueR = LOW;
    valueG = LOW;
    valueB = HIGH;
  }
   if (request.indexOf("/LED=OFF_LEDR=OFF_LEDG=ON_LEDB=OFF") != -1){
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, HIGH);
    digitalWrite(ledB, LOW);
    value = LOW;
    valueR = LOW;
    valueG = HIGH;
    valueB = LOW;
  }
 
  //Set ledPin according to the request
  //digitalWrite(ledPin, value);
   
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
   
  client.print("Led pin is now: ");
  float d=67.45;
  if(value == HIGH) {
    client.print(d);  
  } else {
    client.print("Off");
  }
  client.println("<br>");
  client.print("Button is: ");
  client.print(digitalRead(button));

  client.println("<br>");
  client.print("LDR =  ");
  client.print(analogRead(LDR)); 

  
  client.println("<br><br>");
  client.println("RED<br>");
  client.println("Click <a href=\"/LED=ON_LEDR=ON_LEDG=OFF_LEDB=OFF\">here</a> turn the LED on pin 15 ON<br>");
  client.println("<br>");
  client.println("BLUE<br>");
  client.println("Click <a href=\"/LED=OFF_LEDR=OFF_LEDG=OFF_LEDB=ON\">here</a> turn the LED on pin 12 ON<br>");
  client.println("<br>");
  client.println("GREEN<br>");
  client.println("Click <a href=\"/LED=OFF_LEDR=OFF_LEDG=ON_LEDB=OFF\">here</a> turn the LED on pin 13 ON<br>");
  client.println("<br>");
  client.println("OFF ALL LED<br>");
    client.println("Click <a href=\"/LED=OFF_LEDR=OFF_LEDG=OFF_LEDB=OFF\">here</a> turn off all the LED<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
