
#include "more4iot.h"
#include "secrets.h"

#include "WiFi.h"

#define TIME_TO_SEND 10000
#define HOST "192.168.0.186"
#define PORT 1883
#define UUID "deviceXX"

char ssid[] = WIFI_SSID;
char password[] = WIFI_PASSWORD;
char uuid[] = UUID;
int port = PORT;
char host[] = HOST;

WiFiClient espClient;
More4iotMqtt md(espClient);

void setup()
{
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

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
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  md.connect(host, port);
}

void loop()
{
  delay(TIME_TO_SEND);

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting to AP ...");
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    return;
  }

  if(!md.connected()){
    Serial.println("disconnected...");
    md.connect(host, port);
  }

  md.newDataObject(uuid, 4, 1.0, -2.0);
  md.addField("temperature", 25);
  md.send();

  Serial.println("Sending data...");
}
