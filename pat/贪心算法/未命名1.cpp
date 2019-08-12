#include<stdio.h>
char buff[] = { 3,2,1,0,130 };
int a, b;
int main()
{
	char *p = buff;
	a = *(int*)p;
	b = *(int *)(p + 1);
	printf("a=%x,b=%x\n", a, b);
	printf("a=%d,b=%d\n", a, b);
	return 0;
}
