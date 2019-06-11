#include "FS.h"
#include <ESP8266WiFi.h>
#include <WString.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>    

WiFiServer server(80);

void config_gpio();
void config_wifi();
void query();

const char* ssid     = "SSID";     // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "PASSWORD"; // The password of the Wi-Fi network

const char* cmd_on  = "/on";
const char* cmd_off = "/off";

String header;

void setup()
{
  Serial.begin(115200); 
  Serial.println("Config begin");
  Serial.println("..GPIO");
  config_gpio();
  Serial.println("..wifi");  
  config_wifi();
  server.begin();
  Serial.println("Config end");
}

void loop() 
{
    query(); 
    delay(1000);
}

void config_gpio()
{
   pinMode(12, OUTPUT);
   pinMode(13, OUTPUT);

   digitalWrite(12, LOW);
   digitalWrite(13, LOW);
}

void config_wifi()
{

  IPAddress ip(192,168,0,11);
  IPAddress gateway(192,168,0,1);
  IPAddress subnet(255,255,255,0);   
  WiFi.config(ip, gateway, subnet);
  
  WiFi.begin(ssid,password);
  
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println('\n');
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void query()
{
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Got request...");
    String currentLine = "";
    while(client.connected()){
      if(client.available()){
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c=='\n'){
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length()==0){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET "+cmd_on) >= 0) {
              Serial.println("on");
              digitalWrite(12, HIGH);
              digitalWrite(13, HIGH);
            }else if (header.indexOf("GET "+cmd_off) >= 0) {
              Serial.println("off");
              digitalWrite(12, LOW);
              digitalWrite(13, LOW);
            }

            client.println("OK");
            client.println();
            break;
            
          }else{
            currentLine = "";
          }
        }else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;     // add it to the end of the currentLine
        }
      }
    }
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
