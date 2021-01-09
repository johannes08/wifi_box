#include <SPI.h>
#include <WiFiNINA.h>

#define led 13

char ssid[] = "Internet27";
char pass[] = "97975411637015086953";
int keyIndex = 0;

int status = WL_IDLE_STATUS;
WiFiServer server(80);

String readString;

// Send status to server
// Set Wifi Data dynamically


void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  server.begin();

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {
  WiFiClient client = server.available();
  if (client)
  {
    Serial.println("new client");

    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        if (readString.length() < 100)
        {
          readString += c;
          Serial.write(c);
          
          if (c == '\n') {
            client.println("<a href=\"/?1\"\">Turn On Light</a>");
            client.println("<br />");
            client.println("<br />");
            client.println("<a href=\"/?0\"\">Turn Off Light</a><br />");     

            delay(1);
            
            if(readString.indexOf("?1") > 0)
            {
              digitalWrite(led, HIGH);
              delay(1);
            }
            else{
              if(readString.indexOf("?0") > 0)
              {
                digitalWrite(led, LOW);    
                delay(1);
              }
            }           
            readString="";

            delay(1);
            client.stop();
            Serial.println("client disonnected");
          }
        }
      }
    }
  }
}
