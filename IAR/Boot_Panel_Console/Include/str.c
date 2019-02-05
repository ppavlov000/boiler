#include <string.h>
//#include "inavr.h"
#include "..\console.h"
#include "str.h"
//-----------------------------------------------------------------------------------
u8 outtxt[400],word[40],*wordptr;
u8 intxt[40],*inptr;
u8 *outptr;
//u16 con_st; // Console command state
//u8 ESC=0;
u32 ltmp;
u16	wtmp;
u8	ctmp;
d64 dtmp;
//-----------------------------------------------------------------------------------
void sprintf(u8 *out,u8 *in)
{
//return;
	u8 st=0;
	wait_con_free();
	while(*in!=0)
	{
		// new line or etc
		if(st==1)
		{
			switch(*in)
			{
				case 'n':
					*out=0x0D;
					out++;
					in++;
				break;
				case 'r':
					*out=0x0A;
					out++;
					in++;
				break;
			}
			st=0;
		}
		switch(*in)
		{
			case 92:// '\' is detected
				in++;
				st=1;
			break;
			default:
				*out=*in;
				out++;
				in++;
			break;
		}
	}
	*out=0;
	outptr=&outtxt[0];
	wait_con_free();
}

//-----------------------------------------------------------------------------------
void WordToStr(u8 *out,u16 *val,u8 format)
{
	u8 i,p[5],pp,c,s;
	u32 v,d,t;
	u8 *r;
	wait_con_free();
	//----------- DEC ------------
	if(format==0)
	{
		v=*val;
		pp=4;
		for(i=0;i<5;i++)
		{
			t=v;
			v=v/10;
			d=v*10;
			c=t-d;
			p[pp]=c;
			pp--;
		}
		s=0;
		for(i=0;i<5;i++)
		{
			if(p[i]!=0)s=1;
			if(s!=0)
			{
				*out='0'+p[i];
				out++;
				*out=0;
			}
		}
		if(s==0)
		{
			*out='0';
			out++;
			*out=0;
		}
	}
	wait_con_free();
}

//-----------------------------------------------------------------------------------
void ByteToStr(u8 *out,u8 *val,u8 format)
{
	u8 i,p[3],pp,c,s;
	u32 v,d,t;
	u8 *r;
	wait_con_free();
	//----------- DEC ------------
	if(format==0)
	{
		v=*val;
		pp=2;
		for(i=0;i<3;i++)
		{
			t=v;
			v=v/10;
			d=v*10;
			c=t-d;
			p[pp]=c;
			pp--;
		}
		s=0;
		for(i=0;i<3;i++)
		{
			if(p[i]!=0)s=1;
			if(s!=0)
			{
				*out='0'+p[i];
				out++;
				*out=0;
			}
		}
		if(s==0)
		{
			*out='0';
			out++;
			*out=0;
		}
	}
	wait_con_free();
}

//-----------------------------------------------------------------------------------
void LongToStr(u8 *out,u32 *val,u8 format)
{
	u8 i,p[10],pp,c,s;
	u32 v,d,t;
	u8 *r;
	wait_con_free();
	//----------- DEC ------------
	if(format==0)
	{
		v=*val;
		pp=9;
		for(i=0;i<10;i++)
		{
			t=v;
			v=v/10;
			d=v*10;
			c=t-d;
			p[pp]=c;
			pp--;
		}
		s=0;
		for(i=0;i<10;i++)
		{
			if(p[i]!=0)s=1;
			if(s!=0)
			{
				*out='0'+p[i];
				out++;
				*out=0;
			}
		}
		if(s==0)
		{
			*out='0';
			out++;
			*out=0;
		}
	}
	wait_con_free();
}
//-----------------------------------------------------------------------------------
void strlwr(char *str)
{
	while(*str!=0)
	{
		if((*str>=0x41)&&(*str<=0x5A))
		{
			*str=*str+0x20;
		}
		str++;
	}
}
//-----------------------------------------------------------------------------------
