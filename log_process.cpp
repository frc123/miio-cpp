#include "log_process.h"

void ErrorThrow(int error_code, const char* error_msg)
{
	printf("error_code:%u\n", error_code);
	printf("error_msg:%s\n", error_msg);

}

void ErrorThrow(int error_code, const char* error_msg, const char* error_msg_extra )
{
	printf("error_code:%u\n", error_code);
	printf("error_msg:%s\n", error_msg);
	printf("error_msg_extra:%s\n", error_msg_extra);

}

void ExitProcess(int exit_code)
{
	exit(exit_code);
}

