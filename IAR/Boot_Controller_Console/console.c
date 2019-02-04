#include "main.h"
#include "spm.h"
//-----------------------------------------------------------------------------------
/* Set baud rate */
#define baud 17//5;//35;//71;//9600//35;//19200//5;//115200
//-----------------------------------------------------------------------------------
#define  slovar_len   7
char  slovar[slovar_len][20]=
      { 
        "test",       //0
        "download",   //1
        "atmel",      //2
        "user",    //3                
        "reset",      //4
        "protect",    //5
        "version",    //6
      };
char in;
u16 con_st; // Console command state
u8 ESC=0;
u32 MAddr,MData;
//u16 wtmp;
//u8  ctmp;
//double dtmp;
//-----------------------------------------------------------------------------------
void con_init()
{
  UBRR0H = (unsigned char)(baud>>8);
  UBRR0L = (unsigned char)baud;
  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
  UDR0=' ';  
  outptr=&outtxt[0];
  outtxt[0]=0;  
  word[0]=0;
  wordptr=&word[0];  
  inptr=&intxt[0];
  intxt[0]=0;
  //oldtxt[0]=0;  
  con_st=con_None;
}
//-----------------------------------------------------------------------------------
void con_handle()
{
  // Check tx
  if(UCSR0A & (1<<TXC0))
  {
    if(*outptr!=0)  
    {
//      Delay(1);
      UCSR0A|=(1<<TXC0);
      UDR0=*outptr;
      outptr++;
    }
    else
    {
      outptr=&outtxt[0];
      outtxt[0]=0;  
    }
  }
  // Check rx
  if(UCSR0A & (1<<RXC0))  
  {
    in=UDR0;
    if(outtxt[0]==0) // If outbuff is empty, no out any text
    {
      switch(in)
      {
        case 0x08:
          if(inptr!=&intxt[0])
          {
            sendchar(0x08);        
            sendchar(' ');                  
            sendchar(0x08);                  
            inptr--;          
            *inptr=0;          
          }
        break;
        case 27:break;
        case 0x0d:
        case '?':
          sendchar(in);        
          *inptr=in;
          inptr++;          
          *inptr=0;          
          con_parser();
          inptr=&intxt[0];
          intxt[0]=0;
        break;
  			default:
          sendchar(in);
          *inptr=in;
          inptr++;          
          *inptr=0;          
        break;
      } 
    }
  }
}
//-----------------------------------------------------------------------------------
void con_parser()
{
  u16 i=0;
  //intxt - line to parsing
 // strcpy(oldtxt,intxt);
  in=intxt[0];
  while(in!=0)
  {
      switch(in)
      {
        case 0x0d:
        case ' ':
        case '?':
          word_handler();
        break;
  			default:
          *wordptr=in;
          wordptr++;          
          *wordptr=0;          
  			break;
      } 
      i++;
      in=intxt[i];      
  }
//  if(i!=0)
//    oldtxt[i-1]=0;  // Erase last symbol
}
//-----------------------------------------------------------------------------------
void word_handler()
{
	char st=0;  // status 0-unrecognized command
	strlwr(word);
	strfull(word);
	switch(in)
	{
		case 13:
			//---------------------------    
			if(strcmp(word,"")==0)
  			{
  				st=1;
   	  			sprintf(outtxt,"\n\r");strcpy(outtxt,envitation);wait_con_free();
   	  			break;
	  		}
  			//---------------------------	  		
  			if(con_st==con_Down_Mod)
  			if(strcmp(word,slovar[2])==0)
  			{
				st=1;
				sprintf(outtxt,"\n\r Ready for downloading Atmel application image...");
//				spmRemoveProtection;	
				xmod_status=1;
				header=1;
				Flash_Start_Write(APPL_FLASH_START);
				Xmodem_Start();
				ctmp=XMOD_None;
				while(ctmp==XMOD_None)
				{
					ctmp=Xmodem_Processor();
				  	blink_booting();
				  	fram_watchdog_reset();
				}
//				sprintf(outtxt,"\n\r Press any key");		
				switch(ctmp)
				{
					case XMOD_Ok: Flash_End_Write();sprintf(outtxt,"\n\r Download is successful complete...\n\r");break;
					case XMOD_Error: while(recchar()==-1){fram_watchdog_reset();};sprintf(outtxt,"\n\r Download error!\n\r");break;
					case XMOD_Wrong_HW_Ver:while(recchar()==-1){fram_watchdog_reset();}; sprintf(outtxt,"\n\r Wrong HW Version! Download correct file\n\r");break;
				}
				strcpy(outtxt,envitation);wait_con_free();	
				break;
						  
  			} 
  			//---------------------------	  		
  			if(con_st==con_Down_Mod)
  			if(strcmp(word,slovar[3])==0)
  			{
  				st=1;
  	  			sprintf(outtxt,"\n\r Ready for downloading user program...");
				wait_con_free();	
//				spmRemoveProtection;		
				header=2;	
				xmod_status=2;				
				Flash_Start_Write(PLM_FLASH_START);
				Xmodem_Start();
				ctmp=XMOD_None;
				while(ctmp==XMOD_None)
				{
					ctmp=Xmodem_Processor();
				  	blink_booting();
				  	fram_watchdog_reset();
				}
//				sprintf(outtxt,"\n\r Press any key");
				switch(ctmp)
				{
					case XMOD_Ok: Flash_End_Write();sprintf(outtxt,"\n\r Download is successful complete...\n\r");break;
					case XMOD_Error:while(recchar()==-1){fram_watchdog_reset();}; sprintf(outtxt,"\n\r Download error!\n\r");break;
					case XMOD_Wrong_HW_Ver: while(recchar()==-1){fram_watchdog_reset();};sprintf(outtxt,"\n\r Wrong HW Version! Download correct file\n\r");break;
				}	
				strcpy(outtxt,envitation);wait_con_free();						  
  			}	
  			//---------------------------
  			if(strcmp(word,slovar[0])==0)
  			{
  				st=1;
  	  			sprintf(outtxt,"\n\r Test...\n\r");
//				#define	FLASH_SIZE 0x20000
//          #define	BOOT_SIZE 0x2000					
				fptr=0;
				spmWriteWord(fptr,0x5555);		
				spmProgramPage(fptr);
  	  			sprintf(outtxt,"\n\r Test complete...\n\r");strcpy(outtxt,envitation);wait_con_free();	
  	  			break;			  
  			}
 			//---------------------------
			if(strcmp(word,slovar[5])==0)
			{
				st=1;
				spmEnableFullProtection;
				sprintf(outtxt,"\n\r Full protection enabled...\n\r");  
				break;
  			}  	 			
 			//---------------------------
			if(strcmp(word,slovar[6])==0)
			{
				st=1;
				if((stat & 0x01)==0)
					show_header(HAPP_FLASH_START);
				//if((stat & 0x02)==0)
				//	show_header(HPLM_FLASH_START);
				sprintf(outtxt,"\n\r");
  			}    					
  			//---------------------------
  			if(strcmp(word,slovar[4])==0)
  			{
  				st=1;
  	  			sprintf(outtxt,"\n\r Resetting...");
				MCUCR=0X01;
        		MCUCR=0X00;
        		key=0;
				((void (*)())0x0000)();
  			}
  			//---------------------------  			
  			if(st==0)
  	  		sprintf(outtxt,"\n\r Bad command..."
									  "\n\r");strcpy(outtxt,envitation);wait_con_free();
  	break;
    case ' ':
  			//---------------------------  			    
  			if(strcmp(word,"")==0)
  			{
	  		}
  			//---------------------------	  		
  			if(strcmp(word,slovar[1])==0)
  			{
  			  st=1;
  			  con_st=con_Down_Mod;
  			  key|=0x00007700;
  			}
   	break;
    case '?':
  			if(strcmp(word,"")==0)
  			{
   	  		sprintf(outtxt,"\n\r Avaible commands..."
									  "\n\r      download atmega "
									  "\n\r      download user program "
									  "\n\r      reset"		
									  "\n\r      protect"									  
									  "\n\r");strcpy(outtxt,envitation);wait_con_free();
	  		}
  	break;
	}
	word[0]=0;
	wordptr=&word[0];
}
//-----------------------------------------------------------------------------------
void strfull(s8 *str)
{
  s8 b[40];
  s8 c[40];  
  u8 len,s=0,i;
  if(con_st<100) // This is command no argument!!!
  if(strcmp(str,"")!=0)
  {
    len=strlen(str);
    //---------------------------    
    for(i=0;i<slovar_len;i++)
    {
      memset(b,0,40);
      memcpy(b,slovar[i],len);
      if(strcmp(b,str)==0)
      {
        s++;
        strcpy(c,slovar[i]);
      }
    }
    //---------------------------
    if(s!=1)
      strcpy(str,"nocomm");    
    else
      strcpy(str,c);      
  }
}
//-----------------------------------------------------------------------------------
void wait_con_free()
{
	while(outtxt[0]!=0)
	{
/*	
  		if(UCSR0A & (1<<TXC0))
  		{
    		if(*outptr!=0)  
    		{
//      Delay(1);
      			UCSR0A|=(1<<TXC0);
      			UDR0=*outptr;
      			outptr++;
    		}
   			 else
    		{
     			 outptr=&outtxt[0];
      			outtxt[0]=0;  
    		}
		}*/
		con_handle();
	}	
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
