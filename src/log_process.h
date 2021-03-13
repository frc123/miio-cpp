#pragma once
#include "stdafx.h"

void ErrorThrow(int error_code, const char* error_msg);
void ErrorThrow(int error_code, const char* error_msg, const char* error_msg_extra);
void ExitProcess(int exit_code);
