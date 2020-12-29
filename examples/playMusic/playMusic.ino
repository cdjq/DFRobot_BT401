
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
  bt.switchFunction(bt.eTFCard);
  bt.setPlayMode(bt.eDeviceCycle);
}

void loop(){
  //Play
  bt.playControl(bt.ePlay);
  delay(3000);
  //Pause 
  bt.playControl(bt.ePause);
  delay(3000);
  //Next 
  bt.next();
  delay(3000);
  //Last 
  bt.last();
  delay(3000);
  //Play song in the first file
  bt.playSpecFile(1);
  while(1);
  /*Delete the currently playing file*/
  //bt.delCurFile();
}
