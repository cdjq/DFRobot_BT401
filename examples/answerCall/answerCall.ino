#include <DFRobot_BT401.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial1(2, 3);

DFRobot_BT401 bt;

void setup(){
  Serial1.begin(115200);
  /*Delay 2s for the BT401 to start*/
  delay(2000);
  while(!bt.begin(Serial1)){
    Serial.println("Init failed, please check wire connection!");
    delay(1000);
  }
  bt.setVOl(30);
  bt.switchFunction(bt.eBluetooth);

}

void loop(){
  //Play
    if(bt.getBtStatus() == bt.eCalling){
      Serial.println(bt.getTelNumber());
      delay(50);
      bt.controltalk(bt.eAnswer);
    }
    if(bt.getBtStatus() == bt.eOnphone){
      delay(2000);
      while(true);
    }
}
