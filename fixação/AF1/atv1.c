#include <stdio.h>
#include <stdlib.h>

void altera1(int **p, int *a)
{ 
	**p = *a;
 	*a = *a +50;
}
void altera2(int **p, int *b)
{ 
	*p = b;
 	*b = *b +30;
}

int main()
{
	int x,y, *px, *py;
 	x = 10;
	y = x + 20;
 	px = &x;
 	py = &y;
printf("x = %d, End. x = %p, px = %p, y = %d \n",x,&x, px,y);
altera1(&px, &y);
printf("x = %d, End. x = %p, px = %p, y = %d \n",x,&x, px,y);
getchar();
printf("y = %d, End. y = %p, py = %p, x = %d \n",y,&y, py,x);
altera2(&py, &x);
printf("y = %d, End. y = %p, py = %p, x = %d \n",y,&y, py,x);
getchar();
return(0);
}