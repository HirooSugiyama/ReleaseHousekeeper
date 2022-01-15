/*
��������
�쐬���F2021/10/13
*/
#include"pch.h"

#include"Movenumber.h"

#include"StepTimer.h"

/*===================================
�R���X�g���N�^
===================================*/
MoveNumber::MoveNumber()
	:
	mFirstNum(),
	mVelocityNum(),
	mTopNum(),
	mOneSecondVelocityNum()
{
}

/*===================================
�f�X�g���N�^
===================================*/
MoveNumber::~MoveNumber()
{
}

/*===================================================================================
����������
�����FfirstNum(�ŏ��̒l)�AmoveSecondSpeed(�������鎞��)�AmaxNum(�ŏ��̒l�̍ő�l)
===================================================================================*/
void MoveNumber::Initialize(int firstNum, float moveSecondSpeed, int maxNum)
{
	//������ۑ�����
	mFirstNum = static_cast<float>(firstNum);
	mTopNum = maxNum;


	//1�b������̑����ʂ��v�Z����
	float movenum = static_cast<float>(mTopNum) - mFirstNum;//�������Ȃ���΂Ȃ�Ȃ��l���Z�o
	mOneSecondVelocityNum = movenum / moveSecondSpeed;			//�b���Ŋ���
}

/*================================================================
�X�V����
�����F	timer(�W���̃^�C�}�[)
		fallflag(�����t���O�Btrue�̎��͒l�����炷[default:false])

�Ԃ�l�F�ύX��̒l
==================================================================*/
int MoveNumber::Update(DX::StepTimer const& timer, bool fallflag)
{
	unsigned int fps = timer.GetFramesPerSecond();

	//����0���
	if (fps == 0)
	{
		fps++;
	}

	//1F������̑����ʂ��v�Z����
	mVelocityNum = mOneSecondVelocityNum / fps;



	//�l�𑝂₷�����炷���ŏ�����ς���
	switch (fallflag)
	{
		case true:
		{
			//�ŏ��l�ɓ��B���Ă��Ȃ����
			if (mFirstNum > mTopNum)
			{
				//���X�Ɍ��炵�Ă���
				mFirstNum += mVelocityNum;
			}
			//�ŏ��l�ȏ�ɂȂ�����␳����
			if (mFirstNum < mTopNum)
			{
				mFirstNum = static_cast<float>(mTopNum);
			}

			break;
		}
		case false:
		{
			//�ő�l�ɓ��B���Ă��Ȃ����
			if (mFirstNum < mTopNum)
			{
				//���X�ɑ����Ă���
				mFirstNum += mVelocityNum;
			}
			//�ő�l�ȏ�ɂȂ�����␳����
			if (mFirstNum > mTopNum)
			{
				mFirstNum = static_cast<float>(mTopNum);
			}

			break;
		}
	}
	return static_cast<int>(mFirstNum);
}
