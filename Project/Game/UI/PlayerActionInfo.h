/*
���݂̃v���C���[�̍s����Ԃ�\��UI
�쐬���F2021/10/15
*/
#pragma once


//�񋓌^�̎g�p
#include"../PlayScene/PlaySceneCommon/Player/PlayerActionState.h"
#include"../PlayScene/PlaySceneCommon/Weapon/WeaponeType.h"

//����
#include"../Common/SpriteNumber/SpriteNumber2D.h"
#include"../Common/ObjectSpriteTexture.h"


class PlayerActionInfo
{
private:
	//���n�摜�̕����ʒu
	static const float GROUNDWORK_TEX_HALF_CUT_POSITIONY;

	//���n�摜�̊g�嗦
	static const DirectX::SimpleMath::Vector2 GROUNDWORK_TEX_SCALE;
	//���n�摜�̍��W
	static const DirectX::SimpleMath::Vector2 GROUNDWORK_TEX_POSITION;

	//�ǌ���Ԃ̐؂���ʒu
	static const RECT BLOCK_CREATE_RECT;
	//�U����Ԃ̐؂���ʒu
	static const RECT ATTACK_ENEMY_RECT;

	//����摜�̍��W
	static const DirectX::SimpleMath::Vector2 WEAPON_TEX_SCALE;
	//����摜�̊g�嗦
	static const DirectX::SimpleMath::Vector2 WEAPON_TEX_POSITION;

	//��U���摜�̂��炷��
	static const DirectX::SimpleMath::Vector2 WEAPON_TEX_SHIFT;

	//����摜�̕����T�C�Y
	static const int WEAPON_SIZE;

	//����摜�̏����ʒu
	static const RECT WEAPON_INIT_RECT;

	//�e���̕`��ʒu
	static const DirectX::SimpleMath::Vector2 BULLET_NUM_POSITION;



	//���n�̉摜
	std::unique_ptr<ObjectSpriteTexture> mpGroundworkTexture;

	//�e�핐��摜
	std::unique_ptr<ObjectSpriteTexture> mpWeaponSpriteTexture;

	std::unique_ptr<SpriteNumber2D> mpSpriteWeaponBulletNum;

	//�v���C���[�̏��
	ePlayerActionState mActionState;

	//�v���C���[�̕���
	eWeaponType mPlayerWeapon;

	//���݂̒e��
	int mStrongWeaponBulletNum;

public:

	//�R���X�g���N�^
	PlayerActionInfo();
	//�f�X�g���N�^
	~PlayerActionInfo();
	//����������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();


	//�v���C���[�̏�Ԃ̃A�N�Z�T
	void SetPlayerActionState(ePlayerActionState const& state) { mActionState = state; this->ChangeTexture(); }
	//�������Ă��镐��̕ύX
	void SetPlayerWeaponType(eWeaponType const& type) { mPlayerWeapon = type; this->ChangeTexture(); }

	//�؂���ʒu��؂�ւ���
	void ChangeTexture();

	//���݂̒e���̃A�N�Z�T
	void StrongWeaponBulletNum(int const& num) { mStrongWeaponBulletNum = num; };
};
