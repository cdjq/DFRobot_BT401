/*!
 * @file DFRobot_BT401.cpp
 * @brief Define the basic structure of DFRobot_BT401 class and the implementation of underlying methods
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Eddard](eddard.liu@dfrobot.com)
 * @version  V1.0
 * @date  2020-03-19
 * @get from https://www.dfrobot.com
 * @url https://github.com/cdjq/DFRobot_BT401
 */

#include <DFRobot_BT401.h>
#include <Arduino.h>
#include <string.h>
#include <stdio.h>


DFRobot_BT401::DFRobot_BT401()
{

}

bool DFRobot_BT401::begin(Stream &s){
  _s = &s;
  if(_s == NULL){
      return false;
  }
  return true;
}

//设置音量
bool DFRobot_BT401::setVOl(uint8_t vol)
{
  char data[2];
  itoa(vol, data, 10);
  if(vol > 9){
    sendCMD("CA", data);
  } else{
    sendCMD("CA0", data);
  }
  if(readAck() == "OK\r\n"){
    return true;
  } else{
    return false;
  }
}

//设置工作模式
bool DFRobot_BT401::switchFunction(eFunction_t function)
{
  char data[1];
  itoa(function, data, 10);
  sendCMD("CM0", data);
  if(readAck() == "OK\r\n"){
    return true;
  } else{
    return false;
  }
}

//播放模式
bool DFRobot_BT401::setPlayMode(ePlayMode_t mode)
{
  char data[1];
  itoa(mode, data, 10);
  sendCMD("AC0", data);
  if(readAck() == "OK\r\n"){
    return true;
  } else{
    return false;
  }
}

//播放控制  仅对TF卡和U盘播放有效  AA
bool DFRobot_BT401::playControl(ePlayControl_t cmd)
{
  char data[1];
  itoa(cmd, data, 10);
  sendCMD("AA0", data);
  if(readAck() == "OK\r\n"){
    return true;
  } else{
    return false;
  }
}

//下一曲
bool DFRobot_BT401::next()
{
  sendCMD("CD");
  if(readAck() == "OK\r\n"){
    return true;
  } else{
    return false;
  }
}

//上一曲
bool DFRobot_BT401::last()
{
  sendCMD("CC");
  if(readAck() == "OK\r\n"){
    return true;
  } else{
    return false;
  }
}

//指定设备的第N个文件进行播放
bool DFRobot_BT401::playSpecFile(uint16_t number)
{
  char data[5];
  itoa(number, data, 10);
  sendCMD("AB", data);
  if(readAck() == "OK\r\n"){
    return true;
  } else{
    return false;
  }
}

//指定文件夹循环播放
bool DFRobot_BT401::playSpecFile(const char* path)
{
  sendCMD("AF", path);
  if(readAck() == "OK\r\n"){
    return true;
  } else{
    return false;
  }
}

//删除当前播放的文件
bool DFRobot_BT401::delCurFile()
{
  sendCMD("AA08");
  if(readAck() == "OK\r\n"){
    return true;
  } else{
    return false;
  }
}

//呼叫电话号码
bool DFRobot_BT401::callOut(const char *phoneNumber)
{
  sendCMD("BT", phoneNumber);
  if(readAck() == "OK\r\n"){
    return true;
  } else{
    return false;
  }
}

//通话控制
bool DFRobot_BT401::controltalk(eControltalk_t cmd)
{
  char data[1];
  itoa(cmd, data, 10);
  sendCMD("BA0", data);
  if(readAck() == "OK\r\n"){
    return true;
  } else{
    return false;
  }
}
DFRobot_BT401::eBtStatus DFRobot_BT401::getBtStatus(){

  sendCMD("TS", NULL);
  String status = readAck();
  if(status == "TS+00\r\n"){
    return eStandby;
  }else if(status == "TS+01\r\n"){
    return eBTIdle;
  }else if(status == "TS+02\r\n"){
    return ePlaying;
  }else if(status == "TS+03\r\n"){
    return eCalling;
  }else if(status == "TS+04\r\n"){
    return eOnphone;
  }
  
   return eError;
}
String DFRobot_BT401::getTelNumber(){

  sendCMD("TT", NULL);
  String phone="";
  String data = readAck();
  for(uint8_t i = 0;i < data.length()-3;i++){
      phone += data[3+i];
  }
  
  return phone;

}
//复位
bool DFRobot_BT401::reset()
{
  sendCMD("CZ");
  if(readAck() == "OK\r\n"){
    return true;
  } else{
    return false;
  }
}

void DFRobot_BT401::sendCMD(const char *cmd, const char *payload)
{
  String data;
  data = "AT+";
  data += cmd;
  data +=payload;
  data += "\r\n";
  uint8_t length = data.length();
  uint8_t at[20];
  for(uint8_t i=0;i<length;i++)
    at[i] = data[i];
  _s->write(at,length);
}

void DFRobot_BT401::sendCMD(const char *cmd)
{
  String data;
  data = "AT+";
  data += cmd;
  data += "\r\n";
  uint8_t length = data.length();
  uint8_t at[20];
  for(uint8_t i=0;i<length;i++)
    at[i] = data[i];
  _s->write(at,length);
}

String DFRobot_BT401::readAck(uint8_t len)
{
  String str="                             ";
  size_t offset = 0,left = len;
  long long curr = millis();
  if(len = 0){
    while(1) {
      if(_s->available()) {
        str[offset]= _s->read();
        left--;
        offset++;
      }
      if(str[offset - 1] == '\n' && str[offset - 2] == '\r') break;
      if(millis() - curr > 1000) {
        return "error";
        break;
      }
	}
  } else {
    while(left) {
      if(_s->available()) {
         str[offset]= _s->read();
        left--;
        offset++;
      }
      if(millis() - curr > 1000) {
        return "error";
        break;
      }
  }
  }
  str[len]=0;
  return str;
}




