/*
�e�N���X
�쐬���F2021/09/17
*/
#include"pch.h"
#include"Bullet.h"

//�O���錾
#include"BulletType.h"
#include"BulletStateBase.h"


//�����蔻��̔��a
const float Bullet::COLLIDER_RADIUS = 1.f;
//�����蔻��g��W��
const float Bullet::COLLIDER_RADIUS_EXPANSION = 2.5f;

/*===================================
�R���X�g���N�^
===================================*/
Bullet::Bullet()
	:
	mpBulletModel(),
	mBulletAttackNum(),
	mBulletVelocity(),
	mWeaponType(eWeaponType::NONE),
	mpStateBase(nullptr),
	mpNormalBullet(nullptr),
	mpExplosion(nullptr),
	mpBoomerangBullet(nullptr),
	mExplosionFlag(false)
{
	mpBulletModel = std::make_unique<SphereModel>();

	//��ԕ���
	mpNormalBullet = std::make_unique<BulletStateNormalBullet>();
	mpExplosion = std::make_unique<BulletStateExplosion>();
}

/*===================================
�f�X�g���N�^
===================================*/
Bullet::~Bullet()
{
}

/*===================================
����������
===================================*/
void Bullet::Initialize()
{
	//���g�p��Ԃŏ�����
	mpBulletModel->SetModelUseFlag(false);

	//��ԕ�����Ƀ|�C���^��ۑ�
	mpNormalBullet->SetBuletPointer(this);
	mpExplosion->SetBuletPointer(this);
}

/*=================================
�X�V����
===================================*/
void Bullet::Update()
{
	//��Ԗ��̈ړ��������s��
	bool deleteflag = mpStateBase->Move();

	//�����͈͊O�ɏo����
	if (deleteflag)
	{
		//�u�[���������폜����
		//�A�N�Z�X�������������Ȃ̂�delete�͂��Ȃ��B
		mpBoomerangBullet = nullptr;
		this->SelfDestroy();
	}

	//�����蔻�蔽�f����
	this->SetCollider();

}

/*===================================
�`�揈��
===================================*/
void Bullet::Draw()
{
	mpBulletModel->Draw();
}

/*=================================
�e�쐬����
�����F�o�����W�A�e�̎��
===================================*/
void Bullet::Create(DirectX::SimpleMath::Vector3 const& pos, eWeaponType const& type)
{
	//�g�p��Ԃɂ���
	mpBulletModel->SetModelUseFlag(true);

	//���W�̐ݒ�
	mpBulletModel->SetPosition(pos);

	//�e�̎�ނ̕ۑ�
	mWeaponType = type;

	//�e�̎�ނɂ���ď�����ς���
	switch (mWeaponType)
	{
		case eWeaponType::MACHINE_GUN:
		case eWeaponType::PISTOL:			//NoBreak
		case eWeaponType::ROCKET_LAUNCHER://NoBreak
		{
			//�ʏ�e�̐ݒ�
			this->ChangeStateNormalBullet();

			break;
		}
		case eWeaponType::BOMB:
		{
			//�����e�̐ݒ�
			this->ChangeStateExplosion();
			break;
		}
		case eWeaponType::BOOMERANG:
		{
			this->ChangeStateBoomerang();

			break;
		}

	}
}

/*=================================
���g�p��Ԃւ̕ύX�֐�
===================================*/
void Bullet::SelfDestroy()
{
	if (mpBulletModel->GetModelUseFlag())
	{
		//�����蔻��������l��
		mpBulletModel->SetSphereCollider(DirectX::SimpleMath::Vector3::Zero, 0.f);

		//���g�p��Ԃɂ���
		mpBulletModel->SetModelUseFlag(false);

		//�����t���O������
		mExplosionFlag = false;
	}
}

/*=================================
�g�p�����ǂ�����Ԃ��A�N�Z�T
�Ԃ�l�F�g�p�t���O
===================================*/
bool Bullet::GetUseFlag()const
{
	return mpBulletModel->GetModelUseFlag();
}

/*===================================
Z���W��Ԃ�
�Ԃ�l�F���f����Z���W
===================================*/
float Bullet::GetBulletPositionZ()const
{
	return mpBulletModel->GetPosition().z;
}

/*===================================
�e���ۑ��p�֐�
===================================*/
void Bullet::SetBulletInfomation(BulletInfomation const& pBulletInfomation)
{
	//���f���̎擾
	mpBulletModel->SetModel(pBulletInfomation.mBulletModel);

	//�U���͂̐ݒ�
	mBulletAttackNum = pBulletInfomation.mBulletAttackNum;

	//�g�嗦�̐ݒ�
	mpBulletModel->SetScale(pBulletInfomation.mBulletScale);

	//�e�̑��x�̐ݒ�
	mBulletVelocity = pBulletInfomation.mBulletVelocityZ;
}

/*===================================
�ړ�����
===================================*/
Sphere* Bullet::GetBulletModelCollider()const
{
	return mpBulletModel->GetSphereCollider();
}

/*==================================
�����蔻�萶������
===================================*/
void Bullet::SetCollider()
{
	//�ȗ����p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 pos = mpBulletModel->GetPosition();
	float scale = COLLIDER_RADIUS;

	//�����蔻���ݒ肷��
	mpBulletModel->SetSphereCollider(pos,scale);
}

/*=================================
�����蔻���{�ɂ���
===================================*/
void Bullet::SetDoubleCollider()
{
	//�ȗ����p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 pos = mpBulletModel->GetPosition();
	float scale = COLLIDER_RADIUS* COLLIDER_RADIUS_EXPANSION;

	//�����蔻���ݒ肷��
	mpBulletModel->SetSphereCollider(pos, scale);
}
