/*
�v���C���[�̏�ԕ����X�e�[�g�p�^�[���F�������
�쐬���F2021/06/15
*/
#pragma once
#include"PlayerStateBase.h"


class ObjectSpriteModel;

class PStateStand :public PlayerStateBase
{
private:
	//�ϐ�
	//Player�I�u�W�F�N�g�֕ۑ��p�̃|�C���^
	Player* mpPlayer;

public:
	//�֐�
	//�R���X�g���N�^
	PStateStand();
	//�f�X�g���N�^
	~PStateStand();
	//����������
	void Initialize(Player* pPlayer)override;
	//State�J�n���̏���������
	void Reset()override {}
	//�X�V����
	void Update()override;
	//�`�揈��
	void Draw()override;

};