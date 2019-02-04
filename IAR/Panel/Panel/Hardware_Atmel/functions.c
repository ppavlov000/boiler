//-----------------------------------------------------------------------------------
#include "inavr.h"
#include <iom128.h>
#include "..\System\main.h"
//-----------------------------------------------------------------------------------
// Timer section
//-----------------------------------------------------------------------------------
void Timer_Init()
{
	TCCR1A=0;
	TCCR1B=0x09;	
	TCCR1C=0;//(1<<FOC1A);
//	OCR1A=11059;	// 1 pulses per 1ms	
	OCR1A=1106;		// 10 pulses per 1ms		
//	OCR1A=110590;	// 1 pulses per 10ms
	TCNT1=0;	
	TIMSK|=(1<<OCIE1A);	
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
void FGet(u8 *Data,u32 Addr,u16 Len)
{
  u8 i;
  for(i=0;i<Len;i++)
  {
    *Data=*((u8 __farflash *)Addr+i);
    Data++;
  }
}
//-----------------------------------------------------------------------------------
void FGet_c(u32 Addr,u8 *Data,u16 Len)
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
// Watchdog section
//-----------------------------------------------------------------------------------
void watchdog_init()
{
	ADM706_PORT&=~adm_wd;
	ADM706_DIR|=adm_wd;
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
	ADM706_PORT|=adm_wd;
	__no_operation();
	ADM706_PORT&=~adm_wd;
	__watchdog_reset();
}
//-----------------------------------------------------------------------------------
// Buzzer section
//-----------------------------------------------------------------------------------
void beep_on()
{
	beep_port|=beep_p;
}
//-----------------------------------------------------------------------------------
void beep_off()
{
	beep_port&=~beep_p;
}
//-----------------------------------------------------------------------------------
void beep_init()
{
	beep_port&=~beep_p;beep_dir|=beep_p;
}
//-----------------------------------------------------------------------------------
// PWM back light section
//-----------------------------------------------------------------------------------
void set_backlight_pwm(u16 pwm_value)
{
	OCR3A=bl_100-pwm_value;
//	OCR3A=pwm_value;
}
//-----------------------------------------------------------------------------------
// RS485 section
//-----------------------------------------------------------------------------------
void tx_mode()
{
//	u8 i;
	upc_port|=upc_dir;
}
//-----------------------------------------------------------------------------------
void rx_mode()
{
	upc_port&=~upc_dir;
}
//-----------------------------------------------------------------------------------
#if __MODBUS_ENA==0
void modbus_s_init();
void modbus_s_TXHandler();
void modbus_s_RXHandler();
#endif
//-----------------------------------------------------------------------------------
void Slave_Init()
{
#if __MODBUS_ENA==0	
	upc_init();
#else
	modbus_s_init();
#endif	
}
//-----------------------------------------------------------------------------------
void Slave_TXHandler()
{
#if __MODBUS_ENA==0	
	upc_TXHandler();
#else
	modbus_s_TXHandler();
#endif	
}
//-----------------------------------------------------------------------------------
void Slave_RXHandler()
{
#if __MODBUS_ENA==0	
	upc_RXHandler();
#else
	modbus_s_RXHandler();
#endif	
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
	upc_port_dir|=(upc_dir);
	upc_port&=~(upc_dir);
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
	Slave_RXHandler();
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
// MODBUS section
//-----------------------------------------------------------------------------------	
#pragma vector=USART1_TXC_vect
__interrupt void upc_TX_IRQ()
{
#if __MODBUS_ENA==1		
	modbus_s_TXHandler();
#endif	
}
//-----------------------------------------------------------------------------------

void mod_hardware_init(u32 baund)
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
	upc_port_dir|=(upc_dir);
	upc_port&=~(upc_dir);
	UBRR1H = (unsigned char)(rate>>8);
	UBRR1L = (unsigned char)rate;
	/* Enable receiver and transmitter */
	UCSR1B =(1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1)|(1<<TXCIE1);
	/* Set frame format: 8data, 1stop bit */
	UCSR1C = (0<<USBS1)|(3<<UCSZ10);
	UDR1=' ';	
}
//-----------------------------------------------------------------------------------	
void mod_tx_byte(u8 byte)
{
	UDR1=byte;
}
//-----------------------------------------------------------------------------------
u8 mod_rx_byte()
{
	u8 byte;
	byte=UDR1;
	return byte;
}
//-----------------------------------------------------------------------------------
u8 mod_check_tx()
{
	if(UCSR1A & (1<<TXC1))return 1;
	else return 0;
}
//-----------------------------------------------------------------------------------
void mod_clear_tx_flag()
{
	UCSR1A|=(1<<TXC1);
}
//-----------------------------------------------------------------------------------
// io section
//-----------------------------------------------------------------------------------
void io_init()
{

	DDRB|=0x80;
	PORTB&=~0x80;
	DDRG|=0x02;
	PORTG&=~0x02;	

	DDRE|=0x08;
	
	TCNT3=0;	
	TCCR3A=0xc3;	
	TCCR3B=0x01;	// divider is 1024, one step is equal 92.6mks
	TCCR3C=0;//(1<<FOC1A);
//    OCR3A=m.BackLit_Value;
    OCR3B=0;	
	OCR3C=0;	

	io.num_di=6;
	io.num_do=20;
	io.num_ai=2;
	io.num_ao=4;	    	
}
//-----------------------------------------------------------------------------------
// TSK section
//-----------------------------------------------------------------------------------
void TSC_Init()
{
	DDRD&=~0x01;
	PORTD|=0x01;
	PORTD&=~0x02;	
	
	spi_dir|=spi_ss+spi_sck+spi_mosi;
	spi_dir&=~spi_miso;
	spi_port&=~(spi_sck+spi_mosi);	
	spi_port|=(spi_ss);
	
//	SPCR=(1<<SPE);	
	SPCR=(0<<SPIE)+(1<<SPE)+(0<<DORD)+(1<<MSTR)+(0<<CPOL)+(0<<CPHA)+(3);
	SPSR=1;
}
//-----------------------------------------------------------------------------------
void no_operation()
{}
//-----------------------------------------------------------------------------------
u16 TSC_Transfer(u8 control,u8 newcontrol)
{
	u8 tmp;
	u16 r;
	u16 i;

	tmp=SPDR;
	tmp=SPDR;
		
	spi_port&=~spi_ss;

	for(i=0;i<500;i++)
		no_operation();
		
	tmp=control;	
	tmp|=0x83;
	SPDR = tmp;
	while ((SPSR & 0x80)==0); 	// Wait until SPI Tx empty & Rx Full	
	tmp=SPDR;

	tmp=0;
	SPDR = tmp;
	while ((SPSR & 0x80)==0); 	// Wait until SPI Tx empty & Rx Full	
	tmp=SPDR;	
	r=tmp;

	tmp=newcontrol;	
	tmp|=0x83;
	SPDR = tmp;
	while ((SPSR & 0x80)==0); 	// Wait until SPI Tx empty & Rx Full	
	tmp=SPDR;
	r=r<<8;
	r|=tmp;
	r=r>>3;
	
	tmp=0;
	SPDR = tmp;
	while ((SPSR & 0x80)==0); 	// Wait until SPI Tx empty & Rx Full	
	tmp=SPDR;
	
	for(i=0;i<500;i++)
		no_operation();
		
	spi_port|=spi_ss;
	no_operation();
	no_operation();
	no_operation();			
	no_operation();
	
	r=r & 0x0fff;	
	return r;
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
	EICRA=0xfe;	// all ints - rising adge
	EIMSK=0x00;	

	addr_dir&=~addr_allpins;
	addr_port|=addr_allpins;
	DDRB|=0x80;	
}
//-----------------------------------------------------------------------------------
u8 get_switch_state()
{
	u8 tmp,i;
	tmp=1;
/*	for(i=0;i<5;i++)
	{
		if((PINC & tmp)==0)
		{
			m.Address=i+1;
			break;
		}
		tmp=tmp<<1;
	}*/
	tmp=addr_pins & addr_allpins;
	tmp=~tmp & addr_allpins;
	return tmp;
}
//-----------------------------------------------------------------------------------
void toggle_led()
{
	if(PINB & 0x80)
		PORTB&=~0x80;
	else
		PORTB|=0x80;	
}
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
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
#define LCD_STATUS_STD		(LCD_STATUS_BUSY1|LCD_STATUS_BUSY2)
//-----------------------------------------------------------------------------------
/********************************************
 * Function name: initialise                *
 * Description:   Initialise PIC and LCD    *
 *******************************************/
void lcd_reset(void)
{
    // Set Control Lines to outputs and High
    LCD_CONTROL =( LCD_WR | LCD_RD | LCD_CE_ALT | LCD_CD | LCD_RST);
    LCD_CONTROL_TRIS |= LCD_WR | LCD_RD | LCD_CE_ALT | LCD_CD | LCD_RST;
    LCD_DATA_BUS_TRIS = ALL_INPUTS;
    // Hold Reset Line for 1ms
//    LCD_CONTROL&=nLCD_RST;
    LCD_CONTROL|=LCD_BL;
    LCD_CONTROL&=~LCD_RST;
    Delay(10);
    LCD_CONTROL|=LCD_RST;
    Delay(10);
	LCD_CONTROL&=~LCD_CE_ALT;
}
//--------------------------------------------------------------------------
void lcd_write(u8 data)
{
	u8 i;
	LCD_DATA_BUS_TRIS = ALL_OUTPUTS;
	LCD_CONTROL&=~LCD_WR;
	LCD_DATA_BUS_OUT = data;
	for(i=0;i<3;i++)no_operation();
	LCD_CONTROL|=LCD_WR;
}
//--------------------------------------------------------------------------
u8 lcd_read(void)
{
	u8 i;
	u8 data;
	LCD_DATA_BUS_TRIS = ALL_INPUTS;
	LCD_CONTROL&=~LCD_RD;
	for(i=0;i<3;i++)no_operation();
	data = LCD_DATA_BUS_IN;
	LCD_CONTROL|=LCD_RD;
	return data;
}
//----------------------------------
u8 lcd_read_status(void)
{
	LCD_CONTROL|=LCD_CD;
	return lcd_read();
}
//-----------------------------------------------------------------------------------
uchar lcd_wait(uchar f)
{
//	ulint t;
	while ((lcd_read_status() & f) != f)
	{
		watchdog_reset();
	}
	return 1;
}
//-----------------------------------------------------------------------------------
void lcd_write_command(u8 data)
{
	lcd_wait(LCD_STATUS_STD);

	LCD_CONTROL|=LCD_CD;
	lcd_write(data);
}
//-----------------------------------------------------------------------------------
void lcd_write_data(u8 data)
{
	lcd_wait(LCD_STATUS_STD);

	LCD_CONTROL&=~LCD_CD;
	lcd_write(data);
}

//--------------------------------------------------------------------------
u8 lcd_read_data(void)
{
	lcd_wait(LCD_STATUS_STD);

	LCD_CONTROL&=~LCD_CD;
	return lcd_read();
}
//-----------------------------------------------------------------------------------
