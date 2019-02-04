#include "main.h"
#include "functions.h"
#include "pinout.h"
#include <intrinsics.h>
#include <iom16c62p.h>

//#include <ctype.h>
#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <yfuns.h>

#define PANEL_ADR	6

#define Xin_CLOCK	16000000UL

#define PLL_CLOCK	(Xin_CLOCK * 1)

#define F1_CLOCK	PLL_CLOCK
#define F8_CLOCK	(F1_CLOCK/8)

//#define F2N_CLOCK	(Xin_CLOCK/30)

#define BCLK_CLOCK	PLL_CLOCK

#define TICKS_PER_SEC 1000

//#define USE_WATCHDOG

//#define RENESAS_USE_UART_0	// rs485

__no_init u8 PanelAddress @ 0x400;

//-----------------------------------------------------------------------------------
#define Ok	1

//-----------------------------------------------------------------------------------
// Timer section
//-----------------------------------------------------------------------------------
u32 TickCnt;

void Timer_Init()
{
	TickCnt = 0;

	TA0MR = 0x44;			// time mode, no gate, f8

	TA0 = F8_CLOCK / TICKS_PER_SEC - 1;

	TA0IC = 1;//PRIORITY_TICKS;	// set int level

	TABSR_bit.TA0S = 1; 	// start timer
}

