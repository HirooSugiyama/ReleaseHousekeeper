/*
�v���C���[�̏�ԕ����X�e�[�g�p�^�[���F�������
�쐬���F2021/06/15
*/
#include"pch.h"

#include "PStateStand.h"



//�Ԃ�l����̊֐��̎擾�Ŏg�p�B
#include"../ObjectModel/BoxModel.h"
#include"../../PlaySceneDefence/PreparingBlock.h"
#include"../ObjectModel/ObjectSpriteModel.h"

/*=========================
�R���X�g���N�^
=========================*/
PStateStand::PStateStand()
	:
	PlayerStateBase(),
	mpPlayer(nullptr)
{
}

/*=========================
�f�X�g���N�^
=========================*/
PStateStand::~PStateStand()
{
}

/*=========================
����������
�����F�v���C���[�̃|�C���^
=========================*/
void PStateStand::Initialize(Player* pPlayer)
{
	mpPlayer = pPlayer;
}

/*=========================
�X�V����
=========================*/
void PStateStand::Update()
{
	if (mpPlayer->GetPlayerState() != ePlayerState::STAND) {
		mpPlayer->SetState(ePlayerState::STAND);
	}
}

/*=========================
�`�揈��
=========================*/
void PStateStand::Draw()
{
	mpPlayer->GetPlayerModel()->Draw();
}
