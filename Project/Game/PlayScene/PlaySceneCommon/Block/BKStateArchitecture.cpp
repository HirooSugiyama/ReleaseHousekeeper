/*
�ǂ����񂾂񗧂����̕ǒǉ�����
�쐬���F2021/07/21
*/
#include"pch.h"
#include "BKStateArchitecture.h"



//�֐������{���̂��ߕK�v
#include"Block.h"
#include"../../PlaySceneCommon/ObjectModel/BoxModel.h"




//�萔
//���z���x
const float BKStateArchitecture::BLOCK_CREATE_SPEED = 0.005f;

/*====================
�R���X�g���N�^
======================*/
BKStateArchitecture::BKStateArchitecture()
	:BlockKindBase()
	, mpBlock(nullptr)
	, mFinishPositionY(0.f)
	, mBeginPositionY(0.f)
	, mDefenseHouseSpeed(0.f)
{
}

/*======================
�f�X�g���N�^
======================*/
BKStateArchitecture::~BKStateArchitecture()
{
}

/*======================
����������
�����FBlock�̃|�C���^
======================*/
void BKStateArchitecture::Initialize(Block* pBlock)
{
	//�|�C���^��ۑ�����
	mpBlock = pBlock;
}

/*======================
�X�V����
======================*/
bool BKStateArchitecture::Update()
{
	//�ړ�����
	this->DefenseHouse();

	//�����蔻��̍X�V
	this->UpdateCollider();

	//State�ڍs����
	return this->ChangeStateBlock();
}

/*==============================
����������(�������֌W�ȊO)
================================*/
void BKStateArchitecture::Reset()
{
	//���z�X�s�[�h��ݒ�
	mDefenseHouseSpeed = BLOCK_CREATE_SPEED;

	//�ǂ̃T�C�Y����ŏ���Y�n�_���Z�o����֐�
	this->CreateBeforePositionY();
}

/*======================
�ړ�����:private
======================*/
void BKStateArchitecture::DefenseHouse()
{
	//�ϐ��錾
	DirectX::SimpleMath::Vector3 vel;
	//�ړ��ʐݒ�
	vel.y = mDefenseHouseSpeed;
	//���f���𓮂���
	mpBlock->GetBoxModel()->Move(vel);
}

/*============================
�����蔻��X�V����:private
============================*/
void BKStateArchitecture::UpdateCollider()	
{
	/*�����蔻��̍X�V*/
	//�����ł͕ۑ����ĂȂ����߃��f������Ăяo���B
	DirectX::SimpleMath::Vector3 modelpos, modelscale;
	modelpos = mpBlock->GetBoxModel()->GetPosition();
	modelscale = mpBlock->GetBoxModel()->GetScale();

	//�g�嗦�̔����̒l�𐶐�
	DirectX::SimpleMath::Vector3 halfsize = mpBlock->GetBoxModel()->ReturnHalfSize(modelscale);
	//�ݒ�
	mpBlock->GetBoxModel()->SetAABBCollider(modelpos - halfsize, modelpos + halfsize);
}

/*==============================================================
�����O�̒n�ʂɖ��܂�����Ԃ�Y���W���Z�o:private
==============================================================*/
void BKStateArchitecture::CreateBeforePositionY()
{
	//���z�ςݍ��W���擾
	mFinishPositionY = mpBlock->GetBoxModel()->GetPosition().y;

	//�g�嗦�Ȃǂ��猚�z�O���W���Z�o
	mBeginPositionY = mFinishPositionY- (mFinishPositionY);

	//���ۂɑ�����X�V�����ł���オ�点��B
	DirectX::SimpleMath::Vector3 blockpos = mpBlock->GetBoxModel()->GetPosition();
	blockpos.y = mBeginPositionY;
	mpBlock->GetBoxModel()->SetPosition(blockpos);

}

/*========================================================
State�ύX����:private
�Ԃ�l�F�ύX�t���O(���W�ɉ�����State��؂�ւ���)
========================================================*/
bool BKStateArchitecture::ChangeStateBlock()
{
	if (mFinishPositionY <= mpBlock->GetBoxModel()->GetPosition().y)
	{
		return true;
	}
	return false;
}
