
#include "iostm8s103f3.h"

int main( void )
{
sys_del_ms(100);
printValue((long int)50, 0);
sys_del_ms(100);
long int i=9999;
printValue((long int)-999, 0);

while (1)
{
printValue(i, 0);
sys_del_ms(80);
i--;
}

}