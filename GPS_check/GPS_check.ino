#include <SPI.h>
#include <LoRa.h>
//#include <RH_RF95.h>
#include <SoftwareSerial.h>
#define RX A1
#define TX A2

char msg[100];
int msgLength;
SoftwareSerial mySerial(RX,TX);
//RH_RF95 rf95;
//float frequency = 923.6;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Starting");
  
  Serial.println("LoRa Sender");
//  if (!rf95.init())
//    Serial.println("init failed");
//  // Setup ISM frequency
//  rf95.setFrequency(frequency);
//  // Setup Power,dBm
//  rf95.setTxPower(23);
//  RH_RF95::ModemConfig config;
//  config.reg_1d = 0b01110000 | 0b0100; // Bw125 | Cr46
//  config.reg_1e = 0b10010000 | 0b0100; // Sf512 | CRCon
//  config.reg_26 = 0b00000000; // default.
//  rf95.setModemRegisters(&config);

  if (!LoRa.begin(9236E5)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(9);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(6);
  LoRa.crc();
  LoRa.setTxPower(13);
  mySerial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  if(mySerial.available()){
    char c = mySerial.read();
    if( -1 != c )
    {
      //Serial.print(c);
         
      if('$'==(char)c){
        Serial.print(msg);
        if(msg[0]=='$' && 
           msg[1]=='G' && 
           msg[2]=='P' && 
           msg[3]=='G' && 
           msg[4]=='G' &&
           msg[5]=='A'){
//            char *tp;
//            int cnt=0;
//            /* スペース.を区切りに文字列を抽出 */   
//            tp = strtok( msg, "," );
//            char latSign,longSign,*stopstring;
//            double utc;
//            float latVal,longVal;
//            
//            while ( tp != NULL ) {
//              cnt++;
//              if(cnt==2){
//                Serial.print("UTC:");
//                utc=strtod(tp,&stopstring);
//                Serial.println(utc);
//                
//              }
//              if(cnt==3){
//                Serial.print("lat:");
//                latVal=atof(tp);
//                Serial.println(latVal);
//                
//              }
//              if(cnt==4){
//                Serial.print("lat sign:");
//                latSign=(char)tp;
//                Serial.println(latSign);
//                
//              }
//              if(cnt==5){
//                Serial.print("long:");
//                longVal=atof(tp);
//                Serial.println(longVal);
//                
//              }
//              if(cnt==6){
//                Serial.print("long sign:");
//                longSign=(char)tp;
//                Serial.println(longSign);
//                
//              }
//              tp = strtok( NULL,"," );
//            }
            // send packet
//            rf95.send(msg, strlen((char*)msg));
            LoRa.beginPacket();
//            LoRa.print(utc);
//            LoRa.print(",");
//            LoRa.print(latVal);
//            LoRa.print(",");
//            LoRa.print(latSign);
//            LoRa.print(",");
//            LoRa.print(longVal);
//            LoRa.print(",");
//            LoRa.print(longSign);
            LoRa.print(msg);
            LoRa.endPacket();
            delay(5000);
        }
        *msg = "";
        msgLength=0;
        msg[msgLength] = c;
        Serial.println();
      }else {
        msgLength++;
        msg[msgLength] = c;
      }
    }
  }
  
  //Serial.println(digitalRead(A0));
}
