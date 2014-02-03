#include "ProcessTimer.h"

ProcessTimer::ProcessTimer(int n)
{
	this->counters = new  unsigned __int64[n];
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
}

void ProcessTimer::Start(int counter) {
	QueryPerformanceCounter((LARGE_INTEGER*)&this->counters[counter]);
}

float ProcessTimer::Get(int counter) {
	unsigned __int64 end;
	QueryPerformanceCounter((LARGE_INTEGER*)&end);
	return (float(end - this->counters[counter]) / freq);
}

ProcessTimer::~ProcessTimer(void)
{
	delete [] this->counters;
}