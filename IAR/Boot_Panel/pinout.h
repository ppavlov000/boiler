#ifndef __PINOUT
#define __PINOUT
//-----------------------------------------------------------------------------------
#include "Include\types.h"
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
#define	spi_port	PORTB
#define	spi_pins	PINB
#define	spi_dir		DDRB

#define spi_miso	0x08
#define spi_mosi	0x04
#define spi_sck		0x02
#define spi_ss		0x01
//-----------------------------------------------------------------------------------
#define	io_port		PORTC
#define	io_pins		PINC
#define	io_ddr		DDRC

#define io_valve1	0x20
#define io_valve2	0x40
#define io_valve3	0x80
#define io_relay1	0x08
#define io_relay2	0x10
#define io_io1		0x04
#define io_io2		0x02

#define led0_out	DDRC|=0x01
#define led0_in		DDRC&=~0x01
#define led0_on		PORTC|=0x01
#define led0_off	PORTC&=~0x01

#define led1_out	DDRG|=0x02
#define led1_in		DDRG&=~0x02
#define led1_on		PORTG|=0x02
#define led1_off	PORTG&=~0x02

#define buz_out		DDRG|=0x01
#define buz_in		DDRG&=~0x01
#define buz_on		PORTG|=0x01
#define buz_off		PORTG&=~0x01

#define io_shock	0x02
#define shock_on	PORTA|=io_shock
#define shock_off	PORTA&=~io_shock
//-----------------------------------------------------------------------------------
#define ADM706_PORT PORTB
#define ADM706_DIR 	DDRB
#define ADM706_PINS PINB

#define adm_wd 		0x10
/*
#define adm_init		ADM706_PORT&=~adm_wd;ADM706_DIR|=adm_wd
#define adm_wd_reset	ADM706_PORT|=adm_wd; __no_operation(); ADM706_PORT&=~adm_wd

#define watchdog_reset	adm_wd_reset;__watchdog_reset()
*/
//-----------------------------------------------------------------------------------
#define	addr_port		PORTC
#define	addr_pins		PINC
#define	addr_dir		DDRC

#define addr_pin0		0x01
#define addr_allpins	0xff
//-----------------------------------------------------------------------------------
#define	beep_port		PORTG
#define	beep_pins		PING
#define	beep_dir		DDRG

#define beep_p			0x01
/*
#define beep_init		beep_port&=~beep_p;beep_dir|=beep_p
#define beep_on			beep_port|=beep_p;
#define beep_off		beep_port&=~beep_p;
*/
//---------------------------------------------------------------------------
#define upc_port		PORTD
#define upc_port_dir	DDRD
#define upc_dir			0x10
//#define tx_mode			upc_port|=upc_dir
//#define rx_mode			upc_port&=~upc_dir

//-----------------------------------------------------------------------------------
/* LCD Data Bus Pins */
#define LCD_DATA_BUS_IN     PINF
#define LCD_DATA_BUS_OUT    PORTF
#define LCD_DATA_BUS_TRIS   DDRF

/* LCD Control Pins */
#define LCD_CONTROL         PORTE
#define LCD_CONTROL_TRIS    DDRE
#define LCD_WR_BIT          0x10
#define LCD_RD_BIT          0x20
#define LCD_CE_BIT          0x40
#define LCD_CD_BIT          0x80
#define LCD_RST_BIT         0x04

#define LCD_WR              0x10//(1<<LCD_WR_BIT)
#define LCD_RD              0x20//(1<<LCD_RD_BIT)

#define LCD_CE				0x00
#define LCD_CE_ALT			0x40
#define LCD_BL              0x08//(1<<LCD_CE_BIT)
#define LCD_CD              0x80//(1<<LCD_CD_BIT)
#define LCD_RST             0x04//(1<<LCD_RST_BIT)
//-----------------------------------------------------------------------------------
#endif
