#include "iostm8s103f3.h"

#define rim() asm("rim")
#define sim() asm("sim")
#define nop() asm("nop")

#define PORT_led_ODR       PB_ODR
#define PORT_led_DDR       PB_DDR
#define PORT_led_IDR       PB_IDR
#define PORT_led_CR1       PB_CR1
#define PORT_led_CR2       PB_CR2
#define PIN_DC_da   4
#define PIN_DC_clk  5

#define BIT_DC_da  (1<<PIN_DC_da)
#define BIT_DC_clk (1<<PIN_DC_clk)

#define BIT_DC_mask (BIT_DC_da|BIT_DC_clk)

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