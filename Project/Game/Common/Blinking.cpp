/*
点滅処理援助クラス

作成日：2021/11/01
*/
#include"pch.h"

#include"Blinking.h"


/*===================================
コンストラクタ
===================================*/
Blinking::Blinking(float intervalNum)
	:
	mBlinkingFlag(false),
	mSinfNum(0.f),
	mBlinkingInterval(intervalNum),
	mBlinkingNum(0.f)
{
}

/*===================================
デストラクタ
===================================*/
Blinking::~Blinking()
{
}
/*===================================
更新処理
===================================*/
void Blinking::Update()
{

	mBlinkingNum += mBlinkingInterval;
	mSinfNum = std::sinf(mBlinkingNum);

	//sin値をもとにフラグを建てる
	if (mSinfNum >= 0)
	{
		mBlinkingFlag = true;
	}
	else
	{
		mBlinkingFlag = false;
	}
}