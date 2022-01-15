/*
タイマー
*/
#include"pch.h"

#include"Timer.h"

//フレーム最低値
const float Timer::MIN_FRAME = 50.f;

/*===================================
コンストラクタ
===================================*/
Timer::Timer()
	:
	mMaxTime(),
	mMainTimer(),
	mSubTimer()
{
}

/*===================================
デストラクタ
===================================*/
Timer::~Timer()
{
}

/*=================================
更新処理
===================================*/
bool Timer::Update()
{
	//現在のFPSを取得
	TimerInterface& pT = TimerInterface::GetTimerInstance();

	float fps = static_cast<float>(pT.GetTimer().GetFramesPerSecond());

	//サブタイマー増加
	mSubTimer += static_cast<float>(pT.GetTimer().GetElapsedSeconds()) * fps;
 
	//大体60FPS==1sなので
	if (mSubTimer >= fps)
	{

		mSubTimer = 0.f;
		mMainTimer++;
	}

	//最大時間となったら
	if (mMainTimer >= mMaxTime)
	{
		return true;
	}

	return false;
}



