/*
�^�C�}�[
*/
#pragma once

class Timer
{
private:

	//�t���[���Œ�l
	static const float MIN_FRAME;

	//�ő厞��
	int mMaxTime;

	//�^�C�}�[
	float mMainTimer;
	float mSubTimer;

public:

	//�R���X�g���N�^
	Timer();
	//�f�X�g���N�^
	~Timer();
	//�X�V����
	bool Update();


	//�ő厞�Ԃ̃A�N�Z�T
	void SetMaxTime(int const& time) { mMaxTime = time; }
	int GetMaxTime()const { return mMaxTime; }

	//���݂̎��Ԃ̃A�N�Z�T
	int GetMainTimer()const { return static_cast<int>(mMainTimer); }

	//���݂̎��Ԃ����Z�b�g����
	void ResetMainTimer() { mMainTimer = 0; }
};
