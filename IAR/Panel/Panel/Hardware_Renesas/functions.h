#ifndef __FUNCTIONS
#define __FUNCTIONS
//--------------------------------------------------------------------------------------------------------
#include "..\System\Misc\types.h"
#include "..\System\param.h"
//--------------------------------------------------------------------------------------------------------
// Timer
void Timer_Init();
void Delays(u16 val);
// EEprom
/*
void EEErase(void);
void EEPut(u8 *Data,u16 Addr,u8 Len);
void EEGet(u8 *Data,u16 Addr,u8 Len);
*/
void lc_store_param(TMain *data);
u8 lc_load_param(TMain *data);

// Flash
void FGet(u8 *Data,u32 Addr,u16 Len);
void GetFlashStr(u8 *word,u8* ptr);
// Console
void con_hardware_init(u32 baund);
u8 console_check_rx();
u8 console_check_tx();
void console_clear_tx_flag();
void console_tx_byte(u8 byte);
u8 console_rx_byte();
void console_wait_rx_new_byte();
void sendchar(u8 sym);
s16 recchar();

void reset();
void watchdog_reset();
void watchdog_init();
void no_operation();

void beep_on();
void beep_off();
void beep_init();
void set_backlight_pwm(u16 pwm_value);

void tx_mode();
void rx_mode();
void upc_hardware_init(u32 baund);
void upc_tx_byte(u8 byte);
u8 upc_rx_byte();
u8 upc_check_tx();
u8 upc_check_tx_complite();
void upc_clear_tx_flag();
void io_init();
void TSC_Init();
u16 TSC_Transfer(u8 control,u8 newcontrol);

void hardware_init();
u8 get_switch_state();
void toggle_led();
void enable_interrupt();
void disable_interrupt();

void lcd_write_data(unsigned char data);
unsigned char lcd_read_data(void);
void lcd_write_command(unsigned char data);
unsigned char lcd_read_status(void);
//--------------------------------------------------------------------------------------------------------
#endif