//-----------------------------------------------------------------------------------
#pragma vector=TMRA0
__interrupt void Timer_IRQ()
{
//	__enable_interrupt();
//	TickCnt++;
	Timer_1ms_IRQ();
}
/*
//-----------------------------------------------------------------------------------
// RS485 section
//-----------------------------------------------------------------------------------
#define UART485_RxBufferSize 128
#define UART485_RxBufferMask (UART485_RxBufferSize - 1)
#if (UART485_RxBufferSize & UART485_RxBufferMask)
#error RX buffer size is not a power of 2
#endif

//--------------------------------------------------------------------------
typedef struct {
//  unsigned char Tmp;
  unsigned char RxBuf[UART485_RxBufferSize];
  unsigned char RxPut;
  unsigned char RxGet;
  unsigned char RxSize;
} UART485;

UART485	Uart485;

#ifdef RENESAS_USE_UART_0
	#define UxTB		U0TB
	#define UxRB		U0RB
	#define UxC1_TI		ti_u0c1	//U0C1_bit.TI
#else
	#define UxTB		U1TB
	#define UxRB		U1RB
	#define UxC1_TI		ti_u1c1	//U1C1_bit.TI
#endif

//-----------------------------------------------------------------------------------
void upc_hardware_init(u32 baud)
{
	memset(&Uart485, 0, sizeof(Uart485));

	// --- pin settings ----------------------------------------
#ifdef RENESAS_USE_UART_0
	// TXD0 out
	PD6_bit.PD6_3 = 1;

	// RXD0 in
	PD6_bit.PD6_2 = 0;

	// nRx/Tx select
	PD6_bit.PD6_5 = 1;

	//--- Special Mode Registers -------------------------------
	U0SMR  = 0;
	U0SMR2 = 0;
	U0SMR3 = 0;
	U0SMR4 = 0;

	//--- Baud Rate Register -----------------------------------
	U0BRG = (F1_CLOCK / (baud * 16)) - 1;

	//--- Transmit/Receive Mode Register -----------------------
	U0MR_bit.SMD0 = 1;	// mode UART 8bit
	U0MR_bit.SMD1 = 0;
	U0MR_bit.SMD2 = 1;

	U0MR_bit.CKDIR = 0;	// internal clock

	U0MR_bit.STPS = 0;	// 1 stop bit

//	U0MR_bit.PRY = 0;	// 0 : Odd parity / 1 : Even parity
	U0MR_bit.PRYE = 0;	// disable parity

	U0MR_bit.IOPOL = 0;	// not inversed

	//--- Transmit/Receive Control Register 0 ------------------
	U0C0_bit.CLK0 = 0;	// 0 1: Selects f1
	U0C0_bit.CLK1 = 0;

//	U0C0_bit.CRS = 0;	// 0 : Selects CTS function / 1 : Selects RTS function
	U0C0_bit.CRD = 1;	// Disables CTS/RTS function

	U0C0_bit.NCH = 0;	// 0 : TxDi/SDAi and SCLi are ports for the CMOS output

	U0C0_bit.CKPOL = 0;	// 0 : tx on the falling edge rx on the rising edge

	U0C0_bit.UFORM = 0;	// 0 : LSB first / 1 : MSB first

	//--- Transmit/Receive Control Register 1 ------------------
	U0C1_bit.TE = 1;	// Transmit enable
	U0C1_bit.TI = 0;	//

	U0C1_bit.RE = 1;	// Receive enable

//	U0C1_bit.U0RRM = 0;

	U0C1_bit.U0LCH = 0;	// Data Logic Select Bit 0: Not inversed / 1: Inverse

//	U0C1_bit.U0ERE = 0;	//

    UCON_bit.U0IRS	= 0;
    UCON_bit.U0RRM	= 0;
    UCON_bit.CLKMD0	= 0;
    UCON_bit.CLKMD1	= 0;
    UCON_bit.RCSP	= 0;

	S0RIC = 1;
#else
	// TXD1 out
	PD6_bit.PD6_7 = 1;

	// RXD1 in
	PD6_bit.PD6_6 = 0;

	//--- Special Mode Registers -------------------------------
	U1SMR  = 0;
	U1SMR2 = 0;
	U1SMR3 = 0;
	U1SMR4 = 0;

	//--- Baud Rate Register -----------------------------------
	U1BRG = (F1_CLOCK / (baud_rate * 16)) - 1;

	//--- Transmit/Receive Mode Register -----------------------
	U1MR_bit.SMD0 = 1;	// mode UART 8bit
	U1MR_bit.SMD1 = 0;
	U1MR_bit.SMD2 = 1;

	U1MR_bit.CKDIR = 0;	// internal clock

	U1MR_bit.STPS = 0;	// 1 stop bit

//	U1MR_bit.PRY = 0;	// 0 : Odd parity / 1 : Even parity
	U1MR_bit.PRYE = 0;	// disable parity

	U1MR_bit.IOPOL = 0;	// not inversed

	//--- Transmit/Receive Control Register 0 ------------------
	U1C0_bit.CLK0 = 0;	// 0 1: Selects f8
	U1C0_bit.CLK1 = 0;

//	U1C0_bit.CRS = 0;	// 0 : Selects CTS function / 1 : Selects RTS function
	U1C0_bit.CRD = 1;	// Disables CTS/RTS function

	U1C0_bit.NCH = 0;	// 0 : TxDi/SDAi and SCLi are ports for the CMOS output

	U1C0_bit.CKPOL = 0;	// 0 : tx on the falling edge rx on the rising edge

	U1C0_bit.UFORM = 0;	// 0 : LSB first / 1 : MSB first

	//--- Transmit/Receive Control Register 1 ------------------
	U1C1_bit.TE = 1;	// Transmit enable
	U1C1_bit.TI = 0;	//

	U1C1_bit.RE = 1;	// Receive enable

//	U1C1_bit.U1RRM = 0;

	U1C1_bit.U1LCH = 0;	// Data Logic Select Bit 0: Not inversed / 1: Inverse

//	U1C1_bit.U1ERE = 0;	//

    UCON_bit.U1IRS	= 0;
    UCON_bit.U1RRM	= 0;
    UCON_bit.CLKMD0	= 0;
    UCON_bit.CLKMD1	= 0;
//    UCON_bit.RCSP	= 0;

	S1RIC = 1;//PRIORITY_UART1;
#endif
}

//-----------------------------------------------------------------------------------	
#ifdef RENESAS_USE_UART_0
	#pragma vector=UART0_RX
#else
	#pragma vector=UART1_RX
#endif
__interrupt void Uart485_RxInt(void)
{
	usint buf;

//	__enable_interrupt();

	buf = UxRB;

	if (Uart485.RxSize < UART485_RxBufferSize && !(buf&0x8000)) {
		Uart485.RxBuf[Uart485.RxPut] = buf & 0xff;
		Uart485.RxPut++;
		Uart485.RxPut &= UART485_RxBufferMask;
		Uart485.RxSize++;
	}

	upc_RXHandler();
}

//-----------------------------------------------------------------------------------
void upc_tx_byte(u8 byte)
{
	while (!(UxC1_TI))
		adm_wd_reset();

	UxTB = (u16)(byte&0xff);
}

//-----------------------------------------------------------------------------------
u8 upc_rx_byte()
{
	return (u8)recchar();
}

//-----------------------------------------------------------------------------------
u8 upc_check_tx()
{
	if (UxC1_TI) return 1;
	return 0;
}

//-----------------------------------------------------------------------------------
void upc_clear_tx_flag()
{
}

//-----------------------------------------------------------------------------------
u8 con_check_rx()
{
	if (Uart485.RxSize) return 1;
	return 0;
}

//-----------------------------------------------------------------------------------
s16 recchar()
{
	u8 c;

	if (!Uart485.RxSize) return -1;
	c = Uart485.RxBuf[Uart485.RxGet];
	Uart485.RxGet++;
	Uart485.RxGet &= UART485_RxBufferMask;
	Uart485.RxSize--;
	return c;
}

//-----------------------------------------------------------------------------------
void rx_mode()
{
#ifdef RENESAS_USE_UART_0
	P6_bit.P6_5 = 0;
#endif
}

//-----------------------------------------------------------------------------------
void tx_mode()
{
#ifdef RENESAS_USE_UART_0
	P6_bit.P6_5 = 1;
#endif
}
*/

//-----------------------------------------------------------------------------------
// RS485 section
//-----------------------------------------------------------------------------------
//#define UART485_USE_RX_BUF

//--------------------------------------------------------------------------
#ifdef UART485_USE_RX_BUF

#define UART485_RxBufferSize 128
#define UART485_RxBufferMask (UART485_RxBufferSize - 1)
#if (UART485_RxBufferSize & UART485_RxBufferMask)
#error RX buffer size is not a power of 2
#endif

//--------------------------------------------------------------------------
typedef struct {
//  unsigned char Tmp;
  unsigned char RxBuf[UART485_RxBufferSize];
  unsigned char RxPut;
  unsigned char RxGet;
  unsigned char RxSize;
} UART485;

UART485	Uart485;

#endif

//-----------------------------------------------------------------------------------
void tx_mode()
{
	P6_bit.P6_5 = 1;
}

//-----------------------------------------------------------------------------------
void rx_mode()
{
	P6_bit.P6_5 = 0;
}

//-----------------------------------------------------------------------------------
void upc_hardware_init(u32 baund)
{
#ifdef UART485_USE_RX_BUF
	memset(&Uart485, 0, sizeof(Uart485));
#endif

	// --- pin settings ----------------------------------------
	// TXD0 out
	PD6_bit.PD6_3 = 1;

	// RXD0 in
	PD6_bit.PD6_2 = 0;

	// nRx/Tx select
	PD6_bit.PD6_5 = 1;

	//--- Special Mode Registers -------------------------------
	U0SMR  = 0;
	U0SMR2 = 0;
	U0SMR3 = 0;
	U0SMR4 = 0;

	//--- Baud Rate Register -----------------------------------
	U0BRG = (F1_CLOCK / (baund * 16)) - 1;

	//--- Transmit/Receive Mode Register -----------------------
	U0MR_bit.SMD0 = 1;	// mode UART 8bit
	U0MR_bit.SMD1 = 0;
	U0MR_bit.SMD2 = 1;

	U0MR_bit.CKDIR = 0;	// internal clock

	U0MR_bit.STPS = 0;	// 1 stop bit

//	U0MR_bit.PRY = 0;	// 0 : Odd parity / 1 : Even parity
	U0MR_bit.PRYE = 0;	// disable parity

	U0MR_bit.IOPOL = 0;	// not inversed

	//--- Transmit/Receive Control Register 0 ------------------
	U0C0_bit.CLK0 = 0;	// 0 1: Selects f1
	U0C0_bit.CLK1 = 0;

//	U0C0_bit.CRS = 0;	// 0 : Selects CTS function / 1 : Selects RTS function
	U0C0_bit.CRD = 1;	// Disables CTS/RTS function

	U0C0_bit.NCH = 0;	// 0 : TxDi/SDAi and SCLi are ports for the CMOS output

	U0C0_bit.CKPOL = 0;	// 0 : tx on the falling edge rx on the rising edge

	U0C0_bit.UFORM = 0;	// 0 : LSB first / 1 : MSB first

	//--- Transmit/Receive Control Register 1 ------------------
	U0C1_bit.TE = 1;	// Transmit enable
	U0C1_bit.TI = 0;	//

	U0C1_bit.RE = 1;	// Receive enable

//	U0C1_bit.U0RRM = 0;

	U0C1_bit.U0LCH = 0;	// Data Logic Select Bit 0: Not inversed / 1: Inverse

//	U0C1_bit.U0ERE = 0;	//

    UCON_bit.U0IRS	= 0;
    UCON_bit.U0RRM	= 0;
    UCON_bit.CLKMD0	= 0;
    UCON_bit.CLKMD1	= 0;
    UCON_bit.RCSP	= 0;

	S0RIC = 2;
}

