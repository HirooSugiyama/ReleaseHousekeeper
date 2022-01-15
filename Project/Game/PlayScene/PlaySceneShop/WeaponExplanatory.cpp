/*
新規実行ファイル

*/
#include"pch.h"

#include"WeaponExplanatory.h"

//文字列の描画座標
const DirectX::SimpleMath::Vector2 WeaponExplanatory::STRING_POSITION(680.f, 440.f);
//文字列の拡大率
const DirectX::SimpleMath::Vector2 WeaponExplanatory::STRING_SCALE(0.3f, 0.3f);
//各種武器の説明文
const RECT WeaponExplanatory::STRING_RENGE = RECT{ 0,0,2025,135 };

/*===================================
コンストラクタ
===================================*/
WeaponExplanatory::WeaponExplanatory()
	:
	mpExplanatory(nullptr)
{
	mpExplanatory = std::make_unique<ObjectSpriteTexture>(STRING_RENGE);
}

/*===================================
デストラクタ
===================================*/
WeaponExplanatory::~WeaponExplanatory()
{
}

/*===================================
初期化処理
===================================*/
void WeaponExplanatory::Initialize()
{
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture("Explanatory");

	mpExplanatory->SetTexture(texture); 
	mpExplanatory->Initialize();
	mpExplanatory->SetRect(STRING_RENGE);
	mpExplanatory->SetPosition(STRING_POSITION);
	mpExplanatory->SetScale(STRING_SCALE);
}
/*===================================
描画処理
引数：描画している武器
===================================*/
void WeaponExplanatory::Update(eWeaponType const& type)
{
	RECT rect = STRING_RENGE;
;
	rect.top = (static_cast<int>(type)-1)* STRING_RENGE.bottom;


	rect.bottom *= static_cast<int>(type);

	mpExplanatory->SetRect(rect);
}

/*===================================
描画処理
引数：描画している武器
===================================*/
void WeaponExplanatory::Draw(DirectX::SimpleMath::Vector4 const& color)
{
	mpExplanatory->Draw();
}
