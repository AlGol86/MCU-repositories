#include "stm8s.h"
#include "main.h"

void sysDelay(char del){
char i;
for(i=0;i<del;i++){nop();}
}
void sys_del_ms(int del_ms)	
{
int i;
int  j;
for(i=0;i<del_ms;i++){
for(j=0;j<200;j++){nop();}}
}

/* //open drain ver.
void startTransmittoin(){
	PORT_DC ->CR2&=~BIT_DC_mask;
	PORT_DC ->CR1&=~BIT_DC_mask;
	PORT_DC ->ODR&=~BIT_DC_mask;
	PORT_DC ->DDR|=BIT_DC_clk|BIT_DC_da;
	nop();sysDelay(200);
	PORT_DC ->DDR|=BIT_DC_STB;
}
void sendByte(char byte){
	char i;
	sysDelay(200);
	for(i=0;i<8;i++){
		PORT_DC ->ODR&=~BIT_DC_clk;
		nop();sysDelay(200);
		PORT_DC ->ODR|=(byte&1)<<PIN_DC_da;
		nop();sysDelay(200);
		PORT_DC ->ODR|=BIT_DC_clk;
		byte>>=1;sysDelay(200);
	}
}	
	
void stopTransmittoin(){
	PORT_DC ->ODR|=BIT_DC_STB;
}
*/

//inversion  ver.
void startTransmittoin(){
	PORT_DC ->CR2&=~BIT_DC_mask;
	PORT_DC ->CR1&=~BIT_DC_STB;
	PORT_DC ->ODR&=~BIT_DC_STB;
	PORT_DC ->DDR|=BIT_DC_STB;
	
	PORT_DC ->CR1|=BIT_DC_mask;
		
	PORT_DC ->ODR|=BIT_DC_clk|BIT_DC_da;
	PORT_DC ->DDR|=BIT_DC_mask;
	PORT_DC ->ODR|=BIT_DC_STB;
}
void sendByte(char byte){
	char i;
	for(i=0;i<8;i++){
		PORT_DC ->ODR|=BIT_DC_clk;
		PORT_DC ->ODR&=~BIT_DC_da;
		nop();
		PORT_DC ->ODR|=((~byte)&1)<<PIN_DC_da;
		nop();
		PORT_DC ->ODR&=~BIT_DC_clk;
		byte>>=1;sysDelay(3);
	}
}	
	
void stopTransmittoin(){
	PORT_DC ->ODR&=~BIT_DC_STB;
}


void sendCMD(char byte){
	startTransmittoin();
	sendByte(byte);
	stopTransmittoin();
}
void sendDataBunch(char* byte){
	char i;
	startTransmittoin();
	sendByte(CMD_ADDR_0);
	
	for(i=0;i<8;i++){
		sendByte(*(byte+i));
		sendByte(0);
	}
	stopTransmittoin();
}

void printData(char* byte){
	startTransmittoin();
	sendCMD(CMD_DATA_W_norm_incADDR);
	stopTransmittoin();
	
	startTransmittoin();
	sendDataBunch(byte);
	stopTransmittoin();
	
	startTransmittoin();
	sendCMD(CMD_DISP_ON);
	stopTransmittoin();
}

void printValue(long int val, char leftAlignment){
	char data[14]={0x3f,0x06,0x5b,0x4f,0x66,  0x6d,0x7d,0x07,0x7f,0x6f,/*0-9,(0-9)*/ 0x80,/*'.' (10)*/ 0x00,/*' '(11)*/ 0x08,               /*'_'(12)*/ 0x40};   /* '-'(minus) (13)*/
  char sendingData[8]	={0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00};																														
	long valCopy;
	char sign;
	char digCNTR=1;
	char i,d;

	
	if ((val>99999999)||(val<-9999999)){
		  for(i=0;i<8;i++){
				sendingData[i]=data[13];
		  }
			printData(sendingData);
			return;
  } 
	if (val<0) {sign=1;val=-val;digCNTR++;}
	else sign=0;
	valCopy=val;
	while(valCopy>=10){
		valCopy/=10;
	  digCNTR++;
	}
	
	
	if(leftAlignment){ //leftAlignment
	
    for(i=digCNTR;i>0;i--){
			d=val%10;
			if((d==0)&&(sign)&&(i==1)) 
			  sendingData[0]=data[13];
			else{
			  sendingData[i-1]=data[d];
			  val/=10;
		  }
		}		

    printData(sendingData);
		
		
  } 
	else{//rghtAlignment
	  for(i=8;i>=(9-digCNTR);i--){
			d=val%10;
			if((d==0)&&(sign)&&(i==(9-digCNTR))) 
			  sendingData[8-digCNTR]=data[13];
			else{
			  sendingData[i-1]=data[d];
			  val/=10;
		  }
		}			
    printData(sendingData);
	}
}	