//-----------------------------------------------------------------------------------	
#pragma vector=UART0_RX
__interrupt void Uart485_RxInt(void)
{
//	__disable_interrupt();
#ifdef UART485_USE_RX_BUF
	usint buf;

//	__enable_interrupt();

	buf = U0RB;

	if (Uart485.RxSize < UART485_RxBufferSize) {// && !(buf&0x8000)) {
		Uart485.RxBuf[Uart485.RxPut] = buf & 0xff;
		Uart485.RxPut++;
		Uart485.RxPut &= UART485_RxBufferMask;
		Uart485.RxSize++;
	}
#endif
	upc_RXHandler();
}

//-----------------------------------------------------------------------------------	
void upc_tx_byte(u8 byte)
{
	while (!(U0C1_bit.TI))
		adm_wd_reset();
	U0TB = (u16)(byte&0xff);
}

//-----------------------------------------------------------------------------------
u8 upc_rx_byte()
{
#ifdef UART485_USE_RX_BUF
	u8 c;

	if (!Uart485.RxSize) return 0;
	c = Uart485.RxBuf[Uart485.RxGet];
	Uart485.RxGet++;
	Uart485.RxGet &= UART485_RxBufferMask;
	Uart485.RxSize--;
	return c;
#else
	return U0RB & 0xff;
#endif
}

//-----------------------------------------------------------------------------------
u8 upc_check_rx(void)
{
#ifdef UART485_USE_RX_BUF
	return Uart485.RxSize;
#else
	if (U0C1_bit.RI) return 1;
	return 0;
#endif
}

//-----------------------------------------------------------------------------------
u8 upc_check_tx()
{
	if (U0C1_bit.TI) return 1;
	return 0;
}

//-----------------------------------------------------------------------------------
u8 upc_check_tx_complite()
{
	if (U0C0_bit.TXEPT) return 1;
	return 0;
}

//-----------------------------------------------------------------------------------
void upc_clear_tx_flag()
{
//	UCSR1A|=(1<<TXC1);
}

//-----------------------------------------------------------------------------------
void flash_reenable_page(void)
{
}

//-----------------------------------------------------------------------------------
void enable_interrupt()
{
	__enable_interrupt();
}

//-----------------------------------------------------------------------------------
void no_operation()
{
	__no_operation();
}

//-----------------------------------------------------------------------------------
void adm_init()
{
#ifdef USE_WATCHDOG
	WDC = 0x80;

	PRCR_bit.PRC1 = 1;	// enable write to PM

	PM1_bit.PM12 = 1;	// reset when the watchdog timer underflows
	PM2_bit.PM22 = 0;	// WDT Count Source: 0:CPU clock 1:On-chip oscillator

	PRCR_bit.PRC1 = 0;	// disable write

	WDC = 0x80;
#endif
}

