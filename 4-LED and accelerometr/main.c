#include "led.h"
#include "iic.h"
#include "gy_521.h"
#include "main.h"

statement_t statement;

int main( void )
{
 supply ();
 initGY_521();
 init_LED();
 out(init);
  printValue((int long)555, 0); 
  printValue((int long)666, 1); 
 while(1){
 int x=get_average_GY_521(AXEL_X);
  x/=10;
  
 printValue((int long)x, 0); 
 
 if(check_condition_GY_521(500,100,x)) {out(on);}
 else {out(off);}
 }


}

void out(out_t out){
  switch(out){
  case init:{
	PORT_out_CR2&=~BIT_out;
	PORT_out_CR1&=~BIT_out;
	PORT_out_ODR|=BIT_out;
	PORT_out_DDR|=BIT_out;
	sysDelay(200);
        break;
  }
  case on:{
  PORT_out_ODR&=~BIT_out;
  break;
  }
  case off:{
  PORT_out_ODR|=BIT_out;
  break;
  }
 }
}
