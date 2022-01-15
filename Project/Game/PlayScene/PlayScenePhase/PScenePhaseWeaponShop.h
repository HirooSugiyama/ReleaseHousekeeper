/*
����w���t�F�[�Y
�쐬���F2021/09/30
*/
#pragma once

//���N���X
#include"PlayScenePhaseBase.h"

//����
#include"../PlaySceneCommon/Weapon/WeaponManager.h"
#include"../../Common/ObjectTexture.h"
#include"../PlaySceneShop/RotWeaponSample.h"
#include"Libraries/MyLibraries/FixedPointCamera.h"
#include"../PlaySceneShop/WeaponExplanatory.h"
#include"../../Common/Cursor.h"
#include"../../Common/Blinking.h"



//�O���錾

class BulletManager;			//�|�C���^�ۑ��p�ϐ�
class ActionStateAttackEnemy;	//�|�C���^�ۑ��p�ϐ�
class Cursor;
class Blinking;

class PScenePhaseWeaponShop :public PlayScenePhaseBase
{
private:

	//�w�ʉ摜�̏������W
	static const DirectX::SimpleMath::Vector2 BACKGROUND_TEXTURE_INIT_POSITION;
	//�w�ʉ摜�̊g�嗦
	static const DirectX::SimpleMath::Vector2 BACKGROUND_TEXTURE_SCALE;

	//�J�[�\���̊g�嗦
	static const DirectX::SimpleMath::Vector2 CURSOR_INIT_POSITION;
	//�J�[�\���̍��W
	static const DirectX::SimpleMath::Vector2 CURSOR_SCALE;
	//�J�[�\���̈ړ���
	static const float CURSOR_SHIFT;

	//�_�ŉ摜�̊g�嗦
	static const DirectX::SimpleMath::Vector2 BACK_TEX_SCALE;
	//�_�ŉ摜�̍��W
	static const DirectX::SimpleMath::Vector2 BACK_TEX_POSITION;

	//��_�J�����̍��W
	static const DirectX::SimpleMath::Vector3 PIXED_CAMERA_POSITION;

	//�e�����̐F
	static const DirectX::SimpleMath::Vector4 STRING_COLOR;

	//�e�����̕`����W
	//�l�i
	static const DirectX::SimpleMath::Vector2 STRING_PRICENUM_POSITION;
	//�U����
	static const DirectX::SimpleMath::Vector2 STRING_ATTACKNUM_POSITION;
	//�e��
	static const DirectX::SimpleMath::Vector2 STRING_BULLETNUM_POSITION;


	//PlayScene�I�u�W�F�N�g�֕ۑ��p�̃|�C���^
	PlayScene* mpPlayScene;

	//����Ǘ��N���X
	std::unique_ptr<WeaponManager> mpWeaponManager;

	std::unique_ptr<ObjectTexture> mpBackTexture;

	//���ݑI�����Ă��镐��ԍ�
	int mSelectWeaponNum;

	//�J�[�\��
	std::unique_ptr<Cursor> mpShopCursor;

	//�߂�L�[�`��摜
	std::unique_ptr<ObjectTexture> mpBackGroundTexture;

	//�W�����{���f��
	std::unique_ptr<RotWeaponSample> mpRotWeaponSample;

	//��_�J����
	std::unique_ptr<FixedPointCamera> mpFixedPointCamera;

	//�_�ŃN���X
	std::unique_ptr<Blinking> mpTextureBlinking;

	//���ݑI�����Ă��镐��̑��e��
	int mSelectWeaponBulletNum;
	//���ݑI�����Ă��镐��̒l�i
	int mSelectWeaponPrice;
	//���ݑI�����Ă��镐��̈З�
	int mSelectWeaponAttackNum;

	//��������
	std::unique_ptr<WeaponExplanatory> mpWeaponExplanatory;

	//�h�q��Ԃɖ߂�t���O
	bool mDefenceBackFlag;

public:


	//�R���X�g���N�^
	PScenePhaseWeaponShop();

	//�f�X�g���N�^
	~PScenePhaseWeaponShop();
	
	//������
	void Initialize(PlayScene* pPlayScene)override ;

	//�X�V
	void Update()override; 

	//State�ύX�O�̃��Z�b�g����
	void Reset()override;

	//�`��
	void Draw()override;

private:
	//�����I������
	void SelectWeapon();

	//�J�[�\����������
	void ShopCursorUp();

	//�J�[�\����������
	void ShopCursorDown();

	//����𔃂�
	void BuyWeapon();

	//����Ή���������ɐ؂�ւ���
	void ChangeInfoSelectWeapon();
};