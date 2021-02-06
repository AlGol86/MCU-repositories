#include "stm8s.h"
#include "main.h"

main()
{


long int i=100;	
while (1)
{
printValue(i, 0);
sys_del_ms(80);
i--;
}
}
