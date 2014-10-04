tinyduino-wifi-helloworld
=========================

example IoT project for developers new to wifi driven hardware 

![knoll](http://f.cl.ly/items/202F2h1I1w183v0i3H0W/photocell-tinyduino.jpg)

## Ok, whut.
This is just a quick project showing how simple it is to get up and running with the latest hotness - Internet of Thingy-ma-jiggers.

When all assembled and placed in a mailbox, it'll connect via wifi to both email and sms you when you get mail!

## I do not understand how.
In this example, I'm using an Arduino microprocessor teamed with a light sensor and a wifi module. A battery powers the Arduino, which constantly keeps track of how much light is in the mailbox. When the USPS dudette/dude opens the little back door to put your mail and parcels in, light streams into the mailbox. This trips the device, which will then connect to wifi and send the email and sms to you.

If you do not have one of those door opening mailboxes, you can program it the opposite way - put it in your mailbox so that the sensor gathers light from the mail slot, and when envelopes are pushed through it blocks the light momentarily. Effectively that will be the trigger.

Yep, this only works in daylight, but it's pretty cool anyway. YMMV with wifi strength if your mailbox is made of metal.

## Disclaimer
**This example is presented as educational only.**

Postal companies might not be too pleased about spotting a mysterious device in a mailbox. They won't always assume it's a perfectly harmless Internet of Thingy-ma-flippers contraption full of awesome. **I am not condoning breaking the law with this project. Make sure you're familar with mail/mailbox tampering laws in your country**. The U.S., for example, has a helpful PDF on mail security you can [view here](https://www.hsdl.org/?view&did=34409). Spoiler alert: it has serious people holding guns on the front cover. [This poster is also pretty amazing](https://about.usps.com/securing-the-mail/mailtampering.htm).

Long story short - don't scare the willies out of your friendly neighbourhood post deliverer. Nobody wants the SWAT outside their house.

## Shopping list
+ [TinyCircuits Processor board](https://tiny-circuits.com/tinyduino-processor-board.html)
+ [TinyCircuits Wifi module](https://tiny-circuits.com/tiny-shield-wifi.html)
+ [TinyCurcuits Proto module](https://tiny-circuits.com/tiny-shield-proto-board-2.html) (any will do)
+ [TinyCircuits USB programmer module](https://tiny-circuits.com/tiny-shield-usb-and-icp.html) (not pictured)
+ micro USB cable
+ 10k Ohm resistor
+ [photocell resistor](http://www.adafruit.com/products/161)
+ [3.7v LiPo battery](http://www.adafruit.com/products/1578), at least 500mA 

Tools I assume you have already:
+ [LiPo charger](http://www.adafruit.com/products/1304)
+ soldering iron
+ solder
+ good eyes (my eyes are terrible for close-up work like soldering, but I still manage okay)

## Assembly
(todo)

## Upload sketch, set up server
(todo)

