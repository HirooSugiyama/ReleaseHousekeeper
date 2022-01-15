/*
���݂̃v���C���[�̍s����Ԃ�\��UI
�쐬���F2021/10/15
*/
#include"pch.h"
#include"PlayerActionInfo.h"


//���n�摜�̕����ʒu
const float PlayerActionInfo::GROUNDWORK_TEX_HALF_CUT_POSITIONY = 0.f;
//���n�摜�̊g�嗦
const DirectX::SimpleMath::Vector2 PlayerActionInfo::GROUNDWORK_TEX_SCALE(2.5f,2.5f);
//���n�摜�̍��W
const DirectX::SimpleMath::Vector2 PlayerActionInfo::GROUNDWORK_TEX_POSITION(840.f, 620.f);

//�ǌ���Ԃ̐؂���ʒu
const RECT PlayerActionInfo::BLOCK_CREATE_RECT = RECT{ 0,36,165,72 };
//�U����Ԃ̐؂���ʒu
const RECT PlayerActionInfo::ATTACK_ENEMY_RECT = RECT{ 0,0,165,36 };


//����摜�̊g�嗦
const DirectX::SimpleMath::Vector2 PlayerActionInfo::WEAPON_TEX_SCALE(0.12f, 0.12f);
//����摜�̍��W
const DirectX::SimpleMath::Vector2 PlayerActionInfo::WEAPON_TEX_POSITION(885.f, 620.f);
//��U���摜�̂��炷��
const DirectX::SimpleMath::Vector2 PlayerActionInfo::WEAPON_TEX_SHIFT(125.f,0.f);

//����摜�̕����T�C�Y
const int PlayerActionInfo::PlayerActionInfo::WEAPON_SIZE = 500;


//����摜�̏����ʒu
const RECT PlayerActionInfo::WEAPON_INIT_RECT = RECT{ 0, 0, 500, 500 };

//�e���̕`��ʒu
const DirectX::SimpleMath::Vector2 PlayerActionInfo::BULLET_NUM_POSITION(1000.f, 630.f);

/*=================================
�R���X�g���N�^
===================================*/
PlayerActionInfo::PlayerActionInfo()
	:
	mpGroundworkTexture(),
	mpWeaponSpriteTexture(nullptr),
	mpSpriteWeaponBulletNum(nullptr),
	mActionState(ePlayerActionState::BLOCK_CREATE),
	mPlayerWeapon(eWeaponType::NONE),
	mStrongWeaponBulletNum(0)
{
	mpGroundworkTexture = std::make_unique<ObjectSpriteTexture>
	(
		BLOCK_CREATE_RECT,GROUNDWORK_TEX_POSITION,
		GROUNDWORK_TEX_SCALE
	);

	mpWeaponSpriteTexture = std::make_unique<ObjectSpriteTexture>
	(
		BLOCK_CREATE_RECT,
		WEAPON_TEX_POSITION,
		WEAPON_TEX_SCALE
	);

	mpSpriteWeaponBulletNum = std::make_unique<SpriteNumber2D>();
}

/*=================================
�f�X�g���N�^
===================================*/
PlayerActionInfo::~PlayerActionInfo()
{
}

/*===================================
����������
===================================*/
void PlayerActionInfo::Initialize()
{
	//���\�[�X�̊m��
	ResourceManager *pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture("GroundWorkFrame");

	//����������
	mpGroundworkTexture->Initialize();
	mpGroundworkTexture->SetTexture(texture);


	texture = pRM->GetTexture("WeaponSprite");

	//����������
	mpWeaponSpriteTexture->Initialize();
	mpWeaponSpriteTexture->SetTexture(texture);

	mpSpriteWeaponBulletNum->SetTextureKey("MoneyNumberFont");
	mpSpriteWeaponBulletNum->Initialize();
}

/*===================================
�X�V����
===================================*/
void PlayerActionInfo::Update()
{

}

/*=================================
�`�揈��
===================================*/
void PlayerActionInfo::Draw()
{
	mpGroundworkTexture->Draw();

	if (mActionState == ePlayerActionState::ATTACK_ENEMY)
	{
		mpWeaponSpriteTexture->Draw();


		if (mPlayerWeapon!=eWeaponType::NONE)
		{
			mpSpriteWeaponBulletNum->Create(mStrongWeaponBulletNum, BULLET_NUM_POSITION);
			mpSpriteWeaponBulletNum->Draw();
		}
	}	
}

/*==================================
�؂���ʒu��؂�ւ���
===================================*/
void PlayerActionInfo::ChangeTexture()
{
	//���݂̃v���C���[�̏�Ԃ����ăe�N�X�`����ݒ肷��
	switch (mActionState)
	{
		case ePlayerActionState::BLOCK_CREATE:
		{		
			mpGroundworkTexture->SetRect(BLOCK_CREATE_RECT);

			break;
		}
		
		case ePlayerActionState::ATTACK_ENEMY:
		{
			mpGroundworkTexture->SetRect(ATTACK_ENEMY_RECT);

			//����摜�̐؂���ʒu������������
			mpWeaponSpriteTexture->SetRect(WEAPON_INIT_RECT);

			//�摜���ړ�������
			mpWeaponSpriteTexture->Beside(WEAPON_SIZE, static_cast<int>(mPlayerWeapon));

			//������U������Ȃ�
			if (mPlayerWeapon == eWeaponType::NONE)
			{
				mpWeaponSpriteTexture->SetPosition(WEAPON_TEX_POSITION+ WEAPON_TEX_SHIFT);
			}
			else	//����������Ȃ�
			{
				mpWeaponSpriteTexture->SetPosition(WEAPON_TEX_POSITION);
			}


			break;
		}

		case ePlayerActionState::SUMMON_VILLAGES:
		{
			break;
		}
	}
}
