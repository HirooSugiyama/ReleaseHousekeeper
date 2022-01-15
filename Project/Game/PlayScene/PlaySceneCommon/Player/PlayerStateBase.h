/*
�v���C���[�̏�ԕ����X�e�[�g�p�^�[��
�쐬���F2021/06/15
*/
#pragma once

#include"Player.h"//�|�C���^�̓s����

enum class eStatePlayer
{
	STAND,			
	WALK,			
	DAMAGE,
};

class PlayerStateBase
{

protected:
	//�R���X�g���N�^
	PlayerStateBase()=default;
	//�f�X�g���N�^
	virtual ~PlayerStateBase() = default;

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
