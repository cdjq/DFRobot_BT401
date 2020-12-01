#include <DFRobot_BT401.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial1(2, 3);

DFRobot_BT401 bt;

void setup(){
  Serial1.begin(115200);
  /*延时2S等待BT401启动完成*/
  delay(2000);
  while(!bt.begin(Serial1)){
    Serial.println("初始化失败，请检查接线！");
    delay(1000);
  }
  bt.setVOl(30);
  bt.switchFunction(bt.eBluetooth);

}

void loop(){
  //播放
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
