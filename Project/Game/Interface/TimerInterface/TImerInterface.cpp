/*
タイマーを管理するインターフェース
作成日：2021/10/14
*/
#include"pch.h"

//クラス外部で初期化
TimerInterface* TimerInterface::sTimerInterface = nullptr;

/*===================================
コンストラクタ
===================================*/
TimerInterface::TimerInterface()
	:
	mTimer()
{
}


/*===================================
初期化処理
===================================*/
TimerInterface& TimerInterface::GetTimerInstance()
{

	if (sTimerInterface == nullptr)
	{
		sTimerInterface = new TimerInterface();
	}
	return *sTimerInterface;
}


/*===================================
削除処理
===================================*/
void TimerInterface::Destroy() const
{
	if (sTimerInterface != nullptr) {
		delete sTimerInterface;
		sTimerInterface = nullptr;
	}
}




