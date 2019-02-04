//-----------------------------------------------------------------------------------
#ifndef __MENU
#define __MENU
//-----------------------------------------------------------------------------------
#include "..\..\..\System\Misc\types.h"
//#include "menu_program.h"
//#include "menu_analog_in.h"
//#include "menu_digital_out.h"
//#include "menu_digital_in.h"
//#include "menu_analog_out.h"
//-----------------------------------------------------------------------------------
#define OPERATION_MODES_NUM		5
#define ERRORS_NUM				5
#define PID_PARAMETERS_NUM		9
//-----------------------------------------------------------------------------------
#define KEYS_TIME			40
#define KEYS_REPEAT_TIME0	800
#define KEYS_REPEAT_TIME1	200
#define MAX_BUZZER_TIME		5
//-----------------------------------------------------------------------------------
#define WORD_LEN	16
typedef struct
{
	u8	str[WORD_LEN];
	u8	lvl;	
}TMenuRecodr;
extern TMenuRecodr in_flash* menu_str;
//-----------------------------------------------------------------------------------
#define NEW_WORD_LEN	40
#define NEW_LANG_MAX	2
#define ALL_RECORDS_NUM 83
eu8 LCD_Cur_Pos;
typedef struct
{
	u8	str[NEW_LANG_MAX][NEW_WORD_LEN];
	u8	lvl;	
	u8 	special;
	void (* Routine)();
	s8	UpItem;	
	s8	SubItem;
	s8	PreviosItem;			
	s8	NextItem;	
}TNewMenuRecord;
extern TNewMenuRecord in_flash* new_menu_str;
extern in_flash TNewMenuRecord	Menu[ALL_RECORDS_NUM];
extern u8 Menu_Pos;
//-----------------------------------------------------------------------------------
typedef struct
{
//	__farflash u8* Word;
	u8 			Flag;
	void (* Routine)();		
	void* 		UpItem;	
	void* 		SubItem;
	void* 		PreviosItem;			
	void* 		NextItem;	
}TLCDMenuItem;
//__farflash eu8 Slovar[Slovar_Len][Slovar_Word_Len];
extern TLCDMenuItem _LCD_Root;
//-----------------------------------------------------------------------------------
extern in_flash u8	eng_mode_of_operation_str[OPERATION_MODES_NUM][8];
extern in_flash u8	eng_mode_of_operation_str_full[OPERATION_MODES_NUM][16];
extern in_flash u8	eng_mode_of_controller_str[3][8];
extern in_flash u8	eng_errors_str[ERRORS_NUM][32];
//extern __farflash u8	eng_pid_params_full[PID_PARAMETERS_NUM][20];


extern in_flash u8	ru_mode_of_operation_str[OPERATION_MODES_NUM][8];
extern in_flash u8	ru_mode_of_operation_str_full[OPERATION_MODES_NUM][16];
extern in_flash u8	ru_mode_of_controller_str[3][8];
extern in_flash u8	ru_errors_str[ERRORS_NUM][32];
//extern __farflash u8	ru_pid_params_full[PID_PARAMETERS_NUM][20];
//-----------------------------------------------------------------------------------
evu8 Key0_Time;
evu8 Key1_Time;
evu8 Key2_Time;
evu8 Key3_Time;
evu16 Key_Repeat_Time;
evu8 key0;
evu8 key1;
evu8 key2;
evu8 key3;
eu16 pos;
eu16 edit_pos;
eu8 lcd_txt[32];
eu8 menu_stat;
eu8 current_pid;
eu8 pass_match;
eu8 password_lvl;
//-----------------------------------------------------------------------------------
extern TLCDMenuItem _LCD_Root;
extern TLCDMenuItem*	LCDMenuPtr;
extern TLCDMenuItem*	Previos_LCDMenuPtr;
eu8 newmenuitem;
//extern TMenuRegisters MenuRegs;
//-----------------------------------------------------------------------------------
void menu_init();
void keys_handler();
void keys_menu();
// menu lcd
void lcd_menu_show_info_full();
//void lcd_menu_show_info_limited();
void lcd_menu_choose_mode();
//-----------------------------------------------------------------------------------
void rp_simple_action();
void rp_simple_show();
void rp_text();
//-----------------------------------------------------------------------------------
void lcd_menu_program();
void lcd_menu_edit_program_options();
void lcd_menu_program_run();
void lcd_menu_program_list();
void lcd_menu_program_debug();
void lcd_menu_program_list_show();
void lcd_menu_program_debug_show();
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void lcd_menu_show_digital_out();
void lcd_menu_edit_digital_out();
void lcd_menu_digital_out();
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void lcd_menu_show_digital_in();
void lcd_menu_digital_in();
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void lcd_menu_show_analog_out();
void lcd_menu_analog_out();
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void lcd_menu_show_analog_in();
void lcd_menu_analog_in();
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void lcd_menu_pid_0();
void lcd_menu_pid_1();
void lcd_menu_pid_2();
void lcd_menu_pid_3();
//void lcd_menu_show_pid_0();
//void lcd_menu_show_pid_1();
//void lcd_menu_show_pid_2();
//void lcd_menu_show_pid_3();
void lcd_menu_show_pid_i(u8 num);
void lcd_menu_choose_pid_parameter();
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
extern TLCDMenuItem _LCD_Show_Digital_Out;
extern TLCDMenuItem _LCD_Show_Digital_In;
extern TLCDMenuItem _LCD_Show_Analog_Out;
extern TLCDMenuItem _LCD_Show_Analog_In;
extern TLCDMenuItem _LCD_Edit_Digital_Out;
extern TLCDMenuItem _LCD_Digital_Out;
extern TLCDMenuItem _LCD_Digital_In;
extern TLCDMenuItem _LCD_Analog_In;
extern TLCDMenuItem _LCD_Analog_Out;
extern TLCDMenuItem _LCD_Program;
//extern TLCDMenuItem _LCD_Edit_Program_Options;
extern TLCDMenuItem _LCD_Program_Run;
extern TLCDMenuItem _LCD_Program_List;
extern TLCDMenuItem _LCD_Program_Debug;

extern TLCDMenuItem _LCD_Pid_0;
extern TLCDMenuItem _LCD_Pid_1;
extern TLCDMenuItem _LCD_Pid_2;
extern TLCDMenuItem _LCD_Pid_3;
extern TLCDMenuItem _LCD_Show_Pid_0;
extern TLCDMenuItem _LCD_Show_Pid_1;
extern TLCDMenuItem _LCD_Show_Pid_2;
extern TLCDMenuItem _LCD_Show_Pid_3;
extern TLCDMenuItem _LCD_Choose_Mode;
extern TLCDMenuItem _LCD_Choose_Operation_Mode;
void lcd_show_operation_mode();
void lcd_menu_edit_pid_parameter();

void lcd_title_language();
void lcd_menu_choose_language();
void lcd_menu_show_errors();

void lcd_title_info();
void lcd_show_info();

void lcd_title_time();
void lcd_show_time();

void lcd_enter_password();
void lcd_menu_show_start();
//-----------------------------------------------------------------------------------
#endif
