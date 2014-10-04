tinyduino-wifi-helloworld
=========================

example IoT project for developers new to wifi driven hardware 

![knoll](http://f.cl.ly/items/202F2h1I1w183v0i3H0W/photocell-tinyduino.jpg)

## Ok, whut.
This is just a quick project showing how simple it is to get up and running with the latest hotness - Internet of Thingies.

When all assembled and placed in a mailbox, it'll connect via wifi to both email and sms you when you get mail!

## I do not understand how.
In this example, I'm using an Arduino microprocessor teamed with a light sensor and a wifi module. A battery powers the Arduino, which constantly keeps track of how much light is in the mailbox. When the USPS dudette/dude opens the little back door to put your mail and parcels in, light streams into the mailbox. This trips the device, which will then connect to wifi and send the email and sms to you.

If you do not have one of those door opening mailboxes, you can program it the opposite way - put it in your mailbox so that the sensor gathers light from the mail slot, and when envelopes are pushed through it blocks the light momentarily. Effectively that will be the trigger.

Yep, this only works in daylight, but it's pretty cool anyway.

## Shopping list
(todo)

## Assembly
(todo)

## Upload sketch, set up server
(todo)