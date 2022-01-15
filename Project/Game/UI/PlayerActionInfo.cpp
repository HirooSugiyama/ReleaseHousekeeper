/*
現在のプレイヤーの行動状態を表すUI
作成日：2021/10/15
*/
#include"pch.h"
#include"PlayerActionInfo.h"


//下地画像の分割位置
const float PlayerActionInfo::GROUNDWORK_TEX_HALF_CUT_POSITIONY = 0.f;
//下地画像の拡大率
const DirectX::SimpleMath::Vector2 PlayerActionInfo::GROUNDWORK_TEX_SCALE(2.5f,2.5f);
//下地画像の座標
const DirectX::SimpleMath::Vector2 PlayerActionInfo::GROUNDWORK_TEX_POSITION(840.f, 620.f);

//壁建状態の切り取り位置
const RECT PlayerActionInfo::BLOCK_CREATE_RECT = RECT{ 0,36,165,72 };
//攻撃状態の切り取り位置
const RECT PlayerActionInfo::ATTACK_ENEMY_RECT = RECT{ 0,0,165,36 };


//武器画像の拡大率
const DirectX::SimpleMath::Vector2 PlayerActionInfo::WEAPON_TEX_SCALE(0.12f, 0.12f);
//武器画像の座標
const DirectX::SimpleMath::Vector2 PlayerActionInfo::WEAPON_TEX_POSITION(885.f, 620.f);
//弱攻撃画像のずらす幅
const DirectX::SimpleMath::Vector2 PlayerActionInfo::WEAPON_TEX_SHIFT(125.f,0.f);

//武器画像の分割サイズ
const int PlayerActionInfo::PlayerActionInfo::WEAPON_SIZE = 500;


//武器画像の初期位置
const RECT PlayerActionInfo::WEAPON_INIT_RECT = RECT{ 0, 0, 500, 500 };

//弾数の描画位置
const DirectX::SimpleMath::Vector2 PlayerActionInfo::BULLET_NUM_POSITION(1000.f, 630.f);

/*=================================
コンストラクタ
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
デストラクタ
===================================*/
PlayerActionInfo::~PlayerActionInfo()
{
}

/*===================================
初期化処理
===================================*/
void PlayerActionInfo::Initialize()
{
	//リソースの確保
	ResourceManager *pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture("GroundWorkFrame");

	//初期化処理
	mpGroundworkTexture->Initialize();
	mpGroundworkTexture->SetTexture(texture);


	texture = pRM->GetTexture("WeaponSprite");

	//初期化処理
	mpWeaponSpriteTexture->Initialize();
	mpWeaponSpriteTexture->SetTexture(texture);

	mpSpriteWeaponBulletNum->SetTextureKey("MoneyNumberFont");
	mpSpriteWeaponBulletNum->Initialize();
}

/*===================================
更新処理
===================================*/
void PlayerActionInfo::Update()
{

}

/*=================================
描画処理
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
切り取り位置を切り替える
===================================*/
void PlayerActionInfo::ChangeTexture()
{
	//現在のプレイヤーの状態を見てテクスチャを設定する
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

			//武器画像の切り取り位置を初期化する
			mpWeaponSpriteTexture->SetRect(WEAPON_INIT_RECT);

			//画像を移動させる
			mpWeaponSpriteTexture->Beside(WEAPON_SIZE, static_cast<int>(mPlayerWeapon));

			//もし弱攻撃武器なら
			if (mPlayerWeapon == eWeaponType::NONE)
			{
				mpWeaponSpriteTexture->SetPosition(WEAPON_TEX_POSITION+ WEAPON_TEX_SHIFT);
			}
			else	//買った武器なら
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
