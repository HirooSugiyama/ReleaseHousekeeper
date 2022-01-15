/*
タイマーを管理するインターフェース
作成日：2021/10/14
*/
#pragma once

#include <StepTimer.h>

class TimerInterface
{
private:

	//自分自身
	static TimerInterface* sTimerInterface;

	//タイマー
	DX::StepTimer mTimer;

	//コピーコンストラクタ、コピー代入演算子をdelete。
	TimerInterface( TimerInterface const& pv) = delete;
	TimerInterface operator=( TimerInterface const& pv) = delete;

	//コンストラクタ
	TimerInterface();
	//デストラクタ
	~TimerInterface() = default;

public:
	//自身のインスタンス
	static TimerInterface& GetTimerInstance();

	//削除処理
	void Destroy()const;

	//タイマーのアクセサ
	DX::StepTimer GetTimer() const { return mTimer; }
	void SetTimer(DX::StepTimer const& timer) { mTimer = timer; }

};
