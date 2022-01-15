/*
�v���C���[�̏�ԕ����X�e�[�g�p�^�[���F������
�쐬���F2021/06/15
*/
#pragma once
#include"PlayerStateBase.h"

class DamageTimer;

class PStateDamage :public PlayerStateBase
{
private:
	//�萔
	//�v���C���[�_�ŃC���^�[�o��
	static const int PLAYER_BLINKING_INTERVAL;
	
	//�ϐ�
	//Player�I�u�W�F�N�g�֕ۑ��p�̃|�C���^
	Player* mpPlayer;

	std::unique_ptr<DamageTimer> mpDamageTimer;

public:
	//�֐�
	//�R���X�g���N�^
	PStateDamage();
	//�f�X�g���N�^
	~PStateDamage();

	//����������
	void Initialize(Player* pPlayer)override;
	//State�J�n���̏���������
	void Reset()override {}
	//�X�V����
	void Update()override;
	//�`�揈��
	void Draw()override;
};