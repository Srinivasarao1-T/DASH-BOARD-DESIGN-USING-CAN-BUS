#ifndef _SENSOR_H_
#define _SENSOR_H_
unsigned char ResetDS18b20(void);
unsigned char ReadBit(void);
void WriteBit(unsigned char Dbit);
unsigned char ReadByte(void);
void WriteByte(unsigned char Dout);
int ReadTemp(void);
#endif
