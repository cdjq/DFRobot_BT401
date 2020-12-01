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
  bt.switchFunction(bt.eTFCard);
  bt.setPlayMode(bt.eDeviceCycle);
}

void loop(){
  //播放
  bt.playControl(bt.ePlay);
  delay(3000);
  //暂停
  bt.playControl(bt.ePause);
  delay(3000);
  //下一曲
  bt.next();
  delay(3000);
  //上一曲
  bt.last();
  delay(3000);
  //播放第一个文件
  bt.playSpecFile(1);
  while(1);
  /*删除正在播放的文件*/
  //bt.delCurFile();
}