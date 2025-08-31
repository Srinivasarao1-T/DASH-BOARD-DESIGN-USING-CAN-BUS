#include<LPC21xx.h>
#include "delays.h"

#define D 1<<15		
#define R (IOPIN0&(1<<15))
#define ERROR -1000
unsigned char ResetDS18b20(void)
{
	unsigned int  presence; 
        IODIR0 |= D;
	IOPIN0 |= D;	
	DelayUs(1);
	IOPIN0 &= ~(D);
	DelayUs(478);
	IOPIN0 |= D;
	DelayUs(54); 
	presence = IOPIN0 ; 	
	DelayUs(423);
	
	if(presence&R)
		return 1;
	else 
		return 0;
}

/**READING A BIT USING 1-WIRE PROTOCOL FROM DS18B20**/
unsigned char ReadBit(void)
{
	unsigned int B;	
	IOPIN0 &= ~(D);
	DelayUs(1);
	IOPIN0 |= D;
	IODIR0 &= ~(D);
	DelayUs(10);
	B=IOPIN0;
	IODIR0 |=D;
	if(B&R)
		return 1;
	else 
		return 0;
}
void WriteBit(unsigned char Dbit)
{
	IOPIN0 &= ~(D);
	DelayUs(1);
	if(Dbit)
		IOPIN0 |= D;
	DelayUs(58);
	IOPIN0 |= D;
	DelayUs(1);
}
unsigned char ReadByte(void)
{
	unsigned char i;
	unsigned char Din = 0;
	for (i=0;i<8;i++)
	{
		Din|=ReadBit()? 0x01<<i:Din;
		DelayUs(45); 
	}
	return(Din);
}
void WriteByte(unsigned char Dout)
{
	unsigned char i;
	for (i=0; i<8; i++)
	{	    
		WriteBit((Dout & 0x1)); 
		Dout = Dout >> 1;
		DelayUs(1);
	}
	DelayUs(98);
}

int ReadTemp(void)
{
	unsigned char n,buff[2];
	int temp;
	if(ResetDS18b20()) return ERROR;	  
    WriteByte(0xcc);   
    WriteByte(0x44); 
    while (ReadByte()==0xff); 
	if(ResetDS18b20()) return ERROR;
	WriteByte(0xcc);  
	WriteByte(0xbe);   
    for (n=0; n<2; n++) 
    {
       buff[n]=ReadByte();  
    }
	temp=buff[1];
	temp=temp<<8;
	temp=temp|buff[0];
	return(temp);
}

