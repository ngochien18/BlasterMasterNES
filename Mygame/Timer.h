#pragma once

#include "windows.h"

class Timer
{
private:
	int startTime, limitTime;
public:
	Timer(int limitTime)
	{
		startTime = GetTickCount64();
		this->limitTime = limitTime;
	}

	~Timer() {}

	int GetStartTime() { return startTime; }
	int GetLimitTime() { return limitTime; }
	int GetTick() { return GetTickCount64() - startTime; };
	void Start() { startTime = GetTickCount64(); }
	bool IsTimeUp() { return GetTickCount64() - startTime >= limitTime; }
	void AddToTimer(int msec) { startTime += msec; }
	void Reset() { startTime = 0; }
	void Reset(int newLimitTime) { startTime = 0; limitTime = newLimitTime; }
};

