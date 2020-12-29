/*!
 * @file answerCall.ino.ino
 * @brief 获取来电信息
 * @n Experiment Phenomenon：来电时打印电话号码并接听
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Eddard](Eddard.liu@dfrobot.com)
 * @version  V1.0
 * @date  2020-12-29
 * @get from https://www.dfrobot.com
 * @url https://github.com/cdjq/DFRobot_ID809
*/

#include <DFRobot_BT401.h>
#include <SoftwareSerial.h>

SoftwareSerial btSerial(2, 3);  //RX TX

DFRobot_BT401 bt;

void setup(){
  Serial.begin(115200);
  btSerial.begin(115200);
  /*Delay 2s for the BT401 to start*/
  delay(2000);
  while(!bt.begin(btSerial)){
    Serial.println("Init failed, please check wire connection!");
    delay(1000);
  }
  bt.setVOl(30);
  bt.switchFunction(bt.eBluetooth);
}

void loop(){
    //如果有电话拨入，则打印来电号码并接听
    if(bt.getBtStatus() == bt.eCalling){
      Serial.println(bt.getTelNumber());
      delay(1000);
      //Answer
      bt.controltalk(bt.eAnswer);
      //Refuse to answer
      //bt.controltalk(bt.eRejectCall);
    }
    //如果正处于通话中，则打印来电号码
    if(bt.getBtStatus() == bt.eOnphone){
      Serial.print("通话中:");
      Serial.println(bt.getTelNumber());
      delay(1000);
      //Hang Up
      //bt.controltalk(bt.eHangUp);
    }
}
