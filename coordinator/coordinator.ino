/**
 * @brief final code for coordinator
 */
#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

WiFiClient client;

String thingSpeakAddress= "http://api.thingspeak.com/update?";
String writeAPIKey;
String tsfield1Name;
String request_string;

HTTPClient http;

char arr[20];

void setup()
{
  Serial.begin(9600);
   WiFi.begin("WiFi-NAME","PASSWORD");// Enter network BSSID and PASSWORD
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    //Serial.print("..");

  }
 // Serial.println("CONNECTED");

}


void loop()
{
/**
 * @brief receiving data from router
 */
String FireS,TempS,HumS,SmokS;
if (Serial.available() > 0) 
{
  arr[0]= Serial.read();
  arr[1]= Serial.read();
  arr[2]= Serial.read();
  arr[3]= Serial.read();
  arr[4]= Serial.read();
  arr[5]= Serial.read();
  arr[6]= Serial.read();
  arr[7]= Serial.read();
//String valueas = String(arr[0])+String(arr[1])+String(arr[2])+String(arr[3])+String(arr[4])+String(arr[5])+String(arr[6])+String(arr[7]);
//long value = valueas.toInt();
//Serial.print(valueas);

/**
 * @brief breaking down data
 */
FireS = String(arr[0]);
TempS= String(arr[1])+String(arr[2]);
HumS = String(arr[3])+String(arr[4]);
SmokS = String(arr[5])+String(arr[6])+String(arr[7]);


/**
 * @brief converting sensor data to integer 
 */
int FireValue = FireS.toInt();
int TemperatureValue = TempS.toInt();
int HumidityValue = HumS.toInt();
int SmokeValue = SmokS.toInt();

    /**
     * @brief Uploading Temperature data to thinkspeak
     */
    if (client.connect("api.thingspeak.com",80)) 
    {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "LO4QV232T0ZHKNM9";
      request_string += "&";
      request_string += "field1";
      request_string += "=";
      request_string += TemperatureValue;
      http.begin(request_string);
      http.GET();
      http.end();

    }
    delay(500);

    /**
     * @brief uploading Humidity data to thinkspeak
     */

    if (client.connect("api.thingspeak.com",80)) 
    {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "LO4QV232T0ZHKNM9";
      request_string += "&";
      request_string += "field2";
      request_string += "=";
      request_string += HumidityValue;
      http.begin(request_string);
      http.GET();
      http.end();

    }
    delay(500);
    
    if (client.connect("api.thingspeak.com",80)) 
    {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "LO4QV232T0ZHKNM9";
      request_string += "&";
      request_string += "field3";
      request_string += "=";
      request_string += FireValue;
      http.begin(request_string);
      http.GET();
      http.end();

    }
    delay(500);

    /**
     * @brief uploading Humidity data to thinkspeak
     */
    if (client.connect("api.thingspeak.com",80)) 
    {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "LO4QV232T0ZHKNM9";
      request_string += "&";
      request_string += "field4";
      request_string += "=";
      request_string += SmokeValue;
      http.begin(request_string);
      http.GET();
      http.end();

    }
    delay(500);

}


delay(10000);
}
