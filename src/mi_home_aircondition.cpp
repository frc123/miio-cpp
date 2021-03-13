#include "mi_home_aircondition.h"

int aircondition_property_list_inited = 0;
MiHomeDevice::PropertyId aircondition_property_list[17];

void MiHomeAirconditionInitPropertyList()
{
    aircondition_property_list_inited = 1;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::POWER].did = "power";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::POWER].siid = 2;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::POWER].piid = 1;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::MODE].did = "mode";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::MODE].siid = 2;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::MODE].piid = 2;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::TARGET_TEMPERATURE].did = "target_temperature";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::TARGET_TEMPERATURE].siid = 2;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::TARGET_TEMPERATURE].piid = 4;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::ECO].did = "eco";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::ECO].siid = 2;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::ECO].piid = 7;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::HEATER].did = "heater";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::HEATER].siid = 2;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::HEATER].piid = 9;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::DRYER].did = "dryer";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::DRYER].siid = 2;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::DRYER].piid = 10;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::SLEEP_MODE].did = "sleep_mode";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::SLEEP_MODE].siid = 2;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::SLEEP_MODE].piid = 11;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::FAN_SPEED].did = "fan_speed";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::FAN_SPEED].siid = 3;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::FAN_SPEED].piid = 2;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::VERTICAL_SWING].did = "vertical_swing";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::VERTICAL_SWING].siid = 3;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::VERTICAL_SWING].piid = 4;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::TEMPERATURE].did = "temperature";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::TEMPERATURE].siid = 4;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::TEMPERATURE].piid = 7;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::BUZZER].did = "buzzer";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::BUZZER].siid = 5;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::BUZZER].piid = 1;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::LED].did = "led";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::LED].siid = 6;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::LED].piid = 1;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::ELECTRICITY].did = "electricity";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::ELECTRICITY].siid = 8;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::ELECTRICITY].piid = 1;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::CLEAN].did = "clean";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::CLEAN].siid = 9;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::CLEAN].piid = 1;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::RUNNING_DURATION].did = "running_duration";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::RUNNING_DURATION].siid = 9;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::RUNNING_DURATION].piid = 5;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::FAN_SPEED_PERCENT].did = "fan_speed_percent";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::FAN_SPEED_PERCENT].siid = 10;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::FAN_SPEED_PERCENT].piid = 1;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::TIMER].did = "timer";
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::TIMER].siid = 10;
    aircondition_property_list[MiHomeAircondition::PropertiesIndex::TIMER].piid = 3;
}

MiHomeAircondition::MiHomeAircondition()
{
    if (aircondition_property_list_inited == 0)
        MiHomeAirconditionInitPropertyList();
    property_list_ = aircondition_property_list;
}

void MiHomeAircondition::TimerStringFillStruct(const char* timer_str, PropertiesValues& properties_values)
{
    char buf[20];
    int len = (int)strlen(timer_str);
    memcpy(buf, timer_str, len);
    buf[len] = 0;
    const char* delim = ",";
    strtok(buf, delim);
    char* member2 = strtok(NULL, delim);
    char* member3 = strtok(NULL, delim);
    properties_values.timer_minutes_set = atoi(member2);
    properties_values.timer_delay_on = atoi(member3);
	properties_values.timer_minutes_remain = atoi(member3 + strlen(member3) + 1);
}

