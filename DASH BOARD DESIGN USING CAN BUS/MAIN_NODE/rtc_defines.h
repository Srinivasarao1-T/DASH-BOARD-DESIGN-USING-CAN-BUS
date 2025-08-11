#ifndef _RTC_DEFINES_H
#define _RTC_DEFINES_H

// System clock and peripheral clock Macros
#define F	12000000 
#define C  (5*F)   
#define P  (C/4)

// RTC Macros
#define PREINT_VAL  (int) ((P / 32768) - 1)
#define PREFRAC_VAL (P-((PREINT + 1) * 32768))
#define RTC_ENABLE  (1<<0)
#define RTC_RESET   (1<<1)
#define	RTC_CLKRTC (1<<4)

#endif


