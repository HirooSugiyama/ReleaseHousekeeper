/*
�^�C�}�[���Ǘ�����C���^�[�t�F�[�X
�쐬���F2021/10/14
*/
#include"pch.h"

//�N���X�O���ŏ�����
TimerInterface* TimerInterface::sTimerInterface = nullptr;

/*===================================
�R���X�g���N�^
===================================*/
TimerInterface::TimerInterface()
	:
	mTimer()
{
}


/*===================================
����������
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
�폜����
===================================*/
void TimerInterface::Destroy() const
{
	if (sTimerInterface != nullptr) {
		delete sTimerInterface;
		sTimerInterface = nullptr;
	}
}




