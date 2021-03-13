#pragma once
#include "stdafx.h"
#include "mi_home_device.h"

class MiHomeAircondition : public MiHomeDevice
{
public:
	enum PropertiesIndex
	{
		POWER = 0, MODE, TARGET_TEMPERATURE, ECO, HEATER, DRYER, SLEEP_MODE,
		FAN_SPEED, VERTICAL_SWING, TEMPERATURE, BUZZER, LED, ELECTRICITY, 
		CLEAN, RUNNING_DURATION, FAN_SPEED_PERCENT, TIMER
	};
	enum ModeValue
	{
		COOL = 2,
		DRY = 3,
		FAN = 4,
		HEAT = 5,
	};
	enum FanSpeedValue
	{
		AUTO = 0,
		LEVEL1, LEVEL2, LEVEL3, LEVEL4, LEVEL5, LEVEL6, LEVEL7,
	};
	struct PropertiesValues
	{
		bool power;
		ModeValue mode;
		float target_temperature;
		bool eco;
		bool heater;
		bool dryer;
		bool sleep_mode;
		FanSpeedValue fan_speed;
		bool vertical_swing;
		int temperature;
		bool buzzer;
		bool led;
		//void electricity;
		string clean;
		float running_duration;
		int fan_speed_percent;
		int timer_minutes_set;
		int timer_minutes_remain;
		bool timer_delay_on;
	};
private:
	static void TimerStringFillStruct(const char* timer_str, PropertiesValues& properties_values);
public:
	MiHomeAircondition();
	int GetAllProperties(PropertiesValues& properties_values);
	int GetTemperature(int& temperature);
	int GetRunningDuration(float& value);
	int SetPower(const bool value);
	int SetMode(const ModeValue value);
	int SetTargetTemperature(const float temperature);
	int SetEco(const bool value);
	int SetHeater(const bool value);
	int SetDryer(const bool value);
	int SetSleepMode(const bool value);
	int SetFanSpeed(const FanSpeedValue value);
	int SetVerticalSwing(const bool value);
	int SetBuzzer(const bool value);
	int SetLed(const bool value);
	int SetFanSpeedPercent(const int value);
	int SetTimer(int minutes, bool delay_on);

};