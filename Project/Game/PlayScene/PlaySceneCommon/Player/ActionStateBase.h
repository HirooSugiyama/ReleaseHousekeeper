/*
�v���C���[�̍s����ԕ����X�e�[�g�p�^�[��
�쐬���F2021/09/14
*/
#pragma once

#include"Player.h"//�|�C���^�̓s����


class ActionStateBase
{

protected:
	//�R���X�g���N�^
	ActionStateBase() = default;
	//�f�X�g���N�^
	virtual ~ActionStateBase() = default;

public:
	//����������
	virtual void Initialize(Player* pPlayer) = 0;
	//�X�V����
	virtual void Update() = 0;
	//State�J�n���̏���������
	virtual void Reset() = 0;
	//�`�揈��
	virtual void Draw() = 0;

};
