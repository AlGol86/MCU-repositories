#include "stm8s.h"

#define PORT_DC GPIOC
#define PIN_DC_da   3
#define PIN_DC_clk  4
#define PIN_DC_STB  5
#define BIT_DC_da  (1<<PIN_DC_da)
#define BIT_DC_clk (1<<PIN_DC_clk)
#define BIT_DC_STB (1<<PIN_DC_STB)
#define BIT_DC_mask (BIT_DC_da|BIT_DC_clk|BIT_DC_STB)

#define CMD_ADDR_0   0xc0
#define BRIGHTNESS   5 //0-7
#define CMD_DISP_ON  (0x88+BRIGHTNESS)
#define CMD_DISP_OFF 0x80
#define CMD_DATA_W_norm_incADDR 0x40

void sysDelay(char del);
void sys_del_ms(int del_ms);	
void startTransmittoin(void);
void sendByte(char byte);
void stopTransmittoin(void);
void sendCMD(char byte);
void sendDataBunch(char* byte);
void printData(char* byte);
void printValue(long int val, char leftAlignment);
