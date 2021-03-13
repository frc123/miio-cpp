#pragma once
#include "stdafx.h"

int Bcd2Stamp(int y1, int y2, int m, int d, int H, int M, int S);
int Hex2Ascii(const char* hex, unsigned char* ascii);

inline void Char2Int32LittleEndian(const char* bytes, int position, int* num)
{
	#ifdef BIGENDIAN
		*((char*)num + 0) = *(bytes + position + 3);
		*((char*)num + 1) = *(bytes + position + 2);
		*((char*)num + 2) = *(bytes + position + 1);
		*((char*)num + 3) = *(bytes + position + 0);
	#else
		memcpy(num, &(bytes[position]), 4);
	#endif
}

inline void CharToUint16BigEndian(const unsigned char* bytes, uint16_t* num)
{
	*num = ntohs(*(uint16_t*)bytes);
	/*
    *((char*)num + 0) = *(bytes + 1);
    *((char*)num + 1) = *(bytes + 0);
	*/
}

inline void CharToUint32BigEndian(const unsigned char* bytes, uint32_t* num)
{
	*num = ntohl(*(uint32_t*)bytes);
	/*
    *((char*)num + 0) = *(bytes + 3);
    *((char*)num + 1) = *(bytes + 2);
    *((char*)num + 2) = *(bytes + 1);
    *((char*)num + 3) = *(bytes + 0);
	*/
}

inline void Uint16ToCharBigEndian(const uint16_t* num, unsigned char* bytes)
{
	*(uint16_t*)bytes = htons(*num);
	/*
    *(bytes + 0) = *((unsigned char*)num + 1);
    *(bytes + 1) = *((unsigned char*)num + 0);
	*/
}

inline void Uint32ToCharBigEndian(const uint32_t* num, unsigned char* bytes)
{
	*(uint32_t*)bytes = htonl(*num);
	/*
    *(bytes + 0) = *((unsigned char*)num + 3);
    *(bytes + 1) = *((unsigned char*)num + 2);
    *(bytes + 2) = *((unsigned char*)num + 1);
    *(bytes + 3) = *((unsigned char*)num + 0);
	*/
}

