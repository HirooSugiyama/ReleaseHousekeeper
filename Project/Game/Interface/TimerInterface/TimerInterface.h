/*
�^�C�}�[���Ǘ�����C���^�[�t�F�[�X
�쐬���F2021/10/14
*/
#pragma once

#include <StepTimer.h>

class TimerInterface
{
private:

	//�������g
	static TimerInterface* sTimerInterface;

	//�^�C�}�[
	DX::StepTimer mTimer;

	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete�B
	TimerInterface( TimerInterface const& pv) = delete;
	TimerInterface operator=( TimerInterface const& pv) = delete;

	//�R���X�g���N�^
	TimerInterface();
	//�f�X�g���N�^
	~TimerInterface() = default;

public:
	//���g�̃C���X�^���X
	static TimerInterface& GetTimerInstance();

	//�폜����
	void Destroy()const;

	//�^�C�}�[�̃A�N�Z�T
	DX::StepTimer GetTimer() const { return mTimer; }
	void SetTimer(DX::StepTimer const& timer) { mTimer = timer; }

};
