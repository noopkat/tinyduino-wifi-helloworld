/* 
*  Tiny WiFi light sensor with a Tinyduino + CC3000 wifi module + photocell resistor
*  Original sketch written by Marco Schwartz for Open Home Automation
*  https://github.com/openhomeautomation/tiny-wifi-temperature/blob/master/tiny_weather_station/tiny_weather_station.ino
*  Further hacked by @noopkat for use with a light sensor, and a hard-set tokenised GET based on certain conditions, instead of constant reporting
*/

// Include required libraries
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
//#include "utility/debug.h"
#include<stdlib.h>

// Define CC3000 chip pins
#define ADAFRUIT_CC3000_IRQ   2
#define ADAFRUIT_CC3000_VBAT  A3
#define ADAFRUIT_CC3000_CS    8

// WiFi network
#define WLAN_SSID       ""        // cannot be longer than 32 characters
#define WLAN_PASS       ""
#define WLAN_SECURITY   WLAN_SEC_WPA2 // This can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2

// Create CC3000 instance
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIV2);
                                         
// Local server IP, port, and repository (change with your settings !)
uint32_t ip = cc3000.IP2U32(172,0,0,1);
int port = 80;
String repository = "/";

// vars
int sensorPin = 0;
pinMode(sensorPin, INPUT);
bool bright = false;
String token = "558822";

void setup(void)
{
 
  Serial.begin(115200);
    
  // Initialise the CC3000 module
  if (!cc3000.begin())
  {
    while(1);
  }
  
  // Connect to  WiFi network
  cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY);
  Serial.println("Connected to WiFi network!");
    
  // Check DHCP
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100);
  }  
  
  // this is the api call to your software running anywhere
  // token is just a little verification to prevent terrible friends just hitting your service to troll you with false positives
  String request = "POST " + repository + "?token=" + token + " HTTP/1.0";

}

void loop(void)
{
  bool sent = false;
  Serial.begin(9600);
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

  // if light source appears, set bright to true and send request
  if (sensorValue > 0 && bright == false) {
      // this will ensure request is sent only once
      bright = true;

    send_request(request);
    sent = true;
  } 

  // light source gone, go back to dark mode again
  if (sensorValue == 0 && bright == true) {
    bright = false;
  }
}

// Function to send a TCP request and get the result as a string
void send_request (String request) {
     
  // Connect    
  Serial.println("Starting connection to server...");
  Adafruit_CC3000_Client client = cc3000.connectTCP(ip, port);
  
  // Send request
  if (client.connected()) {
    client.println(request);      
    client.println(F(""));
    Serial.println("Connected & Data sent");
  } 
  else {
    Serial.println(F("Connection failed"));    
  }

  while (client.connected()) {
    while (client.available()) {

    // Read answer
    char c = client.read();
    }
  }
  Serial.println("Closing connection");
  Serial.println("");
  client.close();    
  Serial.println("Connection closed.");
}