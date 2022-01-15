/*
�v���C���[�̃u���b�N��������̏���
�쐬���F2021/06/18
*/

#include"pch.h"
#include "PreparingBlock.h"

//�ړ����x�̎擾�Ɏg�p
#include"../PlaySceneCommon/ObjectMove.h"

//�֐����Ŏg�p
#include"../PlaySceneCommon/GridLine/GridLineManager.h"

//�������̎擾
#include"Game/Money/Money.h"






//�u���b�N�����K�v���ސ�
const int PreparingBlock::BLOCK_CREATE_MONEY_NUM = 10;

//�v���C���[���班�����炷���W
const DirectX::SimpleMath::Vector3   PreparingBlock::BLOCK_SHIFT_PLAYERPOSITION(0.f, 0.5f, -3.f);


//�~���̔��a
const float PreparingBlock::SAMPLEBLOCK_COLLIDER_RADIUS = 0.5f;

/*�ړ�����*/
	//���{�u���b�N�̈ړ���(X)
const float PreparingBlock::SAMPLEBLOCK_MOVE_VELOCITY_X = MoveSpeed::MOVE_VELOCITY_X;
//���{�u���b�N�̈ړ���(Y)
const float PreparingBlock::SAMPLEBLOCK_MOVE_VELOCITY_Y = MoveSpeed::MOVE_VELOCITY_Y;
//���{�u���b�N�̈ړ���(Z)
const float PreparingBlock::SAMPLEBLOCK_MOVE_VELOCITY_Z = MoveSpeed::MOVE_VELOCITY_Z;

//�u���b�N�̊g�嗦
const DirectX::SimpleMath::Vector3 PreparingBlock::SAMPLEBLOCK_SCALE(1.5f, 1.5f, 0.5f);

//�u���b�N�̏������W
const DirectX::SimpleMath::Vector3 PreparingBlock::SAMPLEBLOCK_INIT_POSITION(0.0f, 1.3f, -3.0f);

/*===================================
�R���X�g���N�^
===================================*/
PreparingBlock::PreparingBlock()
	: 
	mpSampleModel(nullptr),
	mpCircleCollider(nullptr),
	mMoveFlag(true)
{

	mpSampleModel = std::make_unique<BoxModel>();
	mpCircleCollider = std::make_unique<Circle>();
}

/*===================================
�f�X�g���N�^
===================================*/
PreparingBlock::~PreparingBlock()
{
}

/*===================================
������
===================================*/
void PreparingBlock::Initialize()
{

	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	//���{�u���b�N
	auto samplemodel = pRM->GetCmoModel("WBlock");
	mpSampleModel->SetModel(samplemodel);

	//���{�u���b�N�̏���ݒ肷��
	this->GetBoxModel()->SetPosition(SAMPLEBLOCK_INIT_POSITION);
	this->GetBoxModel()->SetScale(SAMPLEBLOCK_SCALE);


	/*�����蔻�萶��*/
	//�g�嗦�̔����̒l�𐶐�
	DirectX::SimpleMath::Vector3 halfsize = mpSampleModel->ReturnHalfSize(SAMPLEBLOCK_SCALE);
	//�ݒ�
	mpSampleModel->SetAABBCollider(SAMPLEBLOCK_INIT_POSITION - halfsize, SAMPLEBLOCK_INIT_POSITION + halfsize);


	//�����蔻��X�V����
	this->CircleColliderUpdate();

}

/*===============================================
�X�V
�����F�ړ��x�N�g���A���C���Ǘ��N���X�̃|�C���^
==================================================*/
void PreparingBlock::Update(
	DirectX::SimpleMath::Vector3 const& movevel,
	GridLineManager* pGridLineMnager)
{

	//���������ړ��ł��Ȃ���ԂȂ珈�������Ȃ�
	if (mMoveFlag)
	{
		//���g�̈ړ�����
		this->Move(movevel, pGridLineMnager);
		/*�����蔻��X�V*/
		//�g�嗦�̔����̒l�𐶐�
		DirectX::SimpleMath::Vector3 halfsize = mpSampleModel->ReturnHalfSize(mpSampleModel->GetScale());
		//�ݒ�
		mpSampleModel->SetAABBCollider(mpSampleModel->GetPosition() - halfsize,
			mpSampleModel->GetPosition() + halfsize);

		//�����蔻��X�V����
		this->CircleColliderUpdate();
	}
}

/*===================================
�`��
===================================*/
void PreparingBlock::Draw()
{
	mpSampleModel->Draw();
}


/*===================================================
�ړ�����
�����F�ړ��x�N�g���A�O���b�h���Ǘ��N���X�̃|�C���^
===================================================*/
void PreparingBlock::Move(DirectX::SimpleMath::Vector3 const& movevel,
	GridLineManager* pGridLineMnager)
{

	//��{�ƂȂ���W���Z�o
	DirectX::SimpleMath::Vector3 basePosition = movevel + BLOCK_SHIFT_PLAYERPOSITION;

	//2D�ϊ�
	DirectX::SimpleMath::Vector2 castpos;
	castpos.x = basePosition.x;
	castpos.y = basePosition.z;

	//����p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 subpos;

	//��{�ƂȂ���W����ł��߂��O���b�h���̌�_���擾
	castpos = pGridLineMnager->GetIntersectionNearPosition(castpos);

	subpos.x = castpos.x;
	subpos.y = basePosition.y;
	subpos.z = castpos.y;

	mpSampleModel->SetPosition(subpos);
}




/*===================================================================
���Ă��Ȃ��u���b�N���ޕύX�֐�:private
====================================================================*/
void PreparingBlock::ChangeNotUseBlock()
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();

	//�\������u���b�N��ς���
		//���{�u���b�N
	auto samplemodel = pRM->GetCmoModel("NotUseBlock");
	this->GetBoxModel()->SetModel(samplemodel);
}

/*==========================================================
���ނ�����Ă��Ȃ��Ƃ���������u���b�N�̎��ޕύX�֐�:private
============================================================*/
void PreparingBlock::ChangeNotEnoughMat()
{
	//�����������炷
	auto& pM = Money::GetMoneyInstance();

	//�u���b�N���Ĕ���擾
	bool Createflag = true;

	if (pM.GetMoney() <= BLOCK_CREATE_MONEY_NUM)
	{
		Createflag = false;
	}

	//�����ǂ����Ă��Ȃ��Ȃ�(���ސ�������Ȃ�)
	if (!Createflag)
	{
		//���Ă��Ȃ����{���f���ɐ؂�ւ��鏈�����s��
		this->ChangeNotUseBlock();
	}
}

/*==================
�����蔻�萶������
====================*/
void PreparingBlock::CircleColliderUpdate()
{		
	//���C���Փ˔���p�ϐ��̏�����
	//���W�ϊ�
	Vector2XZ pos2D;
	pos2D.x = mpSampleModel->GetPosition().x;
	pos2D.z = mpSampleModel->GetPosition().z;
	mpCircleCollider->mCenter = pos2D;
	mpCircleCollider->mRadius = SAMPLEBLOCK_COLLIDER_RADIUS;
}

