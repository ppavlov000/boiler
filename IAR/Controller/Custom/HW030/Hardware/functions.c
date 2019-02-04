//-----------------------------------------------------------------------------------
#include "inavr.h"
#include <iom128.h>
#include "..\..\..\System\main.h"
//-----------------------------------------------------------------------------------
void tx_mode()
{
//	u8 i;
//	upc_port|=upc_dir;
}
//-----------------------------------------------------------------------------------
void rx_mode()
{
//	upc_port&=~upc_dir;
}
//-----------------------------------------------------------------------------------
void upc_hardware_init(u32 baund)
{
	u16 rate=0;
//#define CONSOLE_RATE	115200 //5//5;//35;//71;//9600//35;//19200//5;//115200	
	switch(baund)
	{
		case 115200: rate=5; break;
		case 57600: rate=11; break;
		case 38400: rate=17; break;
		case 28800: rate=23; break;
		case 19200: rate=35; break;
		case 14400: rate=47; break;		
		case 9600: rate=71; break;
		case 4800: rate=143; break;
		case 2400: rate=287; break;
	}
//	upc_port_dir|=(upc_dir);
//	upc_port&=~(upc_dir);
	UBRR1H = (unsigned char)(rate>>8);
	UBRR1L = (unsigned char)rate;
	/* Enable receiver and transmitter */
	UCSR1B =(1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1);
	/* Set frame format: 8data, 2stop bit */
	UCSR1C = (1<<USBS1)|(3<<UCSZ10);
	UDR1=' ';	
}
//-----------------------------------------------------------------------------------	
#pragma vector=USART1_RXC_vect
__interrupt void upc_RX_IRQ()
{
	upc_RXHandler();
}
//-----------------------------------------------------------------------------------	
void upc_tx_byte(u8 byte)
{
	UDR1=byte;
}
//-----------------------------------------------------------------------------------
u8 upc_rx_byte()
{
	u8 byte;
	byte=UDR1;
	return byte;
}
//-----------------------------------------------------------------------------------
u8 upc_check_tx()
{
	if(UCSR1A & (1<<TXC1))return 1;
	else return 0;
}
//-----------------------------------------------------------------------------------
void upc_clear_tx_flag()
{
	UCSR1A|=(1<<TXC1);
}
//-----------------------------------------------------------------------------------
// Keyboard section
//-----------------------------------------------------------------------------------
void menu_hardware_init()
{
	key_port|=(p_key0+p_key1+p_key2+p_key3);
	key_port_dir&=~(p_key0+p_key1+p_key2+p_key3);
	PORTE&=~p_buzzer;
	DDRE|=p_buzzer;
}
//-----------------------------------------------------------------------------------
u8 menu_is_button_0_pressed()
{
	if((key_pins & p_key0)!=0)
		return 1;
	else
		return 0;
}
//-----------------------------------------------------------------------------------
u8 menu_is_button_1_pressed()
{
	if((key_pins & p_key1)!=0)
		return 1;
	else
		return 0;
}
//-----------------------------------------------------------------------------------
u8 menu_is_button_2_pressed()
{
	if((key_pins & p_key2)!=0)
		return 1;
	else
		return 0;
}
//-----------------------------------------------------------------------------------
u8 menu_is_button_3_pressed()
{
	if((key_pins & p_key3)!=0)
		return 1;
	else
		return 0;
}
//-----------------------------------------------------------------------------------
// Timer section
//-----------------------------------------------------------------------------------
void Timer_Init()
{
	TCCR1A=0;
	TCCR1B=0x09;	
	TCCR1C=0;//(1<<FOC1A);
	OCR1A=11059;	// 1 pulses per 1ms	
//	OCR1A=110590;	// 1 pulses per 10ms
	TCNT1=0;
//	time=0;	
/*
	TCNT0=0;
	TCCR0=0x00;
	OCR0=0xff;

	TCNT2=0;
	TCCR2=0x05;		// divider is 1024, one step is equal 92.6mks
	OCR2=0xff;

	TIMSK=(1<<OCIE1A)+(1<<OCIE0)+(1<<OCIE2);
	ETIMSK=(1<<OCIE3A);	
*/
	TIMSK|=(1<<OCIE1A);
//	ETIMSK=(1<<OCIE3A);		
}
//-----------------------------------------------------------------------------------
#pragma vector=TIMER1_COMPA_vect
__interrupt void Timer_IRQ()
{
	Timer_1ms_IRQ();
}
//-----------------------------------------------------------------------------------
void Delays(u16 val)// value in 10mks
{
	u8 i;
	while(val!=0)
	{
		for(i=0;i<110;i++)__no_operation();
		val--;
	}
}

//-----------------------------------------------------------------------------------
// EEprom section
//-----------------------------------------------------------------------------------
void EEPut(u8 *Data,u16 Addr,u8 Len)
{
	u8 i;
	for(i=0;i<Len;i++)
	{
		__EEPUT(Addr+i,*Data);
		watchdog_reset();
		Data++;
	}
}
//-----------------------------------------------------------------------------------
void EEGet(u8 *Data,u16 Addr,u8 Len)
{
	u8 i;
	for(i=0;i<Len;i++)
	{
		__EEGET(*Data,Addr+i);
		watchdog_reset();
		Data++;
	}
}
//-----------------------------------------------------------------------------------
// Flash section
//-----------------------------------------------------------------------------------
void FGet(u32 Addr,u8 *Data,u16 Len)
{
	u8 i;
	for(i=0;i<Len;i++)
	{
		*Data=*((u8 __farflash *)Addr+i);
		Data++;
	}
}
//-----------------------------------------------------------------------------------
void GetFlashStr(u8 *word,u8* ptr)
{
	while((*(__farflash u8*)ptr)!=0)
	{
		*word=(*(__farflash u8*)ptr);
		ptr++;
		word++;
	}	
	*word=0;
}
//-----------------------------------------------------------------------------------
// Console section
//-----------------------------------------------------------------------------------
void con_hardware_init(u32 baund)
{
	u16 rate=0;
//#define CONSOLE_RATE	115200 //5//5;//35;//71;//9600//35;//19200//5;//115200	
	switch(baund)
	{
		case 115200: rate=5; break;
		case 57600: rate=11; break;
		case 38400: rate=17; break;
		case 28800: rate=23; break;
		case 19200: rate=35; break;
		case 14400: rate=47; break;		
		case 9600: rate=71; break;
		case 4800: rate=143; break;
		case 2400: rate=287; break;
	}
	UBRR0H = (unsigned char)(rate>>8);
	UBRR0L = (unsigned char)rate;
	// Enable receiver and transmitter
	UCSR0B =(1<<RXEN0)|(1<<TXEN0);
	// Set frame format: 8data, 2stop bit
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	UDR0=' ';	// This is for setting TX flag to 1 at beggining
}
//-----------------------------------------------------------------------------------
u8 console_check_rx()	// if return value is 1 then something is in a buffer
{
	if(UCSR0A & (1<<RXC0))return 1;
	else return 0;
}
//-----------------------------------------------------------------------------------
u8 console_check_tx()
{
	if(UCSR0A & (1<<TXC0))return 1;
	else return 0;
}
//-----------------------------------------------------------------------------------
void console_clear_tx_flag()
{
	UCSR0A|=(1<<TXC0);
}
//-----------------------------------------------------------------------------------
void console_tx_byte(u8 byte)
{
	UDR0=byte;
}
//-----------------------------------------------------------------------------------
u8 console_rx_byte()
{
	u8 byte;
	byte=UDR0;
	return byte;
}
//-----------------------------------------------------------------------------------
void console_wait_rx_new_byte()
{
	while(!(UCSR0A & (1<<RXC0)))
	{}
}
//-----------------------------------------------------------------------------------
void sendchar(u8 sym)
{
	outtxt[0]=sym;
	outtxt[1]=0;
	wait_con_free();
}
//-----------------------------------------------------------------------------------
s16 recchar()
{
	u8 temp;
	if(UCSR0A & (1<<RXC0))	
	{
		temp=UDR0;
		return temp;
	}
	else
		return -1;
}

//-----------------------------------------------------------------------------------
// Watchdog section
//-----------------------------------------------------------------------------------
void watchdog_init()
{
//	ADM706_PORT&=~adm_wd;
//	ADM706_DIR|=adm_wd;
	
}
//-----------------------------------------------------------------------------------
void hardware_init()
{
	MCUCR=0X01;
	MCUCR=0X00;
	// Watchdog disable
	WDTCR = (1<<WDCE) | (1<<WDE);
	WDTCR = 0x00;
	TWCR=0;
// External interrupts
//	EICRB=0x20;	// all ints - rising adge
//	EIMSK=0x40;	
}
//-----------------------------------------------------------------------------------
void reset()
{
	// Watchdog enable
	WDTCR = (1<<WDCE) | (1<<WDE);
	WDTCR = 0x08;
	while(1);
}
//-----------------------------------------------------------------------------------
void watchdog_reset()
{
	fram_watchdog_reset();
	__watchdog_reset();
}
/*
//-----------------------------------------------------------------------------------
void power_init()
{
	power_port_dir|=b_power;
}
//-----------------------------------------------------------------------------------
void power_on()
{
	power_port|=b_power;
}
//-----------------------------------------------------------------------------------
void power_off()
{
	power_port&=~b_power;
}
*/
//-----------------------------------------------------------------------------------
void led_on()
{
#ifndef __HW030	
	led_port|=led_out;
#endif
}
//-----------------------------------------------------------------------------------
void led_off()
{
#ifndef __HW030		
	led_port&=~led_out;
#endif
}
//-----------------------------------------------------------------------------------
void led_dir_out()
{
#ifndef __HW030	
	led_port_dir|=led_out;
#endif	
}
//-----------------------------------------------------------------------------------
u8 led_check()
{
#ifndef __HW030		
	if(led_pins & led_out)return 1;
#endif		
	return 0;
}
//-----------------------------------------------------------------------------------
void led_toggle()
{
#ifndef __HW030		
	if(led_pins & led_out)
		led_port&=~led_out;
	else
		led_port|=led_out;	
#endif	
}
//-----------------------------------------------------------------------------------
// Buzzer section
//-----------------------------------------------------------------------------------
void beep_on()
{
	PORTE|=p_buzzer;
}
//-----------------------------------------------------------------------------------
void beep_off()
{
	PORTE&=~p_buzzer;
}
//-----------------------------------------------------------------------------------
void beep_init()
{
//	beep_port&=~beep_p;beep_dir|=beep_p;
}
//-----------------------------------------------------------------------------------
void no_operation()
{}
//-----------------------------------------------------------------------------------
void enable_interrupt()
{
	__enable_interrupt();
}
//-----------------------------------------------------------------------------------
void disable_interrupt()
{
	__disable_interrupt();
}
//-----------------------------------------------------------------------------------
void adc_hardware_init()
{
	CS_PORT|=p_adc_cs;
	CS_DIR|=p_adc_cs;
	
	SPI_DIR|=(p_spi_mosi+p_spi_clk+p_spi_ss);
	SPI_DIR&=~(p_spi_miso);	
	SPI_PORT&=~(p_spi_miso+p_spi_mosi+p_spi_clk);		
	SPI_PORT|=(p_spi_ss);	

	CHANNEL_PORT&=~(p_ch0+p_ch1+p_ch2);		
	CHANNEL_DIR|=(p_ch0+p_ch1+p_ch2);

	SPCR=(0<<SPIE)+(1<<SPE)+(0<<DORD)+(1<<MSTR)+(0<<CPOL)+(0<<CPHA)+(2);
}
//------------------------------------------------------------------------------
void adc_set_channel(u8 ch)
{
//	u8 atmp=0;
	// Tets
	// Addr0
	if(ch & 0x01)
		CHANNEL_PORT|=p_ch0;		
	else
		CHANNEL_PORT&=~p_ch0;			
	// Addr1
	if(ch & 0x02)
		CHANNEL_PORT|=p_ch1;		
	else
		CHANNEL_PORT&=~p_ch1;	
	// Addr2
	if(ch & 0x04)
		CHANNEL_PORT|=p_ch2;	
	else
		CHANNEL_PORT&=~p_ch2;				
}
//------------------------------------------------------------------------------
s16 adc_conversion()
{
	u16 tmp;
	u8	tmp8[3];	
	f32	ftmp;
//#ifdef __NO_ADC
//	ad_res=100;
//	return;
//#endif	
	tmp=SPDR;
	tmp=SPDR;
	CS_PORT&=~p_adc_cs;
	__disable_interrupt();	
	// 1th byte
 	SPDR = 0;
//	tmp8[0]=SPDR; 	
	while ((SPSR & 0x80)==0); 	// Wait until SPI Tx empty & Rx Full	
	tmp8[0]=SPDR;
//	tmp8[0]=adc_exchange();
	// 2th byte	
 	SPDR = 0;
	while ((SPSR & 0x80)==0); 	// Wait until SPI Tx empty & Rx Full	
	tmp8[1]=SPDR;	
//	tmp8[1]=adc_exchange();
	__enable_interrupt();	

	ad_tmp32=tmp8[0];
	ad_tmp32=ad_tmp32<<8;
	ad_tmp32|=tmp8[1];

	tmp=ad_tmp32>>1;	
	tmp&=0xfff;
	
	CS_PORT|=p_adc_cs;	
	ad_res_int=tmp;
	ftmp=tmp;
	ftmp=ftmp/0x0fff;
	ftmp*=10000;
	ad_res=ftmp;	
	return ad_res;
}
//-----------------------------------------------------------------------------------
