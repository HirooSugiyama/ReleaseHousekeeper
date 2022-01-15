/*
��U���N���X
�쐬���F2021/09/14
*/
#include"pch.h"
#include"WeaponHand.h"

//�֐��̎g�p
#include"../ObjectModel/BoxModel.h"


//�v���C���[�̍��W����U������܂ł̋���
const DirectX::SimpleMath::Vector3 WeaponHand::ATTACKSTATE_PLAYER_DISTANCE_POSITION(0.f, 0.f,-3.5f);

//�����蔻��̊g�嗦
//���f��
const DirectX::SimpleMath::Vector3 WeaponHand::ATTACKSTATE_COLLIRDEMODEL_SCALE(3.5f, 1.f, 1.f);

const float WeaponHand::ATTACKSTATE_COLLIRDE_SCALE = 1.6f;


//�U���ő�t���[����
const int WeaponHand::ATTACKSTATE_MAX_ATTACK_FRAME = 60;
//�����ő�t���[����
const int WeaponHand::ATTACKSTATE_MAX_RECOIL_FRAME = 5;

//�G�ւ�1��̍U���̃_���[�W�l
const int WeaponHand::ATTACKSTATE_HAND_DAMAGE = 2;

//�A�j���[�V�����̍��W�������グ��l
const float WeaponHand::ATTACK_STATE_SHIFT_ANIMATION = 1.f;

/*===================================
�R���X�g���N�^
===================================*/
WeaponHand::WeaponHand()
	:
	mpWeapon(nullptr),
	mpAnim(nullptr),
	mpPlayer(nullptr),
	mWorld(),
	mAttackFlag(eHandState::STAND_BY),
	mAttackFrameCountNum(0),
	mAnimationFlag(false),
	mColliderPosition(DirectX::SimpleMath::Vector3::Zero)
{
	mpWeapon = std::make_unique<SphereModel>();
	mpAnim = std::make_unique<NormalAttackAnim>();
}

/*===================================
�f�X�g���N�^
===================================*/
WeaponHand::~WeaponHand()
{
}

/*===================================
����������
===================================*/
void WeaponHand::Initialize()
{

	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("Weapon");

	//���f���̐ݒ�
	mpWeapon->SetModel(model);

	//�g�嗦�̐ݒ�
	mpWeapon->SetScale(ATTACKSTATE_COLLIRDEMODEL_SCALE);

	//���W�̍X�V�͍X�V������

	//�A�j���[�V�����̏���������
	mpAnim->Initialize();
}

/*=======================================================================
�X�V����
=======================================================================*/
void WeaponHand::Update()
{
	//����p�ϐ��̏���
	DirectX::SimpleMath::Vector3 pos;
	pos = mpPlayer->GetPlayerModel()->GetPosition() + ATTACKSTATE_PLAYER_DISTANCE_POSITION;

	//���W�̐ݒ�
	mpWeapon->SetPosition(pos);

	//�ȗ����ϐ��̐錾
	DirectX::SimpleMath::Matrix trans;

	trans = DirectX::SimpleMath::Matrix::CreateTranslation(ATTACKSTATE_PLAYER_DISTANCE_POSITION);

	//�v�Z����(�`�揈���Ŏg�p)
	mWorld = trans * mpPlayer->GetPlayerAttackWorldMatrix();

	//�U���t���[���v������
	this->AttackFrameCount();

	//�U����ԂȂ珈����ʂ�
	if (mAttackFlag==eHandState::ATTACK&&!mAnimationFlag)
	{
		//�����蔻��쐬
		this->SetCollider();


		//�A�j���[�V�����̍X�V����
		mAnimationFlag = mpAnim->Update(mpPlayer->GetPlayerAttackWorldMatrix());
	}
	//��U����ԂȂ�قȂ鏈����ʂ�
	else 
	{
		mpWeapon->SetSphereCollider(DirectX::SimpleMath::Vector3::Zero, 0.f);
	}


	//���݂̔����t���[�����ő�ɓ��B������
	if (mAnimationFlag &&mAttackFrameCountNum < -ATTACKSTATE_MAX_RECOIL_FRAME)
	{
		//��U����ԂƂ�
		mAttackFlag = eHandState::STAND_BY;

		//���Z�b�g�������s��
		this->Reset();
	}


}


/*=================================
�`�揈��
===================================*/
void WeaponHand::Draw()
{
	//�U����ԂȂ珈����ʂ�
	if (mAttackFlag== eHandState::ATTACK)
	{
		//�A�j���[�V�����̕`�揈��
		mpAnim->Draw();
	}
}

/*===========================
�����蔻���Ԃ�����
===========================*/
SphereModel* WeaponHand::GetCollider()
{
	return mpWeapon.get();
}

/*=========================================
�����蔻��̍쐬:private
����:�����t���O(false �쐬���Ȃ�)
=========================================*/
void WeaponHand::SetCollider(bool const& flag)
{
	switch (flag)
	{
		case false:
		{
			/*�����蔻�萶��*/
			mColliderPosition =
				DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Zero, mWorld);
			mpWeapon->SetSphereCollider(mColliderPosition, ATTACKSTATE_COLLIRDE_SCALE);
			break;
		}
		case true:
		{
			/*�����蔻��폜*/
			mpWeapon->SetSphereCollider(DirectX::SimpleMath::Vector3::Zero, 0.f);

			break;
		}

	}
}

/*===========================
�U������ғ�����:private
===========================*/
void WeaponHand::AttackFrameCount()
{

	//���݂̍U���t���[�����ő�t���[���ɓ��B������
	if (mAnimationFlag&& mAttackFlag== eHandState::ATTACK)
	{
		//������ԂƂ�
		mAttackFlag = eHandState::COOL_TIME;	
	}


	if (mAttackFlag == eHandState::COOL_TIME)
	{
		mAttackFrameCountNum--;//�U���t���[���𑝂₵�Ă���
	}
}

/*===========================
���Z�b�g����:private
===========================*/
void WeaponHand::Reset()
{
	mAttackFrameCountNum = 0;//�J�E���g�����Z�b�g����	
	mAnimationFlag = false;

	//�A�j���[�V�����̃��Z�b�g����
	mpAnim->Reset();

}
