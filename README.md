# Clock7
__A 3D printed, illuminated, colored, connected, smart powered, 7 segmented clock__

This project was inspired by the design of the beautiful but discontinued [ClockONE by Twelve24](https://www.kickstarter.com/projects/twelve24/clockone-by-twelve24) kickstarter and more recently brought back to my memory by the [Huge Seven Segment Display made by engineerish](https://www.thingiverse.com/thing:2977443).

The goal of this project is to create a wall clock made out of 4 of these huge seven segment displays and connected somehow by two dots in the middle separating the hours from the minutes so the final things looks like the ClockONE.
The clock will be illuminated by a strip of WS2812B commonly named NeoPixels so that the 7seg displays can be controlled individually, and so he brightness and color of the light can be changed.

## First iteration of the project:
* Displaying the time as a 24h digital clock using the LED strip with pure and bright white light.
* The time will be fetched from an external API so the DST and time zone will be already taken care of.
* Using the 3D printed enclosure of the clock, an ESP8266 and a 5V 10A power supply (see below for the electrical requirements).

## Planned improvements to the clock:
* Add color and brightness shifting depending on time of the day.
* Add a companion weather station (also based on a ESP8266 platform) with a REST API to display temperature, humidity and atmospheric pressure as well as weather forecast from an external API using light animation on the clock.

## Electrical requirements
The rule of thumb for the WS2812B is that each LED with its driver can consume up to 60mA when set to white full brightness RGB(255, 255, 255).
The clock will be made of 4 7segs display, each having 7 segments (duh..!), made out of 4 LEDs. That's a total of 112 LEDs. If we count 4 LEDs for each dot that will be in the middle of the clock that's a grand total of (tadaaaa!) 120 LEDs. This is quite convenient since you can buy a 2 meters strip of WS2812B with 60 LEDS by meter from AliExpress for cheap.

Therefore, we have: 120LEDs * 60mA = 7.2A

Not all LEDs will be on at the same time and even if I'm not sure they will run at full brightness using a 10A 5V we can make sure we don't run out of power and the power adapter will only run at a fraction of its maximum output resulting in better efficiency.
