/*
�_�ŏ��������N���X

�쐬���F2021/11/01
*/
#include"pch.h"

#include"Blinking.h"


/*===================================
�R���X�g���N�^
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
�f�X�g���N�^
===================================*/
Blinking::~Blinking()
{
}
/*===================================
�X�V����
===================================*/
void Blinking::Update()
{

	mBlinkingNum += mBlinkingInterval;
	mSinfNum = std::sinf(mBlinkingNum);

	//sin�l�����ƂɃt���O�����Ă�
	if (mSinfNum >= 0)
	{
		mBlinkingFlag = true;
	}
	else
	{
		mBlinkingFlag = false;
	}
}