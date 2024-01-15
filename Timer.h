#pragma once
#include <chrono>
#include <functional>

class Timer
{
private:
	//計測開始時間
	std::chrono::steady_clock::time_point startTime;

	//経過時間
	float elapsedTime;

public:
	Timer();
	~Timer();
	
	/// <summary>
	/// Timer関数
	/// </summary>
	/// <param name="time">計測時間</param>
	/// <param name="callback">実行したい関数</param>
	void LoopTimer(float time, std::function<void()>* callback);

	//計測開始時間の初期化
	void ResetStartTime();

	float GetElapsedTime() { return elapsedTime; }
};

