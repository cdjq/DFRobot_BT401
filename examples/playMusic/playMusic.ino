#include <DFRobot_BT401.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial1(2, 3);

DFRobot_BT401 bt;

void setup(){
  Serial1.begin(115200);
  
  while(!bt.begin(Serial1)){
    Serial.println("初始化失败，请检查接线！");
    delay(1000);
  }
  bt.setVOl(30);
  peratingMode(bt.eTFCard);
  playMode(bt.eDeviceCycle);
}

void loop(){
  //播放
  playControl(bt.ePlay);
  delay(3000);
  //暂停
  playControl(bt.ePause);
  delay(3000);
  //下一曲
  next(bt.ePlay);
  delay(3000);
  //上一曲
  last(bt.ePlay);
  delay(3000);
  //播放第一个
  assignNumPlay(1);
  while(1);
  /*删除正在播放的文件*/
  //bt.delCurFile();
}