#ifndef FLAGS_H
#define FLAGS_H

#include <stdint.h>

void setz(const unsigned short val);
int getz();
void setn(const unsigned short val);
int getn();
void seth(const unsigned short val);
int geth();
void setc(const unsigned short val);
int getC();
void setADDflags(uint8_t a,uint8_t b,uint8_t result);
void setADD16flags(uint16_t a,uint16_t b);
void setADCflags(uint8_t a,uint8_t b,uint8_t c,uint8_t result);
void setSUBflags(uint8_t a,uint8_t b,uint8_t result);
void setSBCflags(uint8_t a,uint8_t b,uint8_t c,uint8_t result);
void setINCflags(uint8_t r,uint8_t result);
void setDECflags(uint8_t r,uint8_t result);
void setORflags(uint8_t result);
void setXORflags(uint8_t r);
void setANDflags(uint8_t r);
void setSWAPflags(uint8_t r);
void setCPflags(uint8_t a, uint8_t b);
void setBITflags(unsigned short bit);

#endif /* FLAGS_H */
