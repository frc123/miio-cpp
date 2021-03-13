# Code Structure
.
├── aes.c
├── aes.h
├── aes.hpp // [kokke/tiny-AES-c](https://github.com/kokke/tiny-AES-c)
├── log_process.cpp
├── log_process.h
├── main.cpp // Entrance
├── Makefile
├── md5.cpp
├── md5.h // [JieweiWei/md5](https://github.com/JieweiWei/md5)
├── mi_home_aircondition.cpp
├── mi_home_aircondition.h // *air-conditioner class*
├── mi_home_device.cpp
├── mi_home_device.h // *miio protocol parent class*
├── rapidjson
│   ├── // [Tencent/rapidjson](https://github.com/Tencent/rapidjson)
├── socket_class.cpp
├── socket_class.h // udp client/server encapsulation class
├── stdafx.h
├── type_tools.cpp
└── type_tools.h  // type conversion tools

# Makefile

There is a important macro *BIGENDIAN*, and you should define it depends on your mechine.

```
# IMPORTANT: If your machine is Big Endian, please remove the following "#"
# CFLAGS += -DBIGENDIAN
# C++FLAGS += -DBIGENDIAN
```

# Find Your Device Token

There several ways to get the token of your devices. 

The recommended method is get tokens from log files from Mi Home app 5.4.49 for Android.

Browser to files in `SmartHome/logs/` and search your devices so you may obtain tokens.

# Secondary Develop

Now, the project only have air conditioner implementation.

For more Mi Home device, you may develop them based on smart-home-server/mi-home-device.

[Mi Home Device Protocal Documentaion](https://iot.mi.com/new/doc/design/spec/overall) will be helpful. You may find field/key and the specfic value of your devices here.

Welcome to contribute the project!
