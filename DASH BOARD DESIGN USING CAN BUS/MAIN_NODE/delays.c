void delayms(unsigned int ms_dly)
{
	unsigned int i;
	for(;ms_dly>0;ms_dly--)
		for(i=12000;i>0;i--);	   
                               
}


void DelayMS(unsigned int dly)
{
	unsigned int i;
	for(;dly>0;dly--)
	{
		for(i=0;i<1200;i++);
	}
}

void DelayUs(int us)
{
	unsigned int i,j;
	for(j=0;j<us;j++)
	for(i=0;i<10;i++);
}
void  DelayS(unsigned int  dly)
{  unsigned int  i;

   for(; dly>0; dly--) 
      for(i=12000000; i>0; i--);
}
