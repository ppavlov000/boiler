#ifndef __FUNCTIONS
#define __FUNCTIONS
//--------------------------------------------------------------------------------------------------------
#include "..\..\..\System\Misc\types.h"
#include "..\..\..\System\defines.h"
//--------------------------------------------------------------------------------------------------------
// Timer
void Timer_Init();
// EEprom
void EEPut(u8 *Data,u16 Addr,u8 Len);
void EEGet(u8 *Data,u16 Addr,u8 Len);
// Flash
void FGet(u32 Addr,u8 *Data,u16 Len);
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

void hardware_init();
void reset();
void watchdog_reset();
void watchdog_init();
void enable_interrupt();
void power_init();
void power_on();
void power_off();
void led_on();
void led_off();
void led_out();
u8 led_check();

void beep_on();
void beep_off();
void beep_init();
void set_backlight_pwm(u16 pwm_value);

//void tx_mode();
//void rx_mode();
void upc_hardware_init(u32 baund);
void upc_tx_byte(u8 byte);
u8 upc_rx_byte();
u8 upc_check_tx();
void upc_Set_Channel(u8 channel);
void tx_mode();
void rx_mode();

void upc_clear_tx_flag();
void io_hardware_init();
void no_operation();

void atmel_hardware_init();
void led_toggle();
void enable_interrupt();
void disable_interrupt();

void adc_hardware_init();
void adc_set_channel(u8 ch);
s16 adc_conversion();

void menu_hardware_init();
u8 menu_is_button_0_pressed();
u8 menu_is_button_1_pressed();
u8 menu_is_button_2_pressed();
u8 menu_is_button_3_pressed();
//--------------------------------------------------------------------------------------------------------
#endif
