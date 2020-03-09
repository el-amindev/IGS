/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>

const char* ssid = "IGS";
const char* password = "12345678";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

boolean waternow=false;

void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(2, OUTPUT);

 
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  
  // Start the server
  server.begin();
  Serial.println("Server Started");

  // Print the IP address
  Serial.write(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("New Client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  client.flush();
  
  
  int val;
  
  if (req.indexOf("manu/ON") != -1){
  waternow=true;}
  else if (req.indexOf("manu/OFF") != -1){
   waternow=false;}
    
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  
  
  client.flush();

 
  delay(1);
  Serial.println("Client Disonnected");
  if (waternow==true){ digitalWrite(2, HIGH);
  delay (30000);
  waternow=false;}
  else{digitalWrite(2, LOW);}

  // The client will actually be disconnected 
  // when the function returns and 'client' object is destroyed
}
