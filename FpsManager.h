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
	//1フレームにかかる時間
	const double FRAME_TIME = 0.0;
	//計測開始時間
	LARGE_INTEGER timeStart;
	//計測終了時間
	LARGE_INTEGER timeEnd;
	//計測周波数
	LARGE_INTEGER timeFreq;;
};