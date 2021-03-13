#include "stdafx.h"
#include "mi_home_aircondition.h"
#include "log_process.h"

//TODO: Put your air condition ip address here
#define AIRCONDITION_IP_ADDRESS  ""
//TODO: Put your air condition token here
#define AIRCONDITION_TOKEN ""

int main()
{
    int ret;
    //aircondition init
    MiHomeAircondition aircondition;
    ret = aircondition.Init(AIRCONDITION_IP_ADDRESS, AIRCONDITION_TOKEN);
    printf("aircondition init ret:%i\n", ret);
    ExitProcess(0);
    return 0;
}


