#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>

/* Set these to your desired credentials. */
const char *ssid = "PhaDungSat";
const char *password = "25072509";

int a,b;
float t;
char c;
String currentLine;

WiFiServer server(80);  
       
void setup()
  {
    Serial.begin(115200);
    delay(10);
               
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password); 
    
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
         
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());   
   
    server.begin();       
  }

void request()
  {
    if (c == '\n')
      {
        if (currentLine.length() == 0)
          {
            ;
          }
        else
          {
            currentLine = "";
          }
      }
    else if (c != '\r') 
      {
        currentLine += c;      
      }
  }


void loop()
  {  
    WiFiClient client = server.available();    
    if (client)
      {   
        Serial.println("Beta Client.");
        currentLine = "";   
                   
        while (client.connected()) 
          {    
            if (client.available()) 
              {                   
                c = client.read();                 
                Serial.write(c);  
                request();
        
                if (currentLine.endsWith("/1")) 
                  {
                    Serial.println(" 1 SECOND ");
                  }
                else if(currentLine.endsWith("/2")) 
                  {
                    Serial.println(" 2 SECOND ");
                  }
                else if (currentLine.endsWith("/3")) 
                  {
                    Serial.println(" 3 SECOND ");
                  }
              }
          } 
      }
  }

 
