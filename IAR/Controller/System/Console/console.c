#include "..\main.h"
#include "MenuItems_SET.h"
#include "MenuItems_SERVICE.h"
//------------------------------------------------------------------------------
u8 console_mode=1;	// 0-Protocol mode 1-console mode
u8 echo_enable=1;
//------------------------------------------------------------------------------
u8	itmp,itmp1,itmp2;
u8 b[Slovar_Word_Len];
u8 c[Slovar_Word_Len];	
u8 d[Slovar_Word_Len];		
//------------------------------------------------------------------------------
c8 StrBuff[Slovar_Word_Len];
u8 StrLine[40];
u8 Invitation_Str[5]={'\r','\n','>',0};
//------------------------------------------------------------------------------
in_flash TCMenuItem _Root=
{
	"","",0,	
	NULL,			
	NULL,		
	&_Set,
	NULL,	
};
//------------------------------------------------------------------------------
TCMenuItem in_flash *	MenuPtr;
TCMenuItem in_flash *	MenuPtr2;
//------------------------------------------------------------------------------
TCMenuItem in_flash*	MenuList[Menu_List_Count];
u8 MenuList_Count;
//------------------------------------------------------------------------------
u8 Last_Using=0;	// Sign
u8 Last_Commands_Ptr=0;
u8 Last_Commannds[Last_Commands_Num][80]=
{
	"",
	"",
	"",
	"",
	"",
};
//------------------------------------------------------------------------------
char in;
u16 con_st; // Console command state
u8 ESC=0;
u8 Params_Count=0;
u32 Params[5];
//------------------------------------------------------------------------------
void con_init()
{
	con_hardware_init(CONSOLE_BOUNDRATE);
	outptr=&outtxt[0];
	outtxt[0]=0;	
	word[0]=0;
	wordptr=&word[0];	
	inptr=&intxt[0];
	intxt[0]=0;
	con_st=con_None;
}
//------------------------------------------------------------------------------
void con_handle()
{
	// Check tx
	if(console_check_tx())
	{
		if(*outptr!=0)	
		{
			console_clear_tx_flag();
			console_tx_byte(*outptr);
			outptr++;
		}
		else
		{
			outptr=&outtxt[0];
			outtxt[0]=0;	
		}
	}
	// Check rx
	if(console_check_rx())	
	{
		in=console_rx_byte();
		if(outtxt[0]==0) // If outbuff is empty, no out any text
		{
			switch(in)
			{
				case 27:			
					// This is ESC sequence
					//ESC=1;
					while(!(console_check_rx()))
					{}
					in=console_rx_byte();
					while(!(console_check_rx()))
					{}
					in=console_rx_byte();
					if(echo_enable==0)break;
					// Erase current line
					while(inptr!=&intxt[0])
					{
						sendchar(0x08);
						sendchar(' ');
						sendchar(0x08);
						inptr--;					
						*inptr=0;					
					}
					// Handle ESC sequence
					switch(in)
					{
						case 0x41:
							// Up arrow
							if(Last_Using)
								if(Last_Commands_Ptr<(Last_Commands_Num-1))
									Last_Commands_Ptr++;							
							strcpy2(intxt,Last_Commannds[Last_Commands_Ptr]);
							Last_Using=1;							
						break;
						case 0x42:
							// Down arrow
							if(Last_Commands_Ptr!=0)
								Last_Commands_Ptr--;
							strcpy2(intxt,Last_Commannds[Last_Commands_Ptr]);
							Last_Using=1;							
						break;							
					}
					// Print new line
					inptr=&intxt[0];
					while(*inptr!=0)
					{
						sendchar(*inptr);
						inptr++;
					}																
				break;
				case 0x08:
					if(inptr!=&intxt[0])
					{
						if(echo_enable){
							sendchar(0x08);				
							sendchar(' ');									
							sendchar(0x08);									
						}
						inptr--;					
						*inptr=0;					
					}
				break;				
				case 0x0A:
				break;
				case 0x0D:
				case '?':
					if(echo_enable)
						sendchar(in);				
					*inptr=in;
					inptr++;					
					*inptr=0;					
					con_parser();
					inptr=&intxt[0];
					intxt[0]=0;
				break;
				case 0x09:
					in=' ';		
				default:
					if(inptr<&intxt[39]){
						if(echo_enable)
							sendchar(in);
						*inptr=in;
						inptr++;					
						*inptr=0;			
					}
				break;
			}
		}
	}
}
//------------------------------------------------------------------------------
void con_parser()
{
	u16 i=0;	
	u8 *ptr;
	MenuPtr=(TCMenuItem in_flash *)_Root.SubItem;
//	MenuPtr=_Root.SubItem;
	in=intxt[0];
	Params_Count=0;
	MenuList[MenuList_Count]=MenuPtr;
	MenuList_Count=1;
	while(in!=0)
	{
			switch(in)
			{
				case 0x0d:
				case ' ':
				case ':':				
				case '.':				
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
	//intxt - line to parsing
	Last_Commands_Ptr=0;
	Last_Using=0;
	ptr=(u8*)intxt;
	while(*ptr!=0)
	{
		if((*ptr==0x0a)||(*ptr==0x0d))
			*ptr=0;
		ptr++;
	}		
	if(strcmp2(intxt,"")!=0)	
		if(strcmp2(Last_Commannds[0],intxt)!=0)	
		{
			for(i=4;i!=0;i--)
				strcpy2(Last_Commannds[i],Last_Commannds[i-1]);
			strcpy2(Last_Commannds[0],intxt);
		}	
	StrLine[0]=0;
}
//------------------------------------------------------------------------------
void word_handler()
{
//	char st=0;	// status 0-unrecognized command
	__strlwr((c8*)word);
	strfull(word);
	switch(in)
	{
		case ' ':
		case ':':		
		case '.':		
			if(word[0]==0)break;
			while(MenuPtr!=NULL)
			{
				if(MenuPtr->Flag==0)				
				{
					// if match found then go to sublayer
					if(strcmp3((u8*)MenuPtr->Word,(u8*)word)==0)
					{
						strcat2(&StrLine[0],(u8*)MenuPtr->Word);
						// if sublayer exist go ...
						if(MenuPtr->SubItem!=NULL)
						{
							MenuPtr=(TCMenuItem in_flash*)MenuPtr->SubItem;
							break;
						}
						// finish of tree - make routine be course key Enter is folowing
						else
						{
							if(MenuPtr->Routine!=NULL)
							{
								MenuPtr->Routine();						
								__sprintf(outtxt,Invitation_Str);		
							}
							MenuPtr=NULL;			
							break;			
						}
					}
					// if no match try to check other tree
					else
					{
						// if next tree exist go to
						if(MenuPtr->NextItem!=NULL)
						{
							MenuPtr=(TCMenuItem in_flash*)MenuPtr->NextItem;
//							break;
						}
						// finish of trees
						else
						{
							MenuPtr=NULL;
							__sprintf(outtxt,"\n\r Bad command ");	
//							__sprintf(outtxt,word);								
							__sprintf(outtxt,Invitation_Str);
						}
					}
				}
				else
				{
//					__sprintf(outtxt,"\n\r Got middle");
					Params[Params_Count]=strtol(word,NULL,0);
					Params_Count++;
					// if next tree exist go to
					if(MenuPtr->SubItem!=NULL)
					{
						MenuPtr=(TCMenuItem in_flash*)MenuPtr->SubItem;
						break;
					}
					// finish of trees
					else
					{
						MenuPtr=NULL;
						__sprintf(outtxt,"\n\r Bad command");	
//						__sprintf(outtxt,word);	
						__sprintf(outtxt,Invitation_Str);
					}
				}								
			}
		break;
		case 0x0d:
			if(strcmp((c8*)word,"")==0)
				__sprintf(outtxt,Invitation_Str);			
			else
			while(MenuPtr!=NULL)
			{
				if(MenuPtr->Flag==0)				
				{
					// if match found then go to sublayer				
					if(strcmp3((u8*)MenuPtr->Word,(u8*)word)==0)
					{
//						MenuList[MenuList_Count]=MenuPtr;
//						MenuList_Count++;					
						strcat2(&StrLine[0],(u8*)MenuPtr->Word);
						// if sublayer exist then print available trees
						if(MenuPtr->SubItem!=NULL)
						{
							__sprintf(outtxt,"\n\r ");
							__sprintf(outtxt,StrLine);
							__sprintf(outtxt," : Available parameters ");
							MenuPtr2=(TCMenuItem in_flash*)MenuPtr->SubItem;
							while(MenuPtr2!=NULL)
							{
								__sprintf(outtxt,"\n\r   ");
								GetFlashStr(outtxt,(u8*)MenuPtr2->Word);
								MenuPtr2=(TCMenuItem in_flash*)MenuPtr2->SubItem;
							}
							__sprintf(outtxt,Invitation_Str);
							MenuPtr=NULL;												
						}
						// finish of tree, do final routine
						else
						{			
							MenuPtr->Routine();
							MenuPtr=NULL;	
							__sprintf(outtxt,Invitation_Str);						
						}
					}
					// if no match try to check other tree
					else
					{
						// if next tree exist go to
						if(MenuPtr->NextItem!=NULL)
						{
							MenuPtr=(TCMenuItem in_flash*)MenuPtr->NextItem;
						}
						// finish of trees
						else
						{
							MenuPtr=NULL;
							__sprintf(outtxt,"\n\r Bad command");
//							__sprintf(outtxt,word);	
							__sprintf(outtxt,Invitation_Str);
							break;
						}
					}
				}
				else
				{
					Params[Params_Count]=strtol(word,NULL,0);
					if(MenuPtr->Routine!=NULL)
					{
						MenuPtr->Routine();					
						__sprintf(outtxt,Invitation_Str);								
					}
					MenuPtr=NULL;
				}				
			}
		break;
		case '?':
				__sprintf(outtxt,"\n\r Available parameters");
				MenuPtr2=MenuPtr;
				while(MenuPtr2!=NULL)
				{
					__sprintf(outtxt,"\n\r   ");
					GetFlashStr(outtxt,(u8*)MenuPtr2->Word);
					MenuPtr2=(TCMenuItem in_flash*)MenuPtr2->NextItem;
				}
				__sprintf(outtxt,Invitation_Str);			
		break;

	}
	word[0]=0;
	wordptr=&word[0];
}
//------------------------------------------------------------------------------
void strfull(u8 *str)
{
	u8 len,s=0;
	MenuPtr2=MenuPtr;
	if(strcmp2(str,"")!=0)
	{
		len=strlen2(str);
		while(MenuPtr2!=NULL)
		{
			memset2(&b[0],0,Slovar_Word_Len);
			memset2(&d[0],0,Slovar_Word_Len);			
			GetFlashStr((u8*)&d[0],(u8*)MenuPtr2->Word);
			memcpy2(b,d,len);
			if(strcmp2(b,str)==0)
			{
				s++;
				GetFlashStr(&c[0],(u8*)MenuPtr2->Word);
			}
			MenuPtr2=(TCMenuItem in_flash*)MenuPtr2->NextItem;			
		}
		//---------------------------
		if(s==1)
			strcpy2(str,c);			
	}
}
//------------------------------------------------------------------------------
void strfull_old(u8 *str)
{
	u8 len,s=0;
	MenuPtr2=MenuPtr;
	if(strcmp2(str,"")!=0)
	{
		len=strlen2(str);
		while(MenuPtr2!=NULL)
		{
			memset2(&b[0],0,Slovar_Word_Len);
			memset2(&d[0],0,Slovar_Word_Len);			
			GetFlashStr((u8*)&d[0],(u8*)MenuPtr2->Word);
			memcpy2(b,d,len);
			if(strcmp2(b,str)==0)
			{
				s++;
				GetFlashStr(&c[0],(u8*)MenuPtr2->Word);
			}
			MenuPtr2=(TCMenuItem in_flash*)MenuPtr2->NextItem;			
		}
		//---------------------------
		if(s==1)
			strcpy2(str,c);			
	}
}
//------------------------------------------------------------------------------
void wait_con_free()
{
	while(outtxt[0]!=0)
	{
		con_handle();
	}
}
//------------------------------------------------------------------------------
void Echo_On()
{
	echo_enable=1;
	Invitation_Str[0]='\r';
}
//------------------------------------------------------------------------------
void Echo_Off()
{
	echo_enable=0;
	Invitation_Str[0]=0;
}
//------------------------------------------------------------------------------
