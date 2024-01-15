#include "Timer.h"

Timer::Timer()
{
	//Œv‘ªŠJnŠÔ‚Ì‰Šú‰»
	ResetStartTime();
	
	elapsedTime = 0.0f;
}

Timer::~Timer()
{
}

void Timer::LoopTimer(float time,std::function<void()>* callback)
{
	auto endTime = std::chrono::steady_clock::now();
	auto diff = endTime - startTime;
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
	elapsedTime = elapsed.count() / 1000.0f;

	if (time * 1000.0f <= elapsed.count())
	{
		startTime = endTime;

		if (callback != nullptr)
		{
			(*callback)();
		}
	}
}

void Timer::ResetStartTime()
{
	startTime = std::chrono::steady_clock::now();
}
