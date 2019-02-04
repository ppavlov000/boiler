//------------------------------------------------------------------------------
#ifndef __PINOUT_H
#define __PINOUT_H
//------------------------------------------------------------------------------
#include "..\..\..\System\defines.h"
//------------------------------------------------------------------------------
// ADC
//------------------------------------------------------------------------------
// CS
#define CS_PORT	PORTA
#define CS_PINS	PINA
#define CS_DIR	DDRA

#define p_adc_cs	0x80
//#define p_can_cs	0x10

// SPI
#define SPI_PORT	PORTB
#define SPI_PINS	PINB
#define SPI_DIR		DDRB

#define p_spi_miso	0x08
#define p_spi_mosi	0x04
#define p_spi_clk	0x02

#define p_spi_ss	0x01

// Signal select
#define CHANNEL_PORT	PORTA
#define CHANNEL_PINS	PINA
#define CHANNEL_DIR		DDRA

#define p_ch0	0x40
#define p_ch1	0x20
#define p_ch2	0x10
//---------------------------------------------------------------------------
// RS485
//---------------------------------------------------------------------------
#define upc_port		PORTD
#define upc_port_dir	DDRD
#define upc_dir		0x10
//#define tx_mode		upc_port|=upc_dir
//#define rx_mode		upc_port&=~upc_dir
//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------
#define led_pins		PINC
#define led_port		PORTC
#define led_port_dir	DDRC
#define led_out			0x80

#define in_port_ins		PINC
#define in_port			PORTC
#define in_port_dir		DDRC
//#define p_vsence		0x01

#define p_din0			0x20
#define p_din1			0x10
#define p_din2			0x08
#define p_din3			0x04
#define p_din4			0x02
#define p_din5			0x01

//#define in_port_vsence			PINC
//#define in_port_vsence			PORTC
//#define in_port_dir_vsence		DDRC
//#define p_vsence				0x01

#define out_port_1		PORTB
#define out_port_1_dir	DDRB
#define p_dout_0		0x10
#define p_dout_1		0x20
#define p_dout_2		0x40
#define p_dout_3		0x80

#define out_port_2		PORTG
#define out_port_2_dir	DDRG
#define p_dout_4		0x08

#define out_port_3		PORTE
#define out_port_3_dir	DDRE
#define p_dout_5		0x08
#define p_dout_6		0x10

#define aout_port		PORTE
#define aout_port_dir	DDRE
//#define p_aout0			0x08
//#define p_aout1			0x10
#define p_buzzer		0x80


#define key_port		PORTA
#define key_pins		PINA
#define key_port_dir	DDRA
#define p_key0			0x02
#define p_key1			0x01
#define p_key2			0x08
#define p_key3			0x04

//#define	io_port		PORTC
//#define	io_pins		PINC
//#define	io_ddr		DDRC

#define io_shock	0x02
#define shock_on	PORTA|=io_shock
#define shock_off	PORTA&=~io_shock

#define lcd_data_port	PORTF
#define lcd_data_pins	PINF
#define lcd_data_dir	DDRF

// Pins
#define	b_ld	0x04	
#define	b_rw	0x20
#define	b_en	0x04

// Macros
#define ld_on	PORTG|=b_ld
#define ld_off	PORTG&=~b_ld
#define rw_on	PORTE|=b_rw
#define rw_off	PORTE&=~b_rw
#define en_on	PORTE|=b_en
#define en_off	PORTE&=~b_en

#define ld_out	DDRG|=b_ld
#define rw_out	DDRE|=b_rw
#define en_out	DDRE|=b_en
//------------------------------------------------------------------------------
#endif
