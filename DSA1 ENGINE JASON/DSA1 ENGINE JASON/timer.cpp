#include "timer.h"



timer::timer()
{
	prev = cur = clock();
	t = dt = fps = 0;
}


timer::~timer()
{
}

void timer::update()
{
	prev = cur;
	cur = clock();
	dt = (cur - prev) / (float)CLOCKS_PER_SEC;
	t += dt;
	fps = 1 / dt;
}
