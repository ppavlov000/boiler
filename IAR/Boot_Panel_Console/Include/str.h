#ifndef __STR
#define __STR
//-----------------------------------------------------------------------------------
#include "types.h"
//-----------------------------------------------------------------------------------
eu8 outtxt[400],word[40],*wordptr;
eu8 intxt[40],*inptr;
eu8 *outptr;

eu32 ltmp;
eu16 wtmp;
eu8  ctmp;
ed64   dtmp;
//-----------------------------------------------------------------------------------
void sprintf(u8 *out,u8 *in);
void sprintf_P(u8 *out, u8 __farflash * in);
s32 strtol(u8* txt,u8**endtxt,u8 digits);
void WordToStr(u8 *out,u16 *val,u8 format);
void ByteToStr2(u8 **out,u8 *val,u8 format);
void ByteToStr(u8 *out,u8 *val,u8 format);
void ByteToStrFillZero(u8 *out,u8 *val,u8 format,u8 digits,u8 fill);
void LongToStr(u8 *out,u32 *val,u8 format);
void strlwr(char *str);
u8 strcmp2(u8* str1,u8* str2);
u8 strcmp3(u8* str1,u8* str2);
void strcat2(u8* str1,u8* str2);
void strcpy2(u8* str1,u8* str2);
void memset2(u8 *s,u8 c, u8 len);
void memcpy2(u8 *s,u8 *c, u8 len);
u16 strlen2(u8* str1);
void stradd(u8* str1,u8* str2);
void WordToStrFillZero(u8 *out,u16 *val,u8 format,u8 digits,u8 fill,u8 sign);
void ShowTemperature(u8 *out,s16 *val);
void ShowTemperatureShort(u8 *out,s16 *val);
void ShowPowerShort(u8 *out,s16 *val);
void WordToStrSigned(u8 *out,s16 *val);
//-----------------------------------------------------------------------------------
#endif
