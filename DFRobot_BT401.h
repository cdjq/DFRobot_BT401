/*!
 * @file DFRobot_BT401.h
 * @brief Define basic structure of DFRobot_BT401 class
 * @n This is an library for capacitive fingerprint module
 * @n Main functions: fingerprint image capturing, fingerprint comparison, fingerprint deletion
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Eddard](eddard.liu@dfrobot.com)
 * @version  V1.0
 * @date  2020-03-19
 * @get from https://www.dfrobot.com
 * @url https://github.com/cdjq/DFRobot_BT401
 */

#ifndef _DFRobot_BT401_H
#define _DFRobot_BT401_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Wire.h>
#include <stdint.h>
#include <SoftwareSerial.h>
//#define ENABLE_DBG
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

class DFRobot_BT401{
public:
  
  //工作模式
  typedef enum{
    eBluetooth = 1,  //蓝牙模式
    eUDisk,          //U盘模式
    eTFCard,         //TF卡模式
    eIdle = 8            //空闲模式
  }eFunction_t;
  
  //播放模式
  typedef enum{
    eRepeatAll = 0,  //全部循环
    eDeviceCycle,      //单设备循环
    eSingleCycle,    //单曲循环
    eDeviceRandom,    //单设备随机播放
    eFileCycle      //文件夹循环
  }ePlayMode_t;
  
  //播放控制
  typedef enum{
    eStop = 0,       //停止
    ePlay,           //播放
    ePause,          //暂停
    ePPSwitch,       //播放&暂停切换
    eFF,             //快进
    eFR,             //快退
    eNextFile,    //播放下一个文件夹
    eLastFile     //播放上一个文件夹
  }ePlayControl_t;
  
  //通话控制
  typedef enum{
    eCallBack = 0,       //回拨上一个电话
    eDisconnectBLE,              //断开蓝牙连接
    eRejectCall,           //拒接
    eHangUp,          //挂断电话
    eAnswer        //接听电话
  }eControltalk_t;
  
  //蓝牙状态
  typedef enum{
   eStandby,  //等待配对
   eBTIdle,   //空闲
   ePlaying,  //正在播放音乐
   eCalling,  //有电话打入
   eOnphone,  //通话中
   eError,
  }eBtStatus;
public:
  DFRobot_BT401();
  bool begin(Stream &s);
  //设置音量
  bool setVOl(uint8_t vol);
  //设置工作模式
  bool switchFunction(eFunction_t function);
  //播放模式
  bool setPlayMode(ePlayMode_t mode);
  //播放控制  仅对TF卡和U盘播放有效
  bool playControl(ePlayControl_t cmd);
  //下一曲
  bool next();
  //上一曲
  bool last();
  //指定设备的第N个文件进行播放  指定序号播放
  bool playSpecFile(uint16_t number);
  //指定路径播放
  bool playSpecFile(const char* path);
  //删除当前播放的文件
  bool delCurFile();
  //呼叫电话号码
  bool callOut(const char* phoneNumber);
  //通话控制
  bool controltalk(eControltalk_t cmd);
  //复位
  bool reset();
  //得到蓝牙状态
  eBtStatus getBtStatus();
  //获取通话号码
  String  getTelNumber();
protected:
 /**
  * @brief Send data 
  * @param Data frame
  */
  void sendCMD(const char *cmd, const char *payload);
  void sendCMD(const char *cmd);
  
  String readAck(uint8_t len = 4);

private:
  Stream *_s;
};

#endif

