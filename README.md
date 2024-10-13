# Weather-Station
This a weather station which can be mounted outside to give weather data.

# Things Needed:

<pre>To make this project, you need:</pre>
**Hardware:**
<pre>1x Arduino UNO or NANO 
1x ESP8266-01 WiFi Module
2x Photoresistors
2x 10KΩ Resistors
2x Soil Sensors (Probe and MH-Sensor Series board)
1x Rain Sensor (MH-Sensor Series board and Detection Module)
1x DHT11 Temperature and Humidity Sensor
1x MQ-135 Gas Sensor</pre>
**Software:**
<pre>1) Thingspeak Account
2) Arduino IDE
3) MIT App Inventor 2 Account</pre>

*You will also need a Wifi Router*

____________________________________________________________________________________

# Changes to be made in files:

<pre>Before uploading the code to the Arduino, replace:
  Line 18) Your Channel's Write API key
  Line 19) Your SSID
  Line 20) Your WiFi Password
</pre>
<pre>To get the API key, create a new thingspeak channel with the following data:
Field 1: Temperature
Field 2: Humidity
Field 3: Plant 1 Soil Water Content
Field 4: Plant 2 Soil Water Content
Field 5: Rainfall
Field 6: Gas Levels
Field 7: Light Intensity - 1
Field 8: Light Intensity - 2

Then you can copy the write API key.
</pre>

<pre>Also, change some parameters in the .aia file:
1) Replace the read API key with your read API key.
2) Replace the channel number with your channel number as well.
</pre>
_________________________________________________________________________________________

# Hardware Connections:

<pre>DHT11:
VCC: 5V
GND: GND
Data: D2
</pre>

<pre>MQ-135:
VCC: 5V
GND: GND
Digital OUT: D4
Analog OUT: A3
</pre>

<pre>Soil Water Sensor 1:
VCC: 5V
GND: GND
Digital OUT: D12
Analog OUT: A5
</pre>

<pre>Soil Water Sensor 2:
VCC: 5V
GND: GND
Digital OUT: D7
Analog OUT: A4
</pre>

<pre>Rain Sensor:
VCC: 5V
GND: GND
Digital OUT: D2
Analog OUT: A2
</pre>

<pre>Photo Resistor 1:
PIN 1: VCC
Pin 2: A0
</pre>

<pre>Photo Resistor 2:
PIN 1: VCC
Pin 2: A1
</pre>

<pre>Resistor 1:
PIN 1: GND
PIN 2: First Photo Resistor's Pin 2
</pre>

<pre>Resistor 2:
PIN 1: GND
PIN 2: Second Photo Resistor's Pin 2
</pre>

<pre>Buzzer:
GND: GND
VCC: D13
</pre>

<pre>ESP8266-01
VCC: 3.3V
GND: GND
EN: 3.3V
TX: 6
RX: 5
Reset: UNUSED
IO1: UNUSED
IO2: UNUSED
</pre>

_________________________________________________________________________________

# Start and Run it:

<pre> First, upload the edited Arduino Code. For the first time, you can see the Serial Monitor. Normally, it will show messages such as:
"Wifi Connected"
"Wifi Got IP"
Also, note that it is normal for the buzzer to beep during startup. In every ~20 Seconds, it will send a reading to the Thingspeak Server. 
You should be able to see the reading on the Channel. If this works, then you can use a external adapter with a rating of either '9V 1.2A' or '12V 1.2A'.
To use the Mobile app, open the https://appinventor.mit.edu/ site, open your project, click on 'build', then on '.apk'. After Compiling, you will get a QR code.
Scan this QR code on your mobile to download the app, you can use the Auto-Update feature. This will get you the values in the table.
</pre>
