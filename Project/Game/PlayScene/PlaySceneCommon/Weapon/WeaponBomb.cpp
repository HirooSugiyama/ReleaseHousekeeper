/*
���e�N���X
�쐬���F2021/10/14
*/
#include"pch.h"
#include"WeaponBomb.h"

//�֐��̎g�p
#include"../ObjectModel/ObjectModel.h"
#include"../Bullet/BulletManager.h"

//�O���錾
#include"../Shadow.h"

//�d�͒萔�̎g�p
#include"../../PlaySceneDefence/Gravity.h"

//�T�E���h�֌W
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"


//���f���̊g�嗦
const DirectX::SimpleMath::Vector3 WeaponBomb::BOMB_MODEL_SCALE(1.5f,1.5f,1.5f);

//���ˈʒu�̒���
const DirectX::SimpleMath::Vector3 WeaponBomb::BOMB_SHOT_SHIFT_POSITION(0.f,0.f,-2.3f);

//�w���z
const int WeaponBomb::BOMB_PRICE = 200;

//�w�����̑��e��
const int WeaponBomb::BOMB_MAX_BULLET_NUM = 5;


//�������x
const float WeaponBomb::FIRST_VELOCITY = 0.3f;

//�ŏ��̍���
const float WeaponBomb::FIRST_HEIGHT = 1.f;

//�e�̑��x
const float WeaponBomb::BULLET_VELOCITY = 0.05f;

//���j���鍂��
const float WeaponBomb::BOMB_MIN_HEIGHT = 1.f;

/*===================================
�R���X�g���N�^
===================================*/
WeaponBomb::WeaponBomb()
	:
	WeaponBase(),
	mpShadow()
{
	mpShadow = std::make_unique<Shadow>();
}

/*===================================
�f�X�g���N�^
===================================*/
WeaponBomb::~WeaponBomb()
{
}

/*=================================
����������
===================================*/
void WeaponBomb::Initialize()
{
	//���f���̏����ݒ�
	this->ModelInit();

	mpShadow->Initialize();

	//�摜��ݒ肷��
	mpShadow->SetTexture("Aim");

	mpShadow->SetScale(DirectX::SimpleMath::Vector2(BOMB_MODEL_SCALE.x,BOMB_MODEL_SCALE.z)/2.f);

	//���Z�b�g����
	this->Reset();
}

/*===================================
���Z�b�g����
===================================*/
void WeaponBomb::Reset()
{
	WeaponBase::SetBulletNum(BOMB_MAX_BULLET_NUM);
}
/*===================================
�`�揈��
===================================*/
void WeaponBomb::Draw()
{
	//���f����`�悷��
	WeaponBase::GetWeaponModel()->Draw();
	//�����l���Z�o
	DirectX::SimpleMath::Vector3 fallpos = this->FallPoint();

	//�e�̕`��
	mpShadow->Draw(fallpos);
}

/*===================================
�e���ˏ���
�Ԃ�l�F���ː��������s��(true :����)
===================================*/
void WeaponBomb::Shot()
{

	//�T�E���h�Đ������擾����
	ADX2& pSound = ADX2::GetInstance();

	//���ۂɒe�𔭎˂��鏈��
	bool shotFlag= WeaponBase::GetBulletManager()->Create
	(
		WeaponBase::GetWeaponModel()->GetPosition() + BOMB_SHOT_SHIFT_POSITION
	);


	//�������˂ł����
	if (shotFlag)
	{
		//�e�������炷
		WeaponBase::ReduceBulletNum();

		pSound.Play(CRI_CUESHEET_0_SE_THROW_BOMB);
	}
}

/*===================================
���f���̏����ݒ�:private
===================================*/
void WeaponBomb::ModelInit()
{
	//���\�[�X�̎擾
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("Grenade");

	//���f���̐ݒ�
	WeaponBase::GetWeaponModel()->SetModel(model);

	//���f���̊g�嗦
	WeaponBase::GetWeaponModel()->SetScale(BOMB_MODEL_SCALE);
}

/*=================================
�����n�_�\��:private
�Ԃ�l�F����������W
===================================*/
DirectX::SimpleMath::Vector3 WeaponBomb::FallPoint()
{
	//�Ԃ�l�p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 fallpos = 
		WeaponBase::GetWeaponModel() ->GetPosition() + BOMB_SHOT_SHIFT_POSITION;

	//���x
	float bulletVelocity = FIRST_VELOCITY;
	//����
	float bulletHeight = FIRST_HEIGHT;
	int i = 0;

	while (fallpos.y >= BOMB_MIN_HEIGHT)
	{
		bulletVelocity -= Gravity::mGravityConstant;
		bulletHeight += bulletVelocity;

		//����p�ϐ��̐錾
		DirectX::SimpleMath::Vector3 movevel = DirectX::SimpleMath::Vector3(0.f, 0.f, -BULLET_VELOCITY);

		//���W�֔��f
		fallpos += movevel;

		DirectX::SimpleMath::Vector3 pos = fallpos;
		pos.y = bulletHeight;

		fallpos = pos;
		i++;
	}

	fallpos.y = BOMB_MIN_HEIGHT;

	return fallpos;
}
