#pragma once
#include <chrono>
#include <functional>

class Timer
{
private:
	//�v���J�n����
	std::chrono::steady_clock::time_point startTime;

	//�o�ߎ���
	float elapsedTime;

public:
	Timer();
	~Timer();
	
	/// <summary>
	/// Timer�֐�
	/// </summary>
	/// <param name="time">�v������</param>
	/// <param name="callback">���s�������֐�</param>
	void LoopTimer(float time, std::function<void()>* callback);

	//�v���J�n���Ԃ̏�����
	void ResetStartTime();

	float GetElapsedTime() { return elapsedTime; }
};

