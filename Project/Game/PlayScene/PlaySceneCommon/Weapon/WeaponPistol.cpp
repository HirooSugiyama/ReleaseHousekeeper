/*
�s�X�g���N���X
�쐬���F2021/10/14
*/
#include"pch.h"
#include"WeaponPistol.h"


//�֐��̎g�p
#include"../Bullet/BulletManager.h"
#include"../ObjectModel/ObjectModel.h"

//�T�E���h�֌W
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"


//���f���̊g�嗦
const DirectX::SimpleMath::Vector3 WeaponPistol::PISTOL_MODEL_SCALE(1.5f,1.5f,1.5f);

//���ˈʒu�̒���
const DirectX::SimpleMath::Vector3 WeaponPistol::PISTOL_SHOT_SHIFT_POSITION(0.f,0.f,-2.3f);

//�w���z
const int WeaponPistol::PISTOL_PRICE = 1000;

//�w�����̑��e��
const int WeaponPistol::PISTOL_MAX_BULLET_NUM = 21;

/*===================================
�R���X�g���N�^
===================================*/
WeaponPistol::WeaponPistol()
	: 
	WeaponBase()
{
}

/*===================================
�f�X�g���N�^
===================================*/
WeaponPistol::~WeaponPistol()
{
}

/*===================================
����������
===================================*/
void WeaponPistol::Initialize()
{
	//���f���̏����ݒ�
	this->ModelInit();

	//���Z�b�g����
	this->Reset();
}

/*===================================
���Z�b�g����
===================================*/
void WeaponPistol::Reset()
{
	WeaponBase::SetBulletNum(PISTOL_MAX_BULLET_NUM);
}

/*===================================
�`�揈��
===================================*/
void WeaponPistol::Draw()
{
	//���f����`�悷��
	WeaponBase::GetWeaponModel()->Draw();
}

/*==================================
�e���ˏ���
�Ԃ�l�F���ː��������s��(true :����)
===================================*/
void WeaponPistol::Shot()
{
	//�T�E���h�Đ������擾����
	ADX2& pSound = ADX2::GetInstance();

	//�e�𐶐�����
	bool shotFlag= WeaponBase::GetBulletManager()->Create
	(
		WeaponBase::GetWeaponModel()->GetPosition() + PISTOL_SHOT_SHIFT_POSITION
	);

	//�������˂ł����
	if (shotFlag)
	{
		//�e�������炷
		WeaponBase::ReduceBulletNum();

		pSound.Play(CRI_CUESHEET_0_SE_SHOT_PISTOL);

	}

}

/*===================================
���f���̏����ݒ�:private
===================================*/
void WeaponPistol::ModelInit()
{
	//���\�[�X�̎擾
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("Pistol");

	//���f���̐ݒ�
	WeaponBase::GetWeaponModel()->SetModel(model);
	

	//���f���̊g�嗦
	WeaponBase::GetWeaponModel()->SetScale(PISTOL_MODEL_SCALE);
}




