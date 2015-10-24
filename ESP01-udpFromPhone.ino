#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include<Wire.h>

/* ----- Set AP ---------- */
const char *ssid = "ESP8266DronesAP";
const char *password = "inwbun.123";
/* ---- End set AP --------*/




//_____________Set UDP variables_____________//
char packetBuffer[1500]; //buffer to hold incoming packet

//float vaules = 0;
//float vaulesR = 0;
//float vaulesL = 0;

int ch1_Eleveltor, ch2_roll, ch3_power, ch4_yaw;
String b,ct;

unsigned long timeStar, timeEnd;
boolean readStar = true;
boolean readStop = false;
boolean testRate = true;

byte byteSend[4];

//_____________End set UDP Variables_________//





//set var multitask
unsigned long times, time2, timesC1, timesC2, timetest1, timetest2;
//end set var multitask


WiFiUDP Udp;

void setup() {
  // put your setup code here, to run once:
  // Open Wifi
  delay(1000);
  WiFi.softAP(ssid, password);
  Udp.begin(80);
  //End open wifi
  Wire.pins(0, 2);// Wire.begin(int sda, int scl)
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  readUDP();

}


// function get data from UPD
void readUDP() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  //
  if (packetSize == 0 ) { // if no data

    unsigned long ts = timeStar;
    timeEnd = millis();
    if ((timeEnd - ts) > 500) {
      // doing when lose data from UDP becuse 500ms


      //readStar = true;
      // readStop = false;
    }

  }
  //

  if (packetSize > 0 )  // if have data
  {

    // analogWrite(16,0);
    // if (readStar == true) {
    timeStar = millis();
    // readStar = false;
    // readStop = true;
    // }
    timeEnd = millis();
    /*
        timeEnd = millis();
        counts++;
      */
    /* Serial.print("Received packet of size ");
     Serial.println(packetSize);
     Serial.print("From ");
     IPAddress remoteIp = Udp.remoteIP();
     Serial.print(remoteIp);
     Serial.print(", port ");
     Serial.println(Udp.remotePort());
    */
    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;

      // Serial.print("Contents:");
      //Serial.println(packetBuffer);
      b = packetBuffer;
      // Serial.println(b);
      //get data ch1_Eleveltor,ch2_roll,ch3_power,ch4_yaw;
      //simple data send from Android    a255b180c50d99!
      /*ch1_Eleveltor = b.substring((b.indexOf('a') + 1), b.indexOf('b')).toInt();
      ch2_roll = b.substring((b.indexOf('b') + 1), b.indexOf('c')).toInt();
      ch3_power = b.substring((b.indexOf('c') + 1), b.indexOf('d')).toInt();
      ch4_yaw = b.substring((b.indexOf('d') + 1), b.indexOf('!')).toInt();
      
      byteSend[0] = ch1_Eleveltor;
      byteSend[1] = ch2_roll;
      byteSend[2] = 0;
      byteSend[3] = ch4_yaw;
      */
      //ct = byteSend;
      //c.trim();
      //Serial.write( byteSend, 4); // send a byte with the value
      
      Serial.println(b);
    }
  }
 
}

// end function get data from UPD

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent(void)
{
  //Wire.write("hello "); // respond with message of 6 bytes
  Wire.write(byteSend,4);// respond with message of 4 bytes
  // as expected by master
}

