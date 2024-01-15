#include "FpsManager.h"

FpsManager::FpsManager(double frame) :FRAME_TIME(1.0f / frame)
{
	//周波数取得
	QueryPerformanceFrequency(&timeFreq);

	//計測開始時間の初期化
	QueryPerformanceCounter(&timeStart);
}

double FpsManager::TimeAdjustment()
{
	//現在の時間を取得
	QueryPerformanceCounter(&timeEnd);
	//経過時間(秒単位)=　(現在の時間-前回のフレームの時間)/周波数
	double frameTime = static_cast<double>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<double>(timeFreq.QuadPart);
	double fps = 0.0;
	//処理時間が余った場合はその分待機
	if (frameTime < FRAME_TIME)
	{
		//Sleepの時間を計算
		DWORD sleepTime = static_cast<DWORD>((FRAME_TIME - frameTime) * 1000);
		timeBeginPeriod(1);
		//待機
		Sleep(sleepTime);
		timeEndPeriod(1);
	}
	fps = 1 / frameTime;

	timeStart = timeEnd;

	return fps;
}
