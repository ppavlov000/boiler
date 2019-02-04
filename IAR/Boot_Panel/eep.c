#include "eep.h"
#include "inavr.h"
void EEPut(u16 Addr,u8 *Data,u8 Len)
{
  u8 i;
  for(i=0;i<Len;i++)
  {
    __watchdog_reset();
    *((u8 __eeprom *)Addr+i)=*Data;
    __watchdog_reset();
    Data++;
  }
}
void EEGet(u8 *Data,u16 Addr,u8 Len)
{
  u8 i;
  for(i=0;i<Len;i++)
  {
    __watchdog_reset();
    *Data= *((u8 __eeprom *)Addr+i);
    __watchdog_reset();
    Data++;
  }
}

