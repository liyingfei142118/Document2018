#include<graphics.h>
#include<conio.h>
void main()
{
	double h=300;
	double v=0;
	double dv=9.8/50;

	initgraph(640,480);
	line(100,421,541,421);
	while(!_kbhit())
	{
		v+=dv;
		h-=(v-dv/2);
		if(h<=0)
		{
			h+=(v-dv/2);
			v=-v*0.9;
		}
		setcolor(GREEN);
		circle(320,400-int(h),20);
		Sleep(20);
		setcolor(BLACK);
		circle(320,400-int(h),20);

	}
	closegraph();
}