#ifndef _ADC_DEFINE_H_
#define _ADC_DEFINE_H_

#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define ADCCLK 3000000
#define CLCKDIV ((PCLK/ADCCLK)-1)
//	DEFINE FORT ADC SFR
#define PDN_BIT 21
#define ADC_START_BIT 24
//DEFINE FOR ADDR_SFR
#define DIGITAL_DATA_BITS 6
#define DONE_BIT 31
#define PIN_FUNC2 1
#define AINO_PIN_FUN PIN_FUN2

#endif
