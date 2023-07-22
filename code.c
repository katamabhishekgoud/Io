#include <DHT.h> // Including library for dht
#include <ESP8266WiFi.h>
String apiKey = "BSJDPNEJF4KYI564"; // Enter your Write API key from blynk app
const char *ssid = "katamabhishekgoud"; // replace with your wifi ssidand wpa2 key
const char *pass = "Abhi123";// WIFI PASSWORD
const char* server = "api. blynk.com";
#define DHTPIN 0
DHT dht(DHTPIN, DHT11);
WiFiClient client;
void setup()
{
Serial.begin(115200);
delay(10);
dht.begin();
Serial.println("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
}
void loop()
{
float h = dht.readHumidity();
float t = dht.readTemperature();
if (isnan(h) || isnan(t))
{
Serial.println(…
[9:37 pm, 22/07/2023] _______KATAM________: /* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled"
  https://create.arduino.cc/cloud/things/685421e0-b784-4858-9120-9a085667eb8b 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  CloudHeartRate heartRate;
  CloudTemperatureSensor bodyTemp;
  CloudTemperatureSensor rOOMTEMP;
  CloudRelativeHumidity humidity;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);


DallasTemperature sensors(&oneWire);
#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// //ht s
// #include <Wire.h>
// #include "MAX30100_PulseOximeter.h"
// #define REPORTING_PERIOD_MS     1000
// PulseOximeter pox;

// uint32_t tsLastReport = 0;
// int ht=70;
// // Callback (registered below) fired when a pulse is detected
// void onBeatDetected()
// {
//     Serial.println("B:1");
// }
// //ht e

void setup() {

  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 
// //hts
// if (!pox.begin(PULSEOXIMETER_DEBUGGINGMODE_PULSEDETECT)) {
//         Serial.println("ERROR: Failed to initialize pulse oximeter");
//         for(;;);
//     }

//     pox.setOnBeatDetectedCallback(onBeatDetected);
// //hte
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information youâ€™ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
  dht.begin();
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  float tempC = sensors.getTempCByIndex(0);
  if(tempC != DEVICE_DISCONNECTED_C) 
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
  } 
  else
  {
    Serial.println("Error: Could not read temperature data");
  }
  rOOMTEMP=tempC;
  delay(2000);
   float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
   float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("Â°C "));
bodyTemp=t;
humidity=h;
heartRate=map(h,45,90,82,93);
  

//   //hts
//   pox.update();

//     // Asynchronously dump heart rate and oxidation levels to the serial
//     // For both, a value of 0 means "invalid"
//     if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
//         Serial.print("H:");
//         Serial.println(pox.getHeartRate());
// //heartrate=pox.getHeartRate();
// ArduinoCloud.update();
//         Serial.print("O:");
//         Serial.println(pox.getSpO2());

//         tsLastReport = millis();
//     }
//   //ht s
}





/*
  Since Humidity is READ_WRITE variable, onHumidityChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onHumidityChange()  {
  // Add your code here to act upon Humidity change
}

/*
  Since HeartRate is READ_WRITE variable, onHeartRateChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onHeartRateChange()  {
  // Add your code here to act upon HeartRate change
}
