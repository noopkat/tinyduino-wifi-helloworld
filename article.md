# Using the Arduino platform to create your very own IoT devices
As a software developer, there's something magic about being able to say, "I made this myself!". Building hardware to integrate with software is no different. Sure, you can buy off the shelf IoT devices for your home and lifestyle, but there's much more fun in building your own. You'll learn a lot about how they work, and will take away a sense of pride and achievement.

This is just a quick project showing how simple it is to get up and running with building and programming your own Internet of Things devices.
When all assembled and placed in a mailbox, this contraption will connect via WiFi to both email and SMS you when you get mail!

In this example, I'm using an Arduino microprocessor teamed with a light sensor and a WiFi module. A battery powers the Arduino, which constantly keeps track of how much light is in the mailbox. When the postal delivery opens the little back door to put your mail and parcels in, light streams into the mailbox. This trips the device, which will then connect to WiFi and send the email and SMS to you.

If you do not have one of those door opening mailboxes, you can program it the opposite way - put it in your mailbox so that the sensor gathers light from the mail slot, and when envelopes are pushed through it blocks the light momentarily. Effectively that will be the trigger.

This only works in daylight, but it's pretty cool anyway. Your mileage may vary with WiFi strength if your mailbox is made of metal.

The full code is hosted on Github: https://github.com/noopkat/tinyduino-wifi-helloworld

**Warning**  - postal companies might not be too pleased about spotting a mysterious device in a mailbox. They won't always assume it's a perfectly harmless Internet of Things device. I am not condoning breaking the law with this project. Make sure you're familiar with mail/mailbox tampering laws in your country. Long story short - don't scare your friendly neighbourhood post deliverer. Nobody wants the police outside their house!

![knoll of parts](http://f.cl.ly/items/0U381w2C3u0u1W3R2x2G/mailbox-device-knoll.jpg)

## Shopping list
  + TinyCircuits Processor board
  + TinyCircuits WiFi module
  + TinyCurcuits Proto module (any will do)
  + TinyCircuits USB programmer module (not pictured)
  + micro USB cable
  + 10k Ohm resistor
  + photocell resistor
  + 3.7v LiPo battery, at least 500mA
  
**Tools I assume you have already:**
  + LiPo charger
  + soldering iron
  + solder

## Assembly
My favourite feature of the TinyCircuits system (other than the tiny size) is the way they easily click together to supply the technology you need.
First, we're going to click everything together as we need it. 

Take the processor board, and click the USB module to the top of it. Then, click the WiFi module to the top of the USB one. Lastly, click together the proto board to the very top of the stack. This will be the order of the stack when we develop it. It allows us to power the board without a battery via the computer, and we can also program it this way.

Next, remove the proto module from the top of the stack. Solder the resistor and photocell to it. The resistor goes from A0 to GND, and the photocell shares the A0, and the other end goes to VBATT. VBATT is a special pin that makes both the USB and battery power sources available to use. See the breadboard fritzing diagram below to assist you:

![fritzing breadboard](https://github.com/noopkat/tinyduino-wifi-helloworld/blob/master/fritzing/photocell-to-arduino.png)

See the following example for how it will look when complete. Note I have left the component arms rather long so that it's easier to see what's going on.

![photo of stack](http://f.cl.ly/items/1p3O0g3l021W1K410H2y/soldered-mailbox-device.jpg)

## Upload Arduino code
Click the proto module back onto your TinyCircuit stack. Plug a micro USB cable into the programming board, then connect to your computer. In the Arduino software, set the board to 'Arduino Pro Mini 3.3v w/ ATMega 328'. Open the sketch from the repo and click 'upload'. Select the correct USB device if prompted.

The main loop of the sketch is pretty simple, see the truncated code below:

```c++
uint32_t ip = cc3000.IP2U32(10,0,1,4);
int port = 8081;
String path = "/mailbox/token/";
String token = "558822";
String request = "GET " + path + token + " HTTP/1.0";

void loop(void)
{
  sensorValue = analogRead(sensorPin);
  // print to serial monitor for debugging purposes
  Serial.println(sensorValue);

  // if light source appears, set bright to true and send request
  // you may have the fiddle with this value to suit your light source
  if (sensorValue < 450 && bright == false) {
      // this will ensure request is sent only once
      bright = true;
      // send request to mailbox server
      send_request(request);
  } 

  // light source gone, go back to dark mode again
  if (sensorValue > 450 && bright == true) {
    bright = false;
  }
  
  delay(300);
}
```

You'll definitely need to play with the default light reading value set in the code above for best results with the physical place you're setting up your device in.

## Set up your server
I created a really simple NodeJS hapi server instance for dealing with the email and SMS. It is running on the local network the device is connected to via WiFi. The server simply waits for a GET request to the specified route, then verifies the request with a static token the Arduino will send as part of the request. This token should help stop your friends pranking you!

When the request is successful, the route handler will call some third party API's to send the notifications. I'm using Twilio for SMS, and Mailgun for the email.

A truncated sample of the code:

```javascript
var Hapi  = require('hapi');
var server = new Hapi.Server('10.0.1.4', 8081);
var passToken = '558822';

server.route({
    method: 'GET',
    path: '/mailbox/token/{token?}',
    handler: function (request, reply) {
      if (request.params.token && request.params.token === passToken) {
        // Twilio
        sendSMS();
        // MailGun
        sendEmail();
     // simple reply for testing manually
        reply('you\'ve got mail!');
      } else {
      // someone's being a prankster if missing/wrong token
        reply('why you gotta troll me, friend :(');
      }
    }
});
// Start the server
server.start();
```

Start the server in bash:

```
node index.js
```

## Test your device
While still plugged in to your computer, reset your device, and make sure your NodeJS server is running. To debug, watch both the Arduino app serial monitor's output, and your bash window. Play with the photo sensor, covering it up and then exposing it to light. You should start receiving emails and SMS's. 

Once verified, you can take the USB programming module out of your TinyCircuit stack completely, as we no longer need it. You'll see 2 terminals on the processor board. Solder a LiPo battery JST connector to these terminals in order to have this device run truly wire free and discreetly. Test again with the LiPo battery connected, then you're ready to use your finished device!

## Optional step
3D print a case for your new contraption, to make it look geek professional.