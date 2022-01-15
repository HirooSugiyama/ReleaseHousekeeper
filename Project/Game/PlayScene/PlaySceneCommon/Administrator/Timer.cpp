/*
�^�C�}�[
*/
#include"pch.h"

#include"Timer.h"

//�t���[���Œ�l
const float Timer::MIN_FRAME = 50.f;

/*===================================
�R���X�g���N�^
===================================*/
Timer::Timer()
	:
	mMaxTime(),
	mMainTimer(),
	mSubTimer()
{
}

/*===================================
�f�X�g���N�^
===================================*/
Timer::~Timer()
{
}

/*=================================
�X�V����
===================================*/
bool Timer::Update()
{
	//���݂�FPS���擾
	TimerInterface& pT = TimerInterface::GetTimerInstance();

	float fps = static_cast<float>(pT.GetTimer().GetFramesPerSecond());

	//�T�u�^�C�}�[����
	mSubTimer += static_cast<float>(pT.GetTimer().GetElapsedSeconds()) * fps;
 
	//���60FPS==1s�Ȃ̂�
	if (mSubTimer >= fps)
	{

		mSubTimer = 0.f;
		mMainTimer++;
	}

	//�ő厞�ԂƂȂ�����
	if (mMainTimer >= mMaxTime)
	{
		return true;
	}

	return false;
}



