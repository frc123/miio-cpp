#include "type_tools.h"

/*
int num = int((unsigned char)(*(bytes + 3)) << 24 |
    (unsigned char)(*(bytes + 2)) << 16 |
    (unsigned char)(*(bytes + 1)) << 8 |
    (unsigned char)(*(bytes + 0)));
return num;
*/

int CharBcd2Int(int dec)
{
    int i = 0;
    u_int8_t res[8];
    int des = 0;
    while (dec)
    {
        res[i] = (u_int8_t)dec % 16;
        dec /= 16;
        i++;
    }
    while (i)
    {
        i--;
        des += (int)res[i] * (int)(pow(10.0, (double)i));
    }
    return des;
}

int Bcd2Stamp(int y1, int y2, int m, int d, int H, int M, int S)
{
    struct tm tm;
    tm.tm_year = (CharBcd2Int(y1) - 19) * 100 + CharBcd2Int(y2);
    tm.tm_mon = CharBcd2Int(m);
    tm.tm_mday = CharBcd2Int(d);
    tm.tm_hour = CharBcd2Int(H);
    tm.tm_min = CharBcd2Int(M);
    tm.tm_sec = CharBcd2Int(S);
    return (int)mktime(&tm);
}

int Hex2Ascii(const char* hex, unsigned char* ascii)
{
    int len = (int)strlen(hex), tlen, i, cnt;
    for (i = 0, cnt = 0, tlen = 0; i < len; i++)
    {
        char c = (char)toupper(hex[i]);
        if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))
        {
            char t = (c >= 'A') ? (char)(c - 'A' + 10) : (char)(c - '0');

            if (cnt)
            {
                ascii[tlen] = (unsigned char)(ascii[tlen] + t);
                tlen++;
                //tlen++;
                cnt = 0;
            }
            else
            {
                ascii[tlen] = (unsigned char)(t << 4);
                cnt = 1;
            }
        }
    }
    return tlen;
}
