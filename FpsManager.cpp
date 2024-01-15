#include "FpsManager.h"

FpsManager::FpsManager(double frame) :FRAME_TIME(1.0f / frame)
{
	//���g���擾
	QueryPerformanceFrequency(&timeFreq);

	//�v���J�n���Ԃ̏�����
	QueryPerformanceCounter(&timeStart);
}

double FpsManager::TimeAdjustment()
{
	//���݂̎��Ԃ��擾
	QueryPerformanceCounter(&timeEnd);
	//�o�ߎ���(�b�P��)=�@(���݂̎���-�O��̃t���[���̎���)/���g��
	double frameTime = static_cast<double>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<double>(timeFreq.QuadPart);
	double fps = 0.0;
	//�������Ԃ��]�����ꍇ�͂��̕��ҋ@
	if (frameTime < FRAME_TIME)
	{
		//Sleep�̎��Ԃ��v�Z
		DWORD sleepTime = static_cast<DWORD>((FRAME_TIME - frameTime) * 1000);
		timeBeginPeriod(1);
		//�ҋ@
		Sleep(sleepTime);
		timeEndPeriod(1);
	}
	fps = 1 / frameTime;

	timeStart = timeEnd;

	return fps;
}
