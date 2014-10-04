/* 
*  Tiny WiFi light sensor with a Tinyduino + CC3000 wifi module + photocell resistor
*  CC3000 lib written by Adafruit
*  sendRequest() method orginally written by Marco Schwartz for Open Home Automation
*  https://github.com/openhomeautomation/tiny-wifi-temperature/blob/master/tiny_weather_station/tiny_weather_station.ino
*  Further hacked by @noopkat for use with a light sensor, and a hard-set tokenised GET based on certain conditions, instead of constant reporting
*/

// Include required libraries
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include <stdlib.h>

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
                                         
// Local server IP, port, and repository (replace these with your own server setup)
uint32_t ip = cc3000.IP2U32(10,0,1,4);
int port = 8081;
String path = "/mailbox/token/";
String token = "558822";

// this is the api call (minus ip and port) to your software running anywhere
// token is just a little verification to prevent terrible friends just hitting your service to troll you with false positives
String request = "GET " + path + token + " HTTP/1.0";

int sensorPin = A0;
// set to dark to begin with
int sensorValue = 1023;
bool bright = false;


void setup(void)
{
  // Start serial
  Serial.begin(9600);
    
  // Initialise the CC3000 module
  if (!cc3000.begin())
  {
    while(1);
  }
}

void loop(void)
{
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

  // if light source appears, set bright to true and send request
  if (sensorValue < 450 && bright == false) {
      // this will ensure request is sent only once
      bright = true;
      // connect to WIFI
      connect_wifi();
      // hit up mailbox server
      send_request(request);
      // disconnect to save battery
      cc3000.disconnect();
  } 

  // light source gone, go back to dark mode again
  if (sensorValue > 450 && bright == true) {
    bright = false;
  }
  
  delay(300);
}

void connect_wifi() {
  // Connect to  WiFi network
  cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY);
  Serial.println("Connected to WiFi network!");
    
  // Check DHCP
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100);
  }  
}

// Function to send a TCP request and get the result as a string
void send_request(String request) {
     
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