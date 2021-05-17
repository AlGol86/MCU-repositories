#include "led.h"
#include "iic.h"
#include "gy_521.h"



int main( void )
{
 supply ();
 initGY_521();
 init_LED();
 
 
 while(1){
 int x=get_average_GY_521(AXEL_X);
  x/=10;
 printValue((int long)x, 0); 
 }


}
  


