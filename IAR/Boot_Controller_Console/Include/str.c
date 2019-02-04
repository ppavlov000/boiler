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
/*
//-----------------------------------------------------------------------------------
void sprintf_P(u8 *out,u8 __farflash* in)
{
	u8 st=0;
//	va_list list;
//	va_start(list,in);
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
*/
//-----------------------------------------------------------------------------------
/*
s32 strtol(u8* txt,u8**endtxt,u8 digits)
{
	u8 d=0; // 0 - decimal 1-hex
	u8 s=0; // 0 -idle 1-stat 2-end
	u8 sign=0; // 0+ 1-
	u8 *p;
	s32 v=0;

	p=txt;
	if(*p=='-')
	{
		sign=1;
		p++;
	}
	while(*p!=0)
	{
		if(d==0)
		{
			if((s==0)&&((*p=='x')||(*p=='X')))
			{
				d=1;
				p++;
			}
			else
			{
				if((*p<'0')||(*p>'9'))return 0;
				v*=10;
				v+=*p-'0';
				if(v!=0)s=1;
				p++;
			}
		}
		if(d==1)
		{
			v*=16;
			s=2;
			if((*p>='0')&&(*p<='9'))
			{
				s=1;
				v+=*p-'0';
			}
			if((*p>='a')&&(*p<='f'))
			{
				s=1;
				v+=*p-'a'+10;
			}
			if((*p>='A')&&(*p<='F'))
			{
				s=1;
				v+=*p-'A'+10;
			}
			if(s==2)return 0;
				p++;
		}
	}
	if(sign==1)v=-v;
	return v;
}
*/
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
	/*
	//----------- HEX ------------
	if(format==1)
	{
		r=(u8*)val;
		r+=1;
//		*out='0';
//		out++;
//		*out='x';
//		out++;
		for(i=0;i<2;i++)
		{
			c=*r>>4;
			if(c<10)
				*out='0'+c;
			else
				*out='A'+c-10;
			out++;
			*out=0;
			c=*r & 0x0f;
			if(c<10)
				*out='0'+c;
			else
				*out='A'+c-10;
			out++;
			*out=0;
			r--;
		}
	}*/
	wait_con_free();
}
/*
//-----------------------------------------------------------------------------------
void WordToStrSigned(u8 *out,s16 *val)
{
	u8 i,p[5],pp,c,s;
	u32 d,t;
	s32 v;
	u8 *r;
	wait_con_free();
	//----------- DEC ------------
//	if(format==0)
	{
		v=*val;
		if(v<0)
		{
			v=-v;
			*out='-';
			out++;
			*out=0;			
		}		
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
*/
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
/*	
	//----------- HEX ------------
	if(format==1)
	{
		r=(u8*)val;
//		*out='0';
//		out++;
//		*out='x';
//		out++;
		c=*r>>4;
		if(c<10)
			*out='0'+c;
		else
			*out='A'+c-10;
		out++;
		*out=0;
		c=*r & 0x0f;
		if(c<10)
			*out='0'+c;
		else
			*out='A'+c-10;
		out++;
		*out=0;
	}
*/	
	wait_con_free();
}
/*
//-----------------------------------------------------------------------------------
void ByteToStrFillZero(u8 *out,u8 *val,u8 format,u8 digits,u8 fill)
{
	u8 i,p[3],pp,c,s;
	u32 v,d,t;
	u8 *r;
	wait_con_free();
	//----------- DEC ------------
	if(format==0)
	{		
		v=*val;
		if(v<10)
		{
			*out=fill;
			out++;
			*out=0;
		}
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
	//----------- HEX ------------
	if(format==1)
	{
		r=(u8*)val;
//		*out='0';
//		out++;
//		*out='x';
//		out++;
		c=*r>>4;
		if(c<10)
			*out='0'+c;
		else
			*out='A'+c-10;
		out++;
		*out=0;
		c=*r & 0x0f;
		if(c<10)
			*out='0'+c;
		else
			*out='A'+c-10;
		out++;
		*out=0;
	}
	wait_con_free();
}
//-----------------------------------------------------------------------------------
void WordToStrFillZero(u8 *out,u16 *val,u8 format,u8 digits,u8 fill,u8 sign)
{
	u8 i,p[3],pp,c,s;
	u32 d,t;
	s16 v;
//	u8 *r;
	wait_con_free();
	//----------- DEC ------------
	if(format==0)
	{		
		v=*val;
		if(v<0)
		{
			v=-v;
			*out='-';
			out++;
			*out=0;			
		}
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
void ShowTemperature(u8 *out,s16 *val)
{
	u8 i,p[5],pp,c,s;
	u32 d,t;
	s16 v;
//	u8 *r;
	wait_con_free();
	//----------- DEC ------------
//	if(format==0)
	{		
		v=*val;
		if(v<0)
		{
			v=-v;
			*out='-';
			out++;
			*out=0;			
		}
		else
		{
			*out='+';
			out++;
			*out=0;			
		}
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
		for(i=0;i<4;i++)
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
		*out='.';
		out++;
		*out=0;		
		if(p[4]!=0)s=1;
		if(s!=0)
		{
			*out='0'+p[4];
			out++;
			*out=0;
		}		
		if(s==0)
		{
			*out='0';
			out++;
			*out=0;
		}
//		*out=0xdf;
//		out++;
		*out='C';
		out++;
		*out=0;				
	}
}
//-----------------------------------------------------------------------------------
void ShowTemperatureShort(u8 *out,s16 *val)
{
	u8 i,p[5],pp,c,s;
	u32 d,t;
	s16 v;
//	u8 *r;
	wait_con_free();
	//----------- DEC ------------
//	if(format==0)
	{		
		v=*val;
		if(v<0)
		{
			v=-v;
			*out='-';
			out++;
			*out=0;			
		}
		else
		{
			*out='+';
			out++;
			*out=0;			
		}
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
		for(i=0;i<4;i++)
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
		*out='.';
		out++;
		*out=0;		
		if(p[4]!=0)s=1;
		if(s!=0)
		{
			*out='0'+p[4];
			out++;
			*out=0;
		}		
		if(s==0)
		{
			*out='0';
			out++;
			*out=0;
		}
	}
}
//-----------------------------------------------------------------------------------
void ShowPowerShort(u8 *out,s16 *val)
{
	u8 i,p[5],pp,c,s;
	u32 d,t;
	s16 v;
//	u8 *r;
	wait_con_free();
	//----------- DEC ------------
//	if(format==0)
	{		
		v=*val;
		if(v<0)
		{
			v=-v;
//			*out='-';
//			out++;
//			*out=0;			
		}
		else
		{
//			*out='+';
//			out++;
//			*out=0;			
		}
		if(v>999)v=999;
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
		for(i=0;i<4;i++)
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
		*out='.';
		out++;
		*out=0;		
		if(p[4]!=0)s=1;
		if(s!=0)
		{
			*out='0'+p[4];
			out++;
			*out=0;
		}		
		if(s==0)
		{
			*out='0';
			out++;
			*out=0;
		}
		*out='%';
		out++;
		*out=0;		
	}
}
*/
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
/*	
	//----------- HEX ------------
	if(format==1)
	{	
		r=(u8*)val;
		r+=3;
//		*out='0';
//		out++;
//		*out='x';
//		out++;
		for(i=0;i<4;i++)
		{
			c=*r>>4;
			if(c<10)
				*out='0'+c;
			else
				*out='A'+c-10;
			out++;
			*out=0;
			c=*r & 0x0f;
			if(c<10)
				*out='0'+c;
			else
				*out='A'+c-10;
			out++;
			 *out=0;
			r--;
		}
	}
*/	
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
/*
//-----------------------------------------------------------------------------------
u8 strcmp2(u8* str1,u8* str2)
{
	u8 sign=0;
	while((*str1!=0)||(*str2!=0))
	{
		if(*str1!=*str2)sign=1;
		str1++;
		str2++;
	}
	return sign;
}
//-----------------------------------------------------------------------------------
u8 strcmp3(u8* str1,u8* str2)
{
	u8 sign=0;
	while((*(__farflash u8*)str1!=0)||(*str2!=0))
	{
		if(*(__farflash u8*)str1!=*str2)sign=1;
		str1++;
		str2++;
	}
	return sign;
}
//-----------------------------------------------------------------------------------
void strcat2(u8* str1,u8* str2)
{
	while(*str1!=0)
		str1++;

	while(*(__farflash u8*)str2!=0)
	{
		*str1=*(__farflash u8*)str2;
		str1++;
		str2++;
	}
	*str1=' ';
	str1++;	
	*str1=0;	
}
//-----------------------------------------------------------------------------------
void strcpy2(u8* str1,u8* str2)
{
	while(*str2!=0)
	{
		*str1=*str2;
		str1++;
		str2++;
	}
	*str1=0;	
}
//-----------------------------------------------------------------------------------
u16 strlen2(u8* str1)
{
	u16 length=0;
	while(*str1!=0)
	{
		str1++;
		length++;
	}
	return length;
}
//-----------------------------------------------------------------------------------
void stradd(u8* str1,u8* str2)
{
	while(*str1!=0)str1++;		
	while(*str2!=0)
	{
		*str1=*str2;
		str1++;
		str2++;
	}
	*str1=0;
}
//-----------------------------------------------------------------------------------
void memset2(u8 *s,u8 c, u8 len)
{
	while(len!=0)
	{
		*s=c;
		s++;		
		len--;
	}
}
//-----------------------------------------------------------------------------------
void memcpy2(u8 *s,u8 *c, u8 len)
{
	while(len!=0)
	{
		*s=*c;
		s++;	
		c++;	
		len--;
	}
}
*/
//-----------------------------------------------------------------------------------
