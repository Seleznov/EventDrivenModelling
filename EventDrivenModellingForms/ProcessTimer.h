#pragma once
#include <windows.h>

class ProcessTimer
{
private:
	unsigned __int64* counters;
	unsigned __int64 freq;
public:
	ProcessTimer(int = 1);
	void Start(int = 0);
	float Get(int = 0);
public:
	~ProcessTimer(void);
};