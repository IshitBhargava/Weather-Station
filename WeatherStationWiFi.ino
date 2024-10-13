#include <SoftwareSerial.h>
#include <dht.h>

#define rainAPin1 A4
#define rainDPin1 12
#define rainAPin2 A5
#define rainDPin2 7
#define rainAPin3 A2
#define rainDPin3 3
#define gasAPin A3
#define gasDPin 4
#define DHTpin 2
#define TX 6
#define RX 5
#define LDR1 A0
#define LDR2 A1
#define Buzz 13
String key = "Your Channel's Write API key";
String ssid = "Your WiFi Name";
String pass = "Your Password";

SoftwareSerial esp8266(TX,RX);
dht DHT;


void setup() {
  Serial.begin(9600);
  esp8266.begin(9600);
  pinMode(rainAPin1, INPUT);
  pinMode(rainDPin1, INPUT);
  pinMode(rainAPin2, INPUT);
  pinMode(rainDPin2, INPUT);
  pinMode(rainAPin3, INPUT);
  pinMode(rainDPin3, INPUT);
  pinMode(gasAPin, INPUT);
  pinMode(gasDPin, INPUT);
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);
  pinMode(DHTpin, INPUT);
  pinMode(Buzz, OUTPUT);
  
  digitalWrite(Buzz, HIGH);

  sendAT("AT+RST\r\n",2000);
  sendAT("AT\r\n",1000);
  sendAT("AT+CWMODE=1\r\n",1000);
  sendAT("AT+CWJAP=\""+ssid+"\",\""+pass+"\"\r\n",1000);
  sendAT("AT+CIFSR\r\n",1000);
  sendAT("AT+CIPMUX=0\r\n",1000);

  digitalWrite(Buzz, LOW);
}

void loop() {
  int rain1valu = analogRead(rainAPin1);
  int rain2valu = analogRead(rainAPin2);
  int rain3valu = analogRead(rainAPin3);
  int gasval = analogRead(gasAPin);
  int l2 = analogRead(LDR1);
  int l1 = analogRead(LDR2);

  int dht_noUse = DHT.read11(DHTpin);

  int temp = DHT.temperature;
  int humid = DHT.humidity;

  bool rain1Dval = digitalRead(rainDPin1);
  bool rain2Dval = digitalRead(rainDPin2);
  bool rain3Dval = digitalRead(rainDPin3);
  bool gasDval = digitalRead(gasDPin);

  int rain1val = map(rain1valu,0,1023,1023,0);
  int rain2val = map(rain2valu,0,1023,1023,0);
  int rain3val = map(rain3valu,0,1023,1023,0);

  Serial.print("Rain1 Analog: "); Serial.print(rain1val); Serial.print("|");
  Serial.print("Rain2 Analog: "); Serial.print(rain2val); Serial.print("|");
  Serial.print("Rain3 Analog: "); Serial.print(rain3val); Serial.print("|");
  Serial.print("Gas Analog: "); Serial.print(gasval); Serial.print("|");
  Serial.print("LDR2: "); Serial.print(l2); Serial.print("|");
  Serial.print("LDR1: "); Serial.print(l1); Serial.print("|");
  Serial.print("Temp: "); Serial.print(temp); Serial.print("|");
  Serial.print("Humidity: "); Serial.print(humid); Serial.print("|");
  Serial.print("Rain1 Digital: "); Serial.print(rain1Dval); Serial.print("|");
  Serial.print("Rain2 Digital: "); Serial.print(rain2Dval); Serial.print("|");
  Serial.print("Rain3 Digital: "); Serial.print(rain3Dval); Serial.print("|");
  Serial.print("Gas Digital: "); Serial.print(gasDval); Serial.println();  // Use println to end the line and start a new one
  String rain1Str = String(rain1val);
  String rain2Str = String(rain2val);
  String rain3Str = String(rain3val);
  String gasStr = String(gasval);
  String l2Str = String(l2);
  String l1Str = String(l1);
  String tempStr = String(temp);
  String humidStr = String(humid);
  String rain1DStr = String(rain1Dval);
  String rain2DStr = String(rain2Dval);
  String rain3DStr = String(rain3Dval);
  String gasDStr = String(gasDval);

  updateTS(tempStr,humidStr,rain1Str,rain2Str,rain3Str,gasStr,l1Str,l2Str);
  delay(13000);
}


String sendAT(String command, const int timeout){
  String response = "";                      // Variable to store ESP8266 response
  esp8266.print(command);                   // Sending the command to ESP8266
  long int time = millis();                // Recording current time
  while ((time + timeout) > millis())    // Waiting for response within timeout
  {
    while (esp8266.available())          // Checking if ESP8266 data available
    {
      char c = esp8266.read();          // Reading character from ESP8266
      response += c;                   // Appending character to response string
    }
  }
  Serial.print(response);           // Printing response to serial monitor
  return response;                  // Returning response string
}


void updateTS(String T, String H, String R, String G, String L, String B, String A, String C){
  Serial.println("");                                                     // Printing empty line
  sendAT("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n", 1000);      // Establishing TCP connection with ThingSpeak
  delay(2000);                                                            // Delay for stability
  String cmd = "GET /update?key="+key+"&field1="+T+"&field2="+H+"&field3="+R+"&field4="+G+"&field5="+L+"&field6="+B+"&field7="+A+"&field8="+C+"\r\n";  // Building GET request URL with temperature and humidity data
  String cmdlen = String(cmd.length());                                   // Calculating command length
  sendAT("AT+CIPSEND=" + cmdlen + "\r\n", 2000);                          // Sending command length to ESP8266
  esp8266.print(cmd);                                                     // Sending GET request to ThingSpeak
  Serial.println(cmd);                                                     // Printing empty line
  sendAT("AT+CIPCLOSE\r\n", 2000);                                        // Closing TCP connection
  Serial.println("Sent AT");                                              // Printing message                                                  
}
