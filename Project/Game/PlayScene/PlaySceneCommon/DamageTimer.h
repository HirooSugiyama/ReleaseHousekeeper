/*
�_���[�W�v���^�C�}�[�N���X
�쐬���F2021/06/16
*/
#pragma once




class DamageTimer
{
private:
	//�萔
	//PSceneState�ύX����
	static const int DAMAGE_TIMER;

	//�ϐ�
		//�^�C�}�[
	int mMainTimer;
	int mSubTimer;
	int mIntervalTimer;
		//���Ԋu�ŕς��t���O
	bool mIntervalFlag;

public:
	//�֐�
	//�R���X�g���N�^
	DamageTimer();
	//�f�X�g���N�^
	~DamageTimer();
	//�X�V����
	bool Update();

	//���Ԋu��true��Ԃ�����
	int RegularIntervalTimer(int const& interval);
};