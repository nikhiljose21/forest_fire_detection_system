
/**
 * @brief final code for node circuit of major project 
 */

#include <dht.h>
#include <SoftwareSerial.h>

/**
 * @brief serial pins for SIM800
 */
 SoftwareSerial sim800l(4, 5); // RX,TX for Arduino and for the module it's TXD RXD, they should be inverted

/**
 * @brief declaring macros
 */
#define MQ2Sensor (A1)
#define FlameSensor (7)
#define HumiditySensor A2
#define TemperatureSensor A3
#define DHTTYPE DHT11



/**
 * @brief initialising DHT sensor
 */
dht DHT;

/**
 * @brief array to transmitt data 
 */
char DataArray[10];

 /**
 * @brief setting pinmode, baud rate and sensor warm up time
 */

void setup() 
{
/**
 * @brief Baud rate set as 9600
 */
Serial.begin(9600);
sim800l.begin(9600);   //Module baude rate, this is on max, it depends on the version

/**
 * @brief sensor warmup time
 */
delay(20000);

/**
 * @brief Setting pinMode
 */
pinMode(MQ2Sensor, INPUT);
pinMode(FlameSensor, INPUT);
//pinMode(HumiditySensor, INPUT);
pinMode(TemperatureSensor, INPUT);
}

void loop() 
{

/**
 * @brief reading values from sensor pins
 */
int FlameValue = 0;
int MQ2Value = analogRead(MQ2Sensor);
DHT.read11(HumiditySensor);
float TemperatureValue = analogRead(TemperatureSensor);
FlameValue = digitalRead(FlameSensor);


/**
 * @brief converting temperature value to degree celsius
 */

 float mv = (TemperatureValue/1024)*5000;
 float cell =mv/20;

 int TempInCelsius = cell;


/**
 * @brief storing humidity value in 
 */
 int HumidityValue = DHT.humidity;


/**
 * @brief transmission sequence
 */

 //values in string
 String TemperatureInString = String(TempInCelsius);
 String HumidityInString = String(HumidityValue);
 String SmokeInString = String(MQ2Value);
 String FlameInString = String(FlameValue);


 //Serial.println("T");
 //Serial.println(TemperatureInString);
 //Serial.println("H");
 //Serial.println(HumidityInString);
 //Serial.println("F");
 //Serial.println(FlameInString);
 //Serial.println("G");
 //Serial.println(SmokeInString);

//Joining all data
String Data = FlameInString + TemperatureInString + HumidityInString + SmokeInString ;

/**
 * @brief sending data
 */
Serial.print(Data);



/**
 * @brief alerting in case of a fire
 */
if((FlameValue == HIGH)&&(MQ2Value>400)&&(TemperatureValue>50))
{
  /** 
   * @brief sending SMS
   */
   
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+91NUMBER\"\r");  //Your phone number don't forget to include your country code, example +212123456789"
  delay(500);
  sim800l.print("FIRE DETECTED AT COORDINATES");       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(500);
  sim800l.print((char)26);// (required according to the datasheet)
  delay(500);
  sim800l.println();
  delay(500);
}
/**
 * @brief Delay of 10 seconds before taking the next reading
 */
delay(10000);

}