//-----------------------------------------------------------------------------------
void adm_wd_reset()
{
#ifdef USE_WATCHDOG
	WDTS = 0;
#endif
}
/*
//-----------------------------------------------------------------------------------
void reset()
{
	u32 adr;

	adr = *((u32 *)0x000C0020UL);
	adr &= 0x00FFFFFFUL;

	__disable_interrupt();

	((void (*)())adr)();

//	PRCR_bit.PRC1 = 1; // enable write to PM

//	PM0_bit.PM03  = 1; // software reset

//	PRCR_bit.PRC1 = 0; // disable write to PM
}
*/
//-----------------------------------------------------------------------------------
void beep_init()
{
}

//-----------------------------------------------------------------------------------
void beep_on()
{
}

//-----------------------------------------------------------------------------------
void beep_off()
{
}

//-----------------------------------------------------------------------------------
void panel_hardware_init()
{
	//--- init Voltage Detection Register (VCR2) --------------
	PRCR_bit.PRC3 = 1;	// enable write

	VCR2 = 0xC0;

	PRCR_bit.PRC3 = 0;	// disable write

	//--- init system clock control register (CM1) ------------
	PRCR_bit.PRC0 = 1;	// enable write

	CM1_bit.CM10 = 0;	// all clock oscillates
	CM1_bit.CM11 = 0;	// use PLL clock

	CM1_bit.CM16 = 0;	// Main Clock Division: 1
	CM1_bit.CM17 = 0;	//

	PRCR_bit.PRC0 = 0;	// disable write

	//--- init system clock control register (CM2) ------------
	PRCR_bit.PRC0 = 1;	// enable write

	CM2_bit.CM20 = 0;	// oscillation stop detect function

	PRCR_bit.PRC0 = 0;	// disable write

	//--- init system clock control register (CM0) ------------
	PRCR_bit.PRC0 = 1;	// enable write to

	CM0_bit.CM00 = 0;	// CLKout mode f8
	CM0_bit.CM01 = 1;

	CM0_bit.CM02 = 0;	// no stop in WAIT mode

//	CM0_bit.CM03 = 1;	// Xcin - Xcout drive high
	CM0_bit.CM04 = 0;	// Xc work as IO port

	CM0_bit.CM05 = 0;	// main clock run

	CM0_bit.CM06 = 0;	// Main Clock Division: CM16 and CM17 enabled

	CM0_bit.CM07 = 0;	// System Clock Select Bit: Main clock

	PRCR_bit.PRC0 = 0;	// disable write

	//--- init processor mode (PM2) ---------------------------
//	PRCR_bit.PRC1 = 1;	// enable write to PM

//	PM2_bit.PM22 = 0;	// WDT Count Source: 1:On-chip oscillator

//	PRCR_bit.PRC1 = 0;	// disable write

	//--- Peripheral Clock Select Register (PCLKR) ------------
	PRCR_bit.PRC0 = 1;	// enable write to

	PCLKR = 0x03;
//	PCLKR_bit.PCLK0 = 1;// Timers A, B Clock Select Bit: f1
//	PCLKR_bit.PCLK1 = 1;// SI/O Clock Select Bit: f1SIO

	PRCR_bit.PRC0 = 0;	// disable write
}

//-----------------------------------------------------------------------------------
void led_toggle()
{
}

//-----------------------------------------------------------------------------------
void led_on()
{
}

//-----------------------------------------------------------------------------------
void led_off()
{
}

//-----------------------------------------------------------------------------------
u8 read_addr_pins()
{
	PanelAddress = PANEL_ADR;
	m_Address = PanelAddress;//PANEL_ADR;

	return 0;
}

//-----------------------------------------------------------------------------------
void start_main()
{
	u32 adr;

	adr = *((u32 *)0x000C0020UL);
	adr &= 0x00FFFFFFUL;

	__disable_interrupt();
//	__set_interrupt_level(7);

	((void (*)())adr)();
}

