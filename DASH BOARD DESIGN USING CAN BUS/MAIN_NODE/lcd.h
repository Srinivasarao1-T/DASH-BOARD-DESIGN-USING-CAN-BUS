#ifndef _LCD_H_
#define _LCD_H_
#include "types.h"
void initLCD(void);
void writeLCD(u8);
void cmdLCD(u8);
void charLCD(u8);
void strLCD(u8 *);
void u32LCD(u32);
// void s32LCD(s32);
void f32LCD(f32,u8);
void BuildCGRAM(const u8*,u8);
#endif
