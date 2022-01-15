/*
����̐������Ǘ��N���X

�쐬���F2021/12/08
*/
#pragma once

//�񋓌^�̎g�p
#include"../PlaySceneCommon/Weapon/WeaponeType.h"
//����
#include"../../Common/ObjectSpriteTexture.h"

class WeaponExplanatory
{
private:
	//������̕`����W
	static const DirectX::SimpleMath::Vector2 STRING_POSITION;
	//������̊g�嗦
	static const DirectX::SimpleMath::Vector2 STRING_SCALE;


	//������̐F���W
	static const DirectX::SimpleMath::Color STRING_COLOR;
	//�e�핐��̐�����
	static const RECT STRING_RENGE;

	
	//�`�悷�镶����(�摜)
	std::unique_ptr<ObjectSpriteTexture> mpExplanatory;
	

public:

	//�R���X�g���N�^
	WeaponExplanatory();
	//�f�X�g���N�^
	~WeaponExplanatory();
	//����������
	void Initialize();
	//�X�V����
	void Update(eWeaponType const& type);
	//�`�揈��
	void Draw(DirectX::SimpleMath::Vector4 const& color);
};
