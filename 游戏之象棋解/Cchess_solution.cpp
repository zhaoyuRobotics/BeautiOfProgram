#include <stdio.h>

int main()
{
  
  unsigned char loop = 81;
  while(loop--)
  {	
	if(loop/9%3 == loop%9%3)
		continue;
     printf("A=%d,B=%d\n",loop/9+1,loop%9+1);
  }

}
