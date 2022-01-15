/*
�V�K���s�t�@�C��

*/
#include"pch.h"

#include"WeaponExplanatory.h"

//������̕`����W
const DirectX::SimpleMath::Vector2 WeaponExplanatory::STRING_POSITION(680.f, 440.f);
//������̊g�嗦
const DirectX::SimpleMath::Vector2 WeaponExplanatory::STRING_SCALE(0.3f, 0.3f);
//�e�핐��̐�����
const RECT WeaponExplanatory::STRING_RENGE = RECT{ 0,0,2025,135 };

/*===================================
�R���X�g���N�^
===================================*/
WeaponExplanatory::WeaponExplanatory()
	:
	mpExplanatory(nullptr)
{
	mpExplanatory = std::make_unique<ObjectSpriteTexture>(STRING_RENGE);
}

/*===================================
�f�X�g���N�^
===================================*/
WeaponExplanatory::~WeaponExplanatory()
{
}

/*===================================
����������
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
�`�揈��
�����F�`�悵�Ă��镐��
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
�`�揈��
�����F�`�悵�Ă��镐��
===================================*/
void WeaponExplanatory::Draw(DirectX::SimpleMath::Vector4 const& color)
{
	mpExplanatory->Draw();
}
