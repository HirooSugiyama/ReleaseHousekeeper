/*
�V�K���s�t�@�C��

*/
#include"pch.h"

#include"DefenseActionBlockCreate.h"


//�֐��̎g�p
#include"Game/UI/MoneyTexture.h"
#include"Game/UI/UI.h"

//�O���錾
#include"../../../PlaySceneCommon/Administrator/Administrator.h"
#include"../../../PlaySceneDefence/PreparingBlock.h"
#include"../../../PlaySceneCommon/Block/BlockManager.h"
#include"../Player.h"


//�֐������̌Ăяo���Ŏg�p
#include"../../../PlaySceneCommon/ObjectModel/BoxModel.h"

//�������̎擾
#include"Game/Money/Money.h"


//�u���b�N�̔�p
const int DefenseActionBlockCreate::BLOCK_COST = 10;

/*=====================================
�R���X�g���N�^
=====================================*/
DefenseActionBlockCreate::DefenseActionBlockCreate()
	:
	mpPlayer(nullptr),
	mpPreparingBlock(nullptr),
	mpBlockManager(nullptr),
	mOverLappingFlag(false),
	mGridLineFlag(false)
{
}

/*=====================================
�f�X�g���N�^
=====================================*/
DefenseActionBlockCreate::~DefenseActionBlockCreate()
{
}

/*=====================================
����������
�����F�v���C���[�̃|�C���^
=====================================*/
void DefenseActionBlockCreate::Initialize(Player* pPlayer)
{
	mpPlayer = pPlayer;
}


/*=====================================
�|�C���^�ۑ��֐�
�����F���{�u���b�N�̃|�C���^
		�u���b�N�Ǘ��N���X�̃|�C���^
=====================================*/
void DefenseActionBlockCreate::SetPointer(
		PreparingBlock* pPreparingBlock,
		BlockManager* pBlockManager)
{
	mpPreparingBlock = pPreparingBlock;
	mpBlockManager = pBlockManager;
}

/*===================================
�u���b�N��������
===================================*/
void DefenseActionBlockCreate::Create()
{
	//���C���̓_��ł͂Ȃ��Ȃ珈����ʂ��Ȃ�
	if (mGridLineFlag == false)
	{
		return;
	}

	//���{�u���b�N�Ɨ����Ă���u���b�N���d�Ȃ��Ă����珈����ʂ�
	if (mOverLappingFlag == false)
	{

		// �L�[���͏����擾����
		KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
		GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

		// �}�E�X���͏����擾����
		auto mouseState = DirectX::Mouse::Get().GetState();

		//�������擾
		auto& pM = Money::GetMoneyInstance();

		//�u���b�N���Ĕ���擾
		bool Createflag = false;
		if (pM.GetMoney() >= BLOCK_COST)
		{
			Createflag = true;
		}


		if (pKey->ActionDefenseHouse()|| pGamePad->ActionPlayer())//�L�[���͂��s��ꂽ��
		{
			//���ސ����K�v���𒴂��Ă�����
			if (Createflag)
			{
				pM.ReduceMoney(BLOCK_COST);

				//�u���b�N�𐶐�����
				mpBlockManager->CreateBlock
				(mpPreparingBlock->GetBoxModel()->GetPosition(),
					mpPreparingBlock->GetBoxModel()->GetScale());


				mpPlayer->GetUIPointer()->CreateMoneyEffect(BLOCK_COST);
			}
		}
	}
}

/*=====================================
�`�揈��
=====================================*/
void DefenseActionBlockCreate::Draw()
{
	//�����ԈȊO�̏ꍇ�̓u���b�N��\������
	if (mpPlayer->GetPlayerState() != ePlayerState::DAMAGE)
	{
		mpPreparingBlock->Draw();
	}
}