int MiHomeAircondition::GetAllProperties(PropertiesValues& properties_values)
{
    Document doc;
    string payload;
    JsonGenGetBatchProperties(GetPacketIdPlus1(), property_list_, PropertiesIndex::POWER, 15, payload);
    if (SendCommand(&payload) < 0)
        return 0;
    if (doc.Parse(payload.c_str()).HasParseError())
        return 0;
    properties_values.power = doc["result"][0]["value"].GetBool();
    properties_values.mode = (ModeValue)doc["result"][1]["value"].GetInt();
    properties_values.target_temperature = doc["result"][2]["value"].GetFloat();
    properties_values.eco = doc["result"][3]["value"].GetBool();
    properties_values.heater = doc["result"][4]["value"].GetBool();
    properties_values.dryer = doc["result"][5]["value"].GetBool();
    properties_values.sleep_mode = doc["result"][6]["value"].GetBool();
    properties_values.fan_speed = (FanSpeedValue)doc["result"][7]["value"].GetInt();
    properties_values.vertical_swing = doc["result"][8]["value"].GetBool();
    properties_values.temperature = doc["result"][9]["value"].GetInt();
    properties_values.buzzer = doc["result"][10]["value"].GetBool();
    properties_values.led = doc["result"][11]["value"].GetBool();
    properties_values.clean = doc["result"][13]["value"].GetString();
    properties_values.running_duration = doc["result"][14]["value"].GetFloat();
    JsonGenGetBatchProperties(GetPacketIdPlus1(), property_list_, PropertiesIndex::FAN_SPEED_PERCENT, 2, payload);
    if (SendCommand(&payload) < 0)
        return 0;
    if (doc.Parse(payload.c_str()).HasParseError())
        return 0;
    properties_values.fan_speed_percent = doc["result"][0]["value"].GetInt();
    const char* timer_str = doc["result"][1]["value"].GetString();
    TimerStringFillStruct(timer_str, properties_values);
    return 1;
}

int MiHomeAircondition::GetTemperature(int& value)
{
    return GetProperty(MiHomeAircondition::PropertiesIndex::TEMPERATURE, &value);
}

int MiHomeAircondition::GetRunningDuration(float& value)
{
    return GetProperty(MiHomeAircondition::PropertiesIndex::RUNNING_DURATION, &value);
}

int MiHomeAircondition::SetPower(const bool value)
{
    return SetProperty(MiHomeAircondition::PropertiesIndex::POWER, &value);
}

int MiHomeAircondition::SetMode(const ModeValue value)
{
    int mode = (int)value;
    return SetProperty(MiHomeAircondition::PropertiesIndex::MODE, &mode);
}

int MiHomeAircondition::SetTargetTemperature(const float value)
{
    return SetProperty(MiHomeAircondition::PropertiesIndex::TARGET_TEMPERATURE, &value);
}

int MiHomeAircondition::SetEco(const bool value)
{
    return SetProperty(MiHomeAircondition::PropertiesIndex::ECO, &value);
}

int MiHomeAircondition::SetHeater(const bool value)
{
    return SetProperty(MiHomeAircondition::PropertiesIndex::HEATER, &value);
}

int MiHomeAircondition::SetDryer(const bool value)
{
    return SetProperty(MiHomeAircondition::PropertiesIndex::DRYER, &value);
}

int MiHomeAircondition::SetSleepMode(const bool value)
{
    return SetProperty(MiHomeAircondition::PropertiesIndex::SLEEP_MODE, &value);
}

int MiHomeAircondition::SetFanSpeed(const FanSpeedValue value)
{
    int fan_speed = (int)value;
    return SetProperty(MiHomeAircondition::PropertiesIndex::FAN_SPEED, &fan_speed);
}

int MiHomeAircondition::SetVerticalSwing(const bool value)
{
    return SetProperty(MiHomeAircondition::PropertiesIndex::VERTICAL_SWING, &value);
}

int MiHomeAircondition::SetBuzzer(const bool value)
{
    return SetProperty(MiHomeAircondition::PropertiesIndex::BUZZER, &value);
}

int MiHomeAircondition::SetLed(const bool value)
{
    return SetProperty(MiHomeAircondition::PropertiesIndex::LED, &value);
}

int MiHomeAircondition::SetFanSpeedPercent(const int value)
{
    return SetProperty(MiHomeAircondition::PropertiesIndex::FAN_SPEED_PERCENT, &value);
}

int MiHomeAircondition::SetTimer(int minutes, bool delay_on)
{
    char buf[10];
    memset(buf, 0, 10);
    sprintf(buf, "1,%u,%i", minutes, delay_on);
    string value = buf;
    int ret;
    ret = SetProperty(MiHomeAircondition::PropertiesIndex::TIMER, &value);
    return ret;
}
