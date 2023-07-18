/***********************************************************************************
 * Copyright:   上海幻身科技有限公司
 * Created:     2022/09/20
 * Author:      moonseer
 * E-mail:      929204168@qq.com
 *
 * Notice:		支持基于moonseer 1.0 (BLE5.0芯片) 的体感服驱动
 *
 * Protocol:    Bluetooth 5.0
 * 
 * History: 
 *        2022/09/20  Create
 * 
 * Version:
 *        1.0
 * 
 * SDK Download URL: 
 *
 **********************************************************************************/

#pragma once
// #define SOURCE_DATA
#ifndef MOONSEER_DEVICE_DRIVER
#define MOONSEER_DEVICE_DRIVER

#define _DLL_MOONSEER_DEVICE_DRIVER
#ifdef _DLL_MOONSEER_DEVICE_DRIVER
#define MOONSEER_DEVICE_DRIVER_EXPORT extern "C" __declspec(dllexport)
#else
#define MOONSEER_DEVICE_DRIVER_EXPORT __declspec(dllimport)
#endif


#include <functional>
/////////////////////////////////// Type Definition ///////////////////////////////////
typedef unsigned char b8;
typedef unsigned long ulong;

enum class DeviceEnum : b8
{
	RightInfrared = 0x01,
	LeftInfrared = 0x02,
	RightButton = 0x04,
	LeftButton = 0x08,
};
 
enum class DeviceState : b8
{
	// 断线
	Disconnected = 0x01,
	// 正常
	Connected = 0x02
};

/////////////////////////////////// Public API Declare ////////////////////////////////
// 标定完成回调
// 参数：modules  1: 盔甲,2 左脚，3 右脚
typedef void (*LPFN_HS_CalibrationCompleteResult)(int modules);
// 获取电量回调
// 参数: power,电量
typedef void (*LPFN_HS_GetPowerResult)(int power);
// 盔甲移动回调
// 参数：frontOrBack ∈ [-1,0) 前移动, 0 静止, (0, +1] 后移动
// 参数：leftOrRight ∈ [-1,0) 左移动, 0 静止, (0, +1] 右移动
typedef void (*LPFN_HS_ArmorMoveResult)(double frontOrBack, double leftOrRight);
// 按钮按下(rising edge trigger mode)
typedef void (*LPFN_HS_PushButtonClick) (b8 buttonId, bool state);
// 按钮持续触摸(level trigger mode)
typedef void (*LPFN_HS_PushButtonStick) (b8 buttonId);
// 红外进入(rising edge trigger mode)
typedef void (*LPFN_HS_InfraredEntry) (b8 buttonId, bool state);
// 红外维持(level trigger mode)
typedef void (*LPFN_HS_InfraredSustained) (b8 buttonId);
// 腿部移动回调
// 参数：frontOrBack ∈ [-1,0) 前移动, 0 静止, (0, +1] 后移动
// 参数：leftOrRight ∈ [-1,0) 左移动, 0 静止, (0, +1] 右移动
typedef void (*LPFN_HS_LegMoveResult)(b8 pos, double frontOrBack, double leftOrRight);
// 状态发生变化
typedef void (*LPFN_HS_DeviceStateChanged)(b8 state);




// 初始化
MOONSEER_DEVICE_DRIVER_EXPORT void HS_Init();
// 设备状态发生变化
// 状态变化为在线（DeviceState::Connected）和离线 (DeviceState::Disconnected)
MOONSEER_DEVICE_DRIVER_EXPORT void HS_DeviceStateChanged(LPFN_HS_DeviceStateChanged _fn);
// 标定
MOONSEER_DEVICE_DRIVER_EXPORT void HS_Calibration(int modules);
// 设置标定精度
MOONSEER_DEVICE_DRIVER_EXPORT void HS_SetPrecision(int modules, int precision);
// 设置标定完成回调函数
MOONSEER_DEVICE_DRIVER_EXPORT void HS_CalibrationCompleteResult(LPFN_HS_CalibrationCompleteResult _fn);
// 获取Power
MOONSEER_DEVICE_DRIVER_EXPORT void HS_PowerResult(LPFN_HS_GetPowerResult _fn);
// 设置盔甲移动
MOONSEER_DEVICE_DRIVER_EXPORT void HS_SetArmorMoveResult(LPFN_HS_ArmorMoveResult _fn);
// 按钮按下时触发
MOONSEER_DEVICE_DRIVER_EXPORT void HS_PushButtonClick(LPFN_HS_PushButtonClick _fn);
// 按钮持续触摸时触发
MOONSEER_DEVICE_DRIVER_EXPORT void HS_PushButtonStick(LPFN_HS_PushButtonStick _fn);
// 红外进入时触发
MOONSEER_DEVICE_DRIVER_EXPORT void HS_InfraredEntry(LPFN_HS_InfraredEntry _fn);
// 红外持续时触发
MOONSEER_DEVICE_DRIVER_EXPORT void HS_InfraredSustained(LPFN_HS_InfraredSustained _fn);
// 设置脚步移动
MOONSEER_DEVICE_DRIVER_EXPORT void HS_SetLegMoveResult(LPFN_HS_LegMoveResult _fn);
// 释放资源
MOONSEER_DEVICE_DRIVER_EXPORT void HS_UnInit();

// 震动设置
// motorIndex 取值: 0 - 11
// shakeTime 时间: 每一个值代表100ms，超过0x80自动截取为0x80, 范围∈[1,128]
// shakePower 振动幅度 取值范围∈ [1,100]
MOONSEER_DEVICE_DRIVER_EXPORT void HS_SetArmorShake(b8 motorIndex, b8 shakeTime, b8 shakePower);
// 震动
MOONSEER_DEVICE_DRIVER_EXPORT void HS_ArmorShake();

#endif
