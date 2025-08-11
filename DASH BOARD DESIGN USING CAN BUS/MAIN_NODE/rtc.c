#include <LPC21xx.h>

#include "rtc_defines.h"
#include "types.h"
#include "lcd.h"
#include "lcd_define.h"

unsigned char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

void RTC_Init(void) 
{
	CCR = RTC_RESET;
	PREINT = PREINT_VAL;
	PREFRAC = PREFRAC_VAL;
	CCR = RTC_ENABLE|RTC_CLKRTC;
}

void GetRTCTimeInfo(s32 *hr,s32 *mi,s32 *se)
{
	*hr = HOUR;
	*mi = MIN;
	*se = SEC;
}											          

void DisplayRTCTime(u32 hr,u32 mi,u32 se)
{
	cmdLCD(0x85);
	charLCD((hr/10)+48);
	charLCD((hr%10)+48);
	charLCD(':');
	charLCD((mi/10)+48);
	charLCD((mi%10)+48);
	charLCD(':');
	charLCD((se/10)+48);
	charLCD((se%10)+48);
	
}

void GetRTCDateInfo(s32 *dt,s32 *mo,s32 *yr)
{
	*dt = DOM;
	*mo = MONTH;
	*yr = YEAR;
	
}
void DisplayRTCDate(u32 dt,u32 mo,u32 yr)
{
	cmdLCD(0x8f);
	charLCD((dt/10)+48);
	charLCD((dt%10)+48);
	charLCD('/');
	charLCD((mo/10)+48);
	charLCD((mo%10)+48);

	
	
}

void SetRTCTimeInfo(u32 hour, u32 min, u32 sec) 
{
	
	HOUR = hour;  
	MIN = min;
	SEC = sec;
}

void SetRTCDateInfo(u32 date,u32 month,u32 year)
{
	DOM = date;
	MONTH = month;
	YEAR = year;
	
}

void GetRTCDay(s32 *day)
{
	*day = DOW;
}
void DisplayRTCDay(u32 day)
{
     cmdLCD(0x80);
	 strLCD(week[day]);
}



