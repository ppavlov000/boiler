//------------------------------------------------------------------------------
#ifndef __PINOUT_H
#define __PINOUT_H
//------------------------------------------------------------------------------
#include "..\..\..\System\defines.h"
//------------------------------------------------------------------------------
// ADC
//------------------------------------------------------------------------------
#define p_spi_ss	0x01

// CS
#define CS_PORT	PORTG
#define CS_PINS	PING
#define CS_DIR	DDRG

#define p_adc_cs	0x08
#define p_can_cs	0x10

// SPI
#define SPI_PORT	PORTB
#define SPI_PINS	PINB
#define SPI_DIR		DDRB

#define p_spi_miso	0x08
#define p_spi_mosi	0x04
#define p_spi_clk	0x02


// Signal select
#define CHANNEL_PORT	PORTB
#define CHANNEL_PINS	PINB
#define CHANNEL_DIR		DDRB

#define p_ch0	0x10
#define p_ch1	0x20
#define p_ch2	0x40
//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------
#define in_port_ins		PINA
#define in_port			PORTA
#define in_port_dir		DDRA
#define p_vsence		0x01
#define p_din0			0x04
#define p_din1			0x08
#define p_din2			0x10
#define p_din3			0x20

#define out_port		PORTC
#define out_port_dir	DDRC
#define p_dout_rel		0x01
#define p_dout0			0x02
#define p_dout1			0x04
#define p_dout2			0x08
#define p_dout3			0x10

#define aout_port		PORTE
#define aout_port_dir	DDRE
#define p_aout0			0x08
#define p_aout1			0x10
#define p_buzzer		0x80


#define key_port		PORTD
#define key_pins		PIND
#define key_port_dir	DDRD
#define p_key0			0x10
#define p_key1			0x20
#define p_key2			0x40
#define p_key3			0x80

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
//---------------------------------------------------------------------------
#define upc_port		PORTD
#define upc_port_dir	DDRD
#define upc_dir		0x10
//------------------------------------------------------------------------------
#endif
