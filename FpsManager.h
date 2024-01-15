#pragma once
#include <fstream>
#include <sstream>
#include <windows.h>
#include <timeapi.h>

#pragma comment(lib,"winmm.lib")

class FpsManager
{
public:
	FpsManager(double frame = 60.0);

	double TimeAdjustment();

private:
	//1�t���[���ɂ����鎞��
	const double FRAME_TIME = 0.0;
	//�v���J�n����
	LARGE_INTEGER timeStart;
	//�v���I������
	LARGE_INTEGER timeEnd;
	//�v�����g��
	LARGE_INTEGER timeFreq;;
};