#ifndef __ATMEL_HARDWARE
#define __ATMEL_HARDWARE
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void Timer_Init();
void con_hardware_init();
void flash_reenable_page(void);
void enable_interrupt();
void no_operation();
void adm_init();
void adm_wd_reset();
void enable_interrupt();
void rx_mode();
void tx_mode();
void beep_init();
void beep_on();
void beep_off();

void reset();
void panel_hardware_init();
void led_toggle();
void led_on();
void led_off();
u8 read_addr_pins();

s16 recchar();
void upc_hardware_init(u32 baud);
void tx_mode();
void rx_mode();
void upc_tx_byte(u8 byte);
u8 upc_rx_byte();
u8 upc_check_tx();
void upc_clear_tx_flag();

void start_main();
void start_boot();
//-----------------------------------------------------------------------------------
#endif
