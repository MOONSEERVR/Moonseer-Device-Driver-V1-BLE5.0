/***********************************************************************************
 * Copyright:   �Ϻ�����Ƽ����޹�˾
 * Created:     2022/09/20
 * Author:      moonseer
 * E-mail:      929204168@qq.com
 *
 * Notice:		֧�ֻ���moonseer 1.0 (BLE5.0оƬ) ����з�����
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
	// ����
	Disconnected = 0x01,
	// ����
	Connected = 0x02
};

/////////////////////////////////// Public API Declare ////////////////////////////////
// �궨��ɻص�
// ������modules  1: ����,2 ��ţ�3 �ҽ�
typedef void (*LPFN_HS_CalibrationCompleteResult)(int modules);
// ��ȡ�����ص�
// ����: power,����
typedef void (*LPFN_HS_GetPowerResult)(int power);
// �����ƶ��ص�
// ������frontOrBack �� [-1,0) ǰ�ƶ�, 0 ��ֹ, (0, +1] ���ƶ�
// ������leftOrRight �� [-1,0) ���ƶ�, 0 ��ֹ, (0, +1] ���ƶ�
typedef void (*LPFN_HS_ArmorMoveResult)(double frontOrBack, double leftOrRight);
// ��ť����(rising edge trigger mode)
typedef void (*LPFN_HS_PushButtonClick) (b8 buttonId, bool state);
// ��ť��������(level trigger mode)
typedef void (*LPFN_HS_PushButtonStick) (b8 buttonId);
// �������(rising edge trigger mode)
typedef void (*LPFN_HS_InfraredEntry) (b8 buttonId, bool state);
// ����ά��(level trigger mode)
typedef void (*LPFN_HS_InfraredSustained) (b8 buttonId);
// �Ȳ��ƶ��ص�
// ������frontOrBack �� [-1,0) ǰ�ƶ�, 0 ��ֹ, (0, +1] ���ƶ�
// ������leftOrRight �� [-1,0) ���ƶ�, 0 ��ֹ, (0, +1] ���ƶ�
typedef void (*LPFN_HS_LegMoveResult)(b8 pos, double frontOrBack, double leftOrRight);
// ״̬�����仯
typedef void (*LPFN_HS_DeviceStateChanged)(b8 state);




// ��ʼ��
MOONSEER_DEVICE_DRIVER_EXPORT void HS_Init();
// �豸״̬�����仯
// ״̬�仯Ϊ���ߣ�DeviceState::Connected�������� (DeviceState::Disconnected)
MOONSEER_DEVICE_DRIVER_EXPORT void HS_DeviceStateChanged(LPFN_HS_DeviceStateChanged _fn);
// �궨
MOONSEER_DEVICE_DRIVER_EXPORT void HS_Calibration(int modules);
// ���ñ궨����
MOONSEER_DEVICE_DRIVER_EXPORT void HS_SetPrecision(int modules, int precision);
// ���ñ궨��ɻص�����
MOONSEER_DEVICE_DRIVER_EXPORT void HS_CalibrationCompleteResult(LPFN_HS_CalibrationCompleteResult _fn);
// ��ȡPower
MOONSEER_DEVICE_DRIVER_EXPORT void HS_PowerResult(LPFN_HS_GetPowerResult _fn);
// ���ÿ����ƶ�
MOONSEER_DEVICE_DRIVER_EXPORT void HS_SetArmorMoveResult(LPFN_HS_ArmorMoveResult _fn);
// ��ť����ʱ����
MOONSEER_DEVICE_DRIVER_EXPORT void HS_PushButtonClick(LPFN_HS_PushButtonClick _fn);
// ��ť��������ʱ����
MOONSEER_DEVICE_DRIVER_EXPORT void HS_PushButtonStick(LPFN_HS_PushButtonStick _fn);
// �������ʱ����
MOONSEER_DEVICE_DRIVER_EXPORT void HS_InfraredEntry(LPFN_HS_InfraredEntry _fn);
// �������ʱ����
MOONSEER_DEVICE_DRIVER_EXPORT void HS_InfraredSustained(LPFN_HS_InfraredSustained _fn);
// ���ýŲ��ƶ�
MOONSEER_DEVICE_DRIVER_EXPORT void HS_SetLegMoveResult(LPFN_HS_LegMoveResult _fn);
// �ͷ���Դ
MOONSEER_DEVICE_DRIVER_EXPORT void HS_UnInit();

// ������
// motorIndex ȡֵ: 0 - 11
// shakeTime ʱ��: ÿһ��ֵ����100ms������0x80�Զ���ȡΪ0x80, ��Χ��[1,128]
// shakePower �񶯷��� ȡֵ��Χ�� [1,100]
MOONSEER_DEVICE_DRIVER_EXPORT void HS_SetArmorShake(b8 motorIndex, b8 shakeTime, b8 shakePower);
// ��
MOONSEER_DEVICE_DRIVER_EXPORT void HS_ArmorShake();

#endif
