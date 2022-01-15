/*
�_���[�W�v���^�C�}�[�N���X
�쐬���F2021/06/16
*/

#include "pch.h"
#include "DamageTimer.h"

const int DamageTimer::DAMAGE_TIMER = 3;

/*==============================
�R���X�g���N�^
==============================*/
DamageTimer::DamageTimer()
	:
	mMainTimer(0),
	mSubTimer(0),
	mIntervalTimer(0),
	mIntervalFlag(false)
{
}

/*==============================
�f�X�g���N�^
==============================*/
DamageTimer::~DamageTimer()
{
}
/*==============================
�X�V����
==============================*/
bool DamageTimer::Update()
{
	//�^�C�}�[�̎擾
	TimerInterface& pT = TimerInterface::GetTimerInstance();
	
	mSubTimer++;
	mIntervalTimer++;
	if (mSubTimer >= static_cast<int>(pT.GetTimer().GetFramesPerSecond())) 
	{
		mSubTimer = 0;
		mMainTimer++;
	}
	//���ԂɂȂ�����true��Ԃ��B
	if (mMainTimer == DAMAGE_TIMER) 
	{
		mMainTimer = 0;
		mIntervalTimer = 0;
		return true;
	}
	return false;
}


/*==============================
���Ԋu�Ńt���O��Ԃ�����
�����F����
�Ԃ�l�F�\���t���O(true���\��)
==============================*/
int DamageTimer::RegularIntervalTimer(int const& interval)
{
	//��莞�ԂɂȂ�����
	if (mIntervalTimer == interval) 
	{		
		//�\������Ă�����
		if (mIntervalFlag) 
		{
			//��\���ɂ���
			mIntervalFlag = false;
		}
		//��\���Ȃ�
		else 
		{
			//�\������
			mIntervalFlag = true;
		}
		mIntervalTimer = 0;
	}
	
	return mIntervalFlag;
}
