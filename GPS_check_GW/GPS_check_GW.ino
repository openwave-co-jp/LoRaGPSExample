#include <SPI.h>
#include <LoRa.h>
//#include <Console.h>
#include "ThingSpeak.h"
#include "YunClient.h"
YunClient client;

//RH_RF95 rf95;
//float frequency = 923.6;
unsigned long myChannelNumber = 000000;
const char * myWriteAPIKey = "XXXXXXXXXXXXXXXX";

void setup() {
  Bridge.begin(115200);
//  Console.begin();
//  while(!Console);
  ThingSpeak.begin(client);
//  Console.println("LoRa Receiver");
  
  if (!LoRa.begin(9236E5)) {
//    Console.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(9);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(6);
  LoRa.crc();
  LoRa.setTxPower(13);
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
//    Console.print("Received packet '");
//    Console.print("packetSize : ");
//    Console.println(packetSize);
    // read packet
    int i = 0;
    char message[256];
    while (LoRa.available() && i < 256) {
      message[i]=LoRa.read();
      i++;
    }
//    Console.print(message);

    
    char *tp;
    int cnt=0;
    /* ,を区切りに文字列を抽出 */   
    tp = strtok( message, "," );
    char latSign,longSign,*stopstring;
    double utc;
    float latVal,longVal,altiVal;
    
    while ( tp != NULL ) {
      cnt++;
      if(cnt==2){
//        Console.print("UTC:");
//        utc=atof(tp);
//        Console.println(utc);
        
      }
      if(cnt==3){
//        Console.print("lat:");
        latVal=atof(tp);
//        Console.println(latVal);
        
      }
//      if(cnt==4){
//        Console.print("lat sign:");
//        latSign=(char)tp;
//        Console.println(latSign);
//        
//      }
      if(cnt==5){
//        Console.print("long:");
        longVal=atof(tp);
//        Console.println(longVal);
        
      }
//      if(cnt==6){
//        Console.print("long sign:");
//        longSign=(char)tp;
//        Console.println(longSign);
//        
//      }
      if(cnt==10){
//        Console.print("alti sign:");
        altiVal=atof(tp);
//        Console.println(altiVal);
      }
      tp = strtok( NULL,"," );
    }
//    Console.println((double)utc);
//    Console.println((float)latVal);
//    Console.println((char)latSign);
//    Console.println((float)longVal);
//    Console.println((char)longSign);
//    // print RSSI of packet
//    Console.print("' with RSSI ");
//    Console.println(LoRa.packetRssi());


//  ThingSpeak.setField(1,ID);
    ThingSpeak.setField(2,LoRa.packetRssi());
    ThingSpeak.setField(3,latVal);
    ThingSpeak.setField(4,longVal);
    ThingSpeak.setField(5,altiVal);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);   // Send Data to IoT Server.
  }
}
