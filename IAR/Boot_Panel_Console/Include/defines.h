#ifndef _DEFINES_H_
#define _DEFINES_H_


#define CPU_CLOCK 11059200L
/*------------------------------------------------------------------*/
/* for 7.3728 MHz */
/*------------------------------------------------------------------*/
#define UART_BaudRate_2400     191
#define UART_BaudRate_4800     95
#define UART_BaudRate_9600     47
#define UART_BaudRate_14400    31
#define UART_BaudRate_19200    23
#define UART_BaudRate_28800    15
#define UART_BaudRate_38400    11
#define UART_BaudRate_57600    7
#define UART_BaudRate_76800    5
#define UART_BaudRate_115200   3
#define UART_BaudRate_230400   1

/*------------------------------------------------------------------*/
#define Ok   1
#define None 0
#define Err -1

/*------------------------------------------------------------------*/
typedef unsigned char           uchar;
typedef signed   short          sint;
typedef unsigned short          usint;
typedef signed   long           lint;
typedef unsigned long           ulint;

typedef ulint                   t_ticks;
#define mat_t_ticks             0xffffffffU


#define  in_flash       __farflash           
#define  sptr          (char in_flash *)
#define  vptr          (void in_flash *)

//#define BOOTFLASH __farflash
//#define APPFLASH  __farflash

/*------------------------------------------------------------------*/
#define Bit(n)           (1 << n)
#define SetBit(addr,n)   (addr |=  (1 << n))
#define ClearBit(addr,n) (addr &= ~(1 << n))
#define CheckBit(addr,n) (addr &   (1 << n))

/*------------------------------------------------------------------*/
#define  ledSys(f)     (f?SetBit(DDRF,0):ClearBit(DDRF,0))

/*------------------------------------------------------------------*/
#undef   max
#define  max(a,b)       (((a) > (b)) ? (a) : (b))
#undef   min
#define  min(a,b)       (((a) < (b)) ? (a) : (b))
/*------------------------------------------------------------------*/
#define  descriptor_next(a,b)       ((a+1)&b)
#define  descriptor_prev(a,b)       ((a-1)&b)
/*------------------------------------------------------------------*/
#define defCFG_RequestSize  21
#define defCFG_ResponseSize 21

/*--------------------------------------------------------------------------*/
#define INT_HardDown  0
#define INT_AdmDown   1
#define INT_Down      2
#define INT_Trying    3
#define INT_Up        4
#define INT_Unknown   5

/*--------------------------------------------------------------------------*/
#define bitSysReq     2 // port D

/*--------------------------------------------------------------------------*/
typedef enum {
  eSw_On,
  eSw_Off,
  eSw_Unknown
} E_ON_OFF;
/*--------------------------------------------------------------------------*/
typedef enum {
  eEd_Enable,
  eEd_Disable,
  eEd_Unknown
} E_EN_DIS;
/*--------------------------------------------------------------------------*/
typedef enum {
  eLs_Unlocked,
  eLs_Locked,
  eLs_Unknown
} E_LOCK_STATUS;
/*--------------------------------------------------------------------------*/
typedef enum {
  eInt_HardDown,
  eInt_AdmDown,
  eInt_Down,
  eInt_Trying,
  eInt_Up
} E_INTERFACE;
/*--------------------------------------------------------------------------*/
typedef enum {
  eVfix_1_2,
  eVfix_2_3,
  eVfix_3_4,
  eVfix_5_6,
  eVfix_7_8,
  eVfix_6_7,
  eVauto
} E_VITERBI_RATE;
/*--------------------------------------------------------------------------*/
typedef enum {
  eSpectrum_Normal,
  eSpectrum_Invert,
  eSpectrum_Togle
} E_SPECTRUM;
/*--------------------------------------------------------------------------*/
typedef enum {
  eENetSpeed_Auto,
  eENetSpeed_100HD,
  eENetSpeed_100FD,
  eENetSpeed_10HD,
  eENetSpeed_10FD,
  eENetSpeed_Unknown
} E_ENET_SPEED;
/*------------------------------------------------------------------*/
typedef struct {
 E_INTERFACE    Interface;
 uchar          LnbFlags;
 ulint          SysClk;
 ulint          Freq;
 ulint          CompFreq;
 ulint          AcqRange;
 ulint          SymbolRate;
 E_VITERBI_RATE ViterbiRate;
} TUNER_CONFIG;
/*------------------------------------------------------------------*/
typedef struct {
 E_INTERFACE Interface;
 uchar        Mac[6];
 uchar        DMac[6];
 E_ENET_SPEED Speed;
} ENET_CONFIG;
/*------------------------------------------------------------------*/
typedef struct {
 E_INTERFACE    Interface;
} DEMUX_CONFIG;
/*------------------------------------------------------------------*/
#define defCFG_DeviceNameSize 11
typedef struct {
  TUNER_CONFIG Tuner;
  DEMUX_CONFIG Demux;
  ENET_CONFIG  ENet;
  char         Name[defCFG_DeviceNameSize];
} CONFIG;

#define defCFG_EepromStartAddress 0x0000
/*------------------------------------------------------------------*/
typedef struct { /*размер должнен быть кратным DES_BLOCK_SIZE*/
 usint Flags;
 ulint SrcIp;
 usint SrcPort;
 uchar DateTime[6];
 uchar unused[8];
 usint Crc;
} IS_CONFIG; /*3 блока*/

#define defIS_EepromStartAddress 0x0400//(sizeof(CONFIG) + sizeof(usint))

#endif

