#include "main.h"
#include "functions.h"
#include "pinout.h"
#include <iom128.h>
#include "inavr.h"
//-----------------------------------------------------------------------------------
void Timer_Init()
{
 	TCCR1A=0;
	TCCR1B=0x09;
	TCCR1C=0;//(1<<FOC1A);
	OCR1A=7372;  // pulses per 1ms
	TIMSK=(1<<OCIE1A);
	TCNT1=0;
	Time0=0;
	Time1=0;
	Time2=0;
 	Time3=0;
}
//-----------------------------------------------------------------------------------
#pragma vector=TIMER1_COMPA_vect
__interrupt void Timer_IRQ()
{
	Timer_1ms_IRQ();		
}
//-----------------------------------------------------------------------------------
void start_main()
{
	MCUCR=0X01;
	MCUCR=0X00;
	((void (*)())0x0000)();
}
//-----------------------------------------------------------------------------------
void start_boot()
{
	// Watchdog enable
	WDTCR = (1<<WDCE) | (1<<WDE);
	WDTCR = 0x08;
	while(1);
}
//-----------------------------------------------------------------------------------
s16 recchar()
{
  u8 temp;
  if(UCSR1A & (1<<RXC1))
  {
    temp=UDR1;
    return temp;
  }
  else
    return -1;
}
//-----------------------------------------------------------------------------------
void flash_reenable_page(void)
{
  while(SPMCSR & (1<<SPMEN));
  __DataToR0ByteToSPMCR_SPM(0,(1<<RWWSRE)|(1<<SPMEN));
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
	ADM706_PORT&=~adm_wd;
	ADM706_DIR|=adm_wd;
}
//-----------------------------------------------------------------------------------
void adm_wd_reset()
{
	ADM706_PORT|=adm_wd;
	no_operation();
	ADM706_PORT&=~adm_wd;
}
//-----------------------------------------------------------------------------------
void beep_init()
{
	beep_port&=~beep_p;
	beep_dir|=beep_p;
}
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
void panel_hardware_init()
{
	MCUCR=0X01;
	MCUCR=0X02;
	DDRE|=0x04;
	PORTE&=0x04;

	addr_dir&=~addr_allpins;
	addr_port|=addr_allpins;
	DDRB|=0x80;
}
//-----------------------------------------------------------------------------------
void led_toggle()
{
	if(PINB & 0x80)
		PORTB&=~0x80;
	else
		PORTB|=0x80;
}
//-----------------------------------------------------------------------------------
void led_on()
{
	PORTB|=0x80;
}
//-----------------------------------------------------------------------------------
void led_off()
{
	PORTB&=~0x80;
}
//-----------------------------------------------------------------------------------
u8 read_addr_pins()
{
	u8 tmp;
//	u8 i;
/*	tmp=0x01;
	for(i=0;i<5;i++)
	{
		if((addr_pins & tmp)==0)
		{
			m_Address=i+1;
			break;
		}
		tmp=tmp<<1;
	}*/
	tmp=addr_pins & addr_allpins;
	tmp=~tmp & addr_allpins;
	
	return tmp;
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
void upc_hardware_init(u32 baud)
{
	u16 rate=0;
//#define CONSOLE_RATE	115200 //5//5;//35;//71;//9600//35;//19200//5;//115200	
	switch(baud)
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