//-----------------------------------------------------------------------------------
void start_boot()
{
	PRCR_bit.PRC1 = 1; // enable write to PM

	PM0_bit.PM03  = 1; // software reset

	PRCR_bit.PRC1 = 0; // disable write to PM
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
#define UART1_RxBufferSize 128
#define UART1_RxBufferMask (UART1_RxBufferSize - 1)
#if (UART1_RxBufferSize & UART1_RxBufferMask)
#error RX buffer size is not a power of 2
#endif

//--------------------------------------------------------------------------
typedef struct {
//  unsigned char Tmp;
  unsigned char RxBuf[UART1_RxBufferSize];
  unsigned char RxPut;
  unsigned char RxGet;
  unsigned char RxSize;
} UART1;

UART1	Uart1;

//--------------------------------------------------------------------------
//
//----------------------------------
#pragma vector=UART1_RX
__interrupt void Uart1_RxInt(void)
{
	u16 buf;

	buf = U1RB;

	if (Uart1.RxSize < UART1_RxBufferSize) {// && !(buf&0x8000)) {
		Uart1.RxBuf[Uart1.RxPut] = buf & 0xff;
		Uart1.RxPut++;
		Uart1.RxPut &= UART1_RxBufferMask;
		Uart1.RxSize++;
	}
}

//--------------------------------------------------------------------------
//
//----------------------------------
void Uart1_Init(u32 baud)
{
	memset(&Uart1, 0, sizeof(Uart1));

	// TXD1 out
	PD6_bit.PD6_7 = 1;

	// RXD1 in
	PD6_bit.PD6_6 = 0;

	//--- Special Mode Registers -------------------------------
	U1SMR  = 0;
	U1SMR2 = 0;
	U1SMR3 = 0;
	U1SMR4 = 0;

	//--- Baud Rate Register -----------------------------------
	U1BRG = (F1_CLOCK / (baud * 16)) - 1;

	//--- Transmit/Receive Mode Register -----------------------
	U1MR_bit.SMD0 = 1;	// mode UART 8bit
	U1MR_bit.SMD1 = 0;
	U1MR_bit.SMD2 = 1;

	U1MR_bit.CKDIR = 0;	// internal clock

	U1MR_bit.STPS = 0;	// 1 stop bit

//	U1MR_bit.PRY = 0;	// 0 : Odd parity / 1 : Even parity
	U1MR_bit.PRYE = 0;	// disable parity

	U1MR_bit.IOPOL = 0;	// not inversed

	//--- Transmit/Receive Control Register 0 ------------------
	U1C0_bit.CLK0 = 0;	// 0 1: Selects f8
	U1C0_bit.CLK1 = 0;

//	U1C0_bit.CRS = 0;	// 0 : Selects CTS function / 1 : Selects RTS function
	U1C0_bit.CRD = 1;	// Disables CTS/RTS function

	U1C0_bit.NCH = 0;	// 0 : TxDi/SDAi and SCLi are ports for the CMOS output

	U1C0_bit.CKPOL = 0;	// 0 : tx on the falling edge rx on the rising edge

	U1C0_bit.UFORM = 0;	// 0 : LSB first / 1 : MSB first

	//--- Transmit/Receive Control Register 1 ------------------
	U1C1_bit.TE = 1;	// Transmit enable
	U1C1_bit.TI = 0;	//

	U1C1_bit.RE = 1;	// Receive enable

//	U1C1_bit.U1RRM = 0;

	U1C1_bit.U1LCH = 0;	// Data Logic Select Bit 0: Not inversed / 1: Inverse

//	U1C1_bit.U1ERE = 0;	//

    UCON_bit.U1IRS	= 0;
    UCON_bit.U1RRM	= 0;
    UCON_bit.CLKMD0	= 0;
    UCON_bit.CLKMD1	= 0;
//    UCON_bit.RCSP	= 0;

	S1RIC = 1;//PRIORITY_UART1;
}

//--------------------------------------------------------------------------
//
//----------------------------------
//int Uart1_PutChar(sint c)
int putchar(int c)
{
//  while (!(U1C0_bit.TXEPT));
  while (!(U1C1_bit.TI));
  U1TB = (usint)(c&0xff);
  return c;
}

//--------------------------------------------------------------------------
//
//----------------------------------
//int Uart1_GetChar(void)
/*
int getchar(coid)
{
  unsigned char c;

  if (!Uart1.RxSize) return -1;
  c = Uart1.RxBuf[Uart1.RxGet];
  Uart1.RxGet++;
  Uart1.RxGet &= UART1_RxBufferMask;
  Uart1.RxSize--;
  return c;
}
*/
