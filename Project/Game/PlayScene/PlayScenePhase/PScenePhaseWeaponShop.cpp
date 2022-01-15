/*
����w���t�F�[�Y
�쐬���F2021/09/30
*/

#include"pch.h"
#include"PScenePhaseWeaponShop.h"

//������
#include"../PlayScene.h"

//�������̎擾
#include"../../Money/Money.h"

//�֐������̎g�p
#include"../../UI/UI.h"
#include"../PlaySceneCommon/Weapon/WeaponBase.h"
#include"../PlaySceneCommon/Player/Player.h"
#include"../PlaySceneCommon/Player/ActionStateAttackEnemy.h"
#include"../PlaySceneCommon/Bullet/BulletManager.h"
#include"../PlaySceneCommon/Bullet/BulletType.h"
#include"../PlaySceneCommon/ObjectModel/ObjectModel.h"

//�w�ʉ摜�̏������W
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::BACKGROUND_TEXTURE_INIT_POSITION(0.f, 0.f);
//�w�ʉ摜�̊g�嗦
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::BACKGROUND_TEXTURE_SCALE(1.f, 1.f);

//�J�[�\���̍��W
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::CURSOR_INIT_POSITION(20.f, 217.f);
//�J�[�\���̊g�嗦
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::CURSOR_SCALE(2.5f, 2.5f);
//�J�[�\���̈ړ���
const float PScenePhaseWeaponShop::CURSOR_SHIFT = 98.f;

//�_�ŉ摜�̊g�嗦
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::BACK_TEX_SCALE(0.3f, 0.3f);
//�_�ŉ摜�̍��W
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::BACK_TEX_POSITION(0.f, 0.f);

//��_�J�����̍��W
const DirectX::SimpleMath::Vector3 PScenePhaseWeaponShop::PIXED_CAMERA_POSITION(0.0f, 2.0f, 10.0f);

//�e�����̐F
const DirectX::SimpleMath::Vector4 PScenePhaseWeaponShop::STRING_COLOR(0.7f, 0.7f, 0.7f, 1.f);

//�l�i
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::STRING_PRICENUM_POSITION(830.f, 505.f);
//�U����
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::STRING_ATTACKNUM_POSITION(960.f, 575.f);
//�e��
const DirectX::SimpleMath::Vector2 PScenePhaseWeaponShop::STRING_BULLETNUM_POSITION(960.f, 645.f);




/*=====================
�R���X�g���N�^
=====================*/
PScenePhaseWeaponShop::PScenePhaseWeaponShop()
	:
	PlayScenePhaseBase(),
	mpPlayScene(nullptr),
	mpWeaponManager(nullptr),
	mpBackTexture(nullptr),
	mSelectWeaponNum(1),
	mpShopCursor(nullptr),
	mpBackGroundTexture(nullptr),
	mpRotWeaponSample(nullptr),
	mpFixedPointCamera(nullptr),
	mpTextureBlinking(nullptr),
	mSelectWeaponBulletNum(0),
	mSelectWeaponPrice(0),
	mSelectWeaponAttackNum(0),
	mpWeaponExplanatory(nullptr),
	mDefenceBackFlag(false)
{
	mpWeaponManager = std::make_unique<WeaponManager>();
	mpShopCursor = std::make_unique<Cursor>();
	mpBackGroundTexture = std::make_unique<ObjectTexture>();
	mpRotWeaponSample = std::make_unique<RotWeaponSample>();
	mpFixedPointCamera = std::make_unique<FixedPointCamera>();
	mpBackTexture = std::make_unique<ObjectTexture>();
	mpTextureBlinking = std::make_unique<Blinking>();
	mpWeaponExplanatory = std::make_unique<WeaponExplanatory>();
}

/*=====================
�f�X�g���N�^
=====================*/
PScenePhaseWeaponShop::~PScenePhaseWeaponShop()
{
}

/*=====================
����������
=====================*/
void PScenePhaseWeaponShop::Initialize(PlayScene* pPlayScene)
{
	//���\�[�X�̊m��
	auto pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture("WeaponBackGround");

	//�|�C���^�̕ۑ�
	mpPlayScene = pPlayScene;

	//�J�[�\���̏���������
	mpShopCursor->Initialize(
		CURSOR_INIT_POSITION,
		CURSOR_SCALE,
		CURSOR_SHIFT);

	//�摜�ǂݍ��ݏ���
	mpBackGroundTexture->Initialize();
	mpBackTexture->Initialize();

	//�w�i�摜�̏���������
	mpBackGroundTexture->SetTexture(texture);
	mpBackGroundTexture->SetPosition(BACKGROUND_TEXTURE_INIT_POSITION);
	mpBackGroundTexture->SetScale(BACKGROUND_TEXTURE_SCALE);

	//�W�����{���f���̏���������
	mpRotWeaponSample->Initialize();

	//����Ǘ��N���X�̏���������
	mpWeaponManager->Initialize(PlayScenePhaseBase::GetBulletManager());

	//����Ή���������ɐ؂�ւ���
	this->ChangeInfoSelectWeapon();

	//�_�ŉ摜�̉摜�ݒ菈��
	texture = pRM->GetTexture("Back");
	mpBackTexture->SetTexture(texture);
	mpBackTexture->SetScale(BACK_TEX_SCALE);
	mpBackTexture->SetPosition(BACK_TEX_POSITION);

	//�ŏ��̓}�V���K����ݒ肵�Ă���(�ŏ��̍��ڂ̓}�V���K���Œ�)
	//�Ώۂ̃��f����W�����f����
	DirectX::Model* model =
		mpWeaponManager->GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->
		WeaponBase::GetWeaponModel()->GetModel();

	mpRotWeaponSample->SetWeaponModel(model);

	//����Ή���������ɐ؂�ւ���
	this->ChangeInfoSelectWeapon();

	//�������̏���������
	mpWeaponExplanatory->Initialize();
}

/*=====================
�X�V����
=====================*/
void PScenePhaseWeaponShop::Update()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//�_�ŏ����̍X�V
	mpTextureBlinking->Update();

	//����I������
	this->SelectWeapon();

	//�W�����{���f���̍X�V����
	mpRotWeaponSample->Update();


	//�h�q�֖߂鏈��
	if (pKey->Back()|| pGamePad->Back())
	{
		ScreenTransitionInterface& pSTI = ScreenTransitionInterface::GetScreenTransitionInstance();

		mDefenceBackFlag = true;
		//���C�v����
		if (pSTI.GetWipe()->IsOpen())
		{
			pSTI.SetWipeUseFlag(true);
			pSTI.GetWipe()->SetClose();
			return;
		}	
	}
	if (mDefenceBackFlag)
	{
		ScreenTransitionInterface& pSTI = ScreenTransitionInterface::GetScreenTransitionInstance();
		//�e��ݒ肷��

		//�h�q�t�F�[�Y��
		mpPlayScene->ChangePhaseToDefence();

		//���Z�b�g�������s��
		mpPlayScene->GetPhase()->Reset();

		//���C�v����
		pSTI.SetWipeUseFlag(true);
		pSTI.GetWipe()->SetOpen();
	}
}

/*==============================
State�ύX�O�̃��Z�b�g����
================================*/
void PScenePhaseWeaponShop::Reset()
{
	//��_�J�����Ɉړ�
	mpPlayScene->ChangeFixedCamera();

	//�J�����s����擾
	CameraInfoIF& pPVIf = CameraInfoIF::GetCameraInfoIFInstance();

	//��_�J�����ɕύX����
	mpFixedPointCamera->SetEyePosition(PIXED_CAMERA_POSITION);			//���W�w��
	pPVIf.SetProjection(mpFixedPointCamera->GetProjectionMatrix());
	pPVIf.SetView(mpFixedPointCamera->GetViewMatrix());

	mDefenceBackFlag = false;

	//���C�v����
	ScreenTransitionInterface& pSTI = ScreenTransitionInterface::GetScreenTransitionInstance();
	pSTI.SetWipeUseFlag(true);
	pSTI.GetWipe()->SetOpen();
}

/*================================
�`�揈��
================================*/
void PScenePhaseWeaponShop::Draw()
{
	//�w�i�̕`��
	mpBackGroundTexture->Draw();

	//�J�[�\���̕`��
	mpShopCursor->Draw(true);

	//�W�����{���f���̕`�揈��
	mpRotWeaponSample->Draw();

	//�������̕`��
	PlayScenePhaseBase::GetUI()->DrawMoneyTexture();


	//�l�i�̕`��
	Utility::DrawString(mSelectWeaponPrice, STRING_PRICENUM_POSITION, STRING_COLOR, Utility::STRING_SIZE_MEDIUM);

	//�U���͒l�̕`��
	Utility::DrawString(mSelectWeaponAttackNum, STRING_ATTACKNUM_POSITION, STRING_COLOR, Utility::STRING_SIZE_MEDIUM);

	//�e���̕`��
	Utility::DrawString(mSelectWeaponBulletNum, STRING_BULLETNUM_POSITION, STRING_COLOR, Utility::STRING_SIZE_MEDIUM);

	//�������̕`��
	mpWeaponExplanatory->Draw(STRING_COLOR);
	 
	if (mpTextureBlinking->GetBlinkingFlag())
	{
		mpBackTexture->Draw();
	}
}

/*===============================
�����I������:private
=================================*/
void PScenePhaseWeaponShop::SelectWeapon()
{
	//�J�[�\����������
	this->ShopCursorDown();

	//�J�[�\�����グ��
	this->ShopCursorUp();

	//����𔃂�
	this->BuyWeapon();
}


/*=================================
�J�[�\����������:private
=================================*/
void PScenePhaseWeaponShop::ShopCursorUp()
{

	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (pKey->SelectOver()|| pGamePad->ChangeCursorUp())
	{
		//�ő�X�e�[�W���ł͂Ȃ��Ȃ珈����ʂ�
		if (mSelectWeaponNum - 1 != static_cast<int>(eWeaponType::NONE))
		{
			//�摜�����
			mpShopCursor->CursorUp();
			mSelectWeaponNum--;

			//�Ώۂ̃��f����W�����f����
			DirectX::Model* model= 
				mpWeaponManager->GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->
				WeaponBase::GetWeaponModel()->GetModel();

			mpRotWeaponSample->SetWeaponModel(model);

			//����Ή���������ɐ؂�ւ���
			this->ChangeInfoSelectWeapon();

			//�Љ�̕ύX
			mpWeaponExplanatory->Update(static_cast<eWeaponType>(mSelectWeaponNum));

		}
	}
}

/*=================================
�J�[�\����������:private
=================================*/
void PScenePhaseWeaponShop::ShopCursorDown()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (pKey->SelectUnder()|| pGamePad->ChangeCursorDown())
	{
		//�ŏ��X�e�[�W���ł͂Ȃ��Ȃ珈����ʂ�
		if (mSelectWeaponNum + 1 != static_cast<int>(eWeaponType::NUM))
		{
			//�摜������
			mpShopCursor->CursorDown();
			mSelectWeaponNum++;

			//�Ώۂ̃��f����W�����f����
			DirectX::Model* model =
				mpWeaponManager->GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->
				WeaponBase::GetWeaponModel()->GetModel();

			mpRotWeaponSample->SetWeaponModel(model);

			//����Ή���������ɐ؂�ւ���
			this->ChangeInfoSelectWeapon();

			//�Љ�̕ύX
			mpWeaponExplanatory->Update(static_cast<eWeaponType>(mSelectWeaponNum));
		}
	}
}


/*========================================
����𔃂�:private
=========================================*/
void PScenePhaseWeaponShop::BuyWeapon()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//��������{�^���������ꂽ��
	if (pKey->Decision()|| pGamePad->Decision())
	{
		//����������邩�ǂ����`�F�b�N
		Money& pM = Money::GetMoneyInstance();
		int money = pM.GetMoney();

		int weaponprice=
			mpWeaponManager->
			GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->
			GetWeaponPrice();

		//�������̂ق�������������
		if (money >= weaponprice)
		{
			//�����������炵��
			pM.ReduceMoney(weaponprice);

			PlayScenePhaseBase::GetUI()->CreateMoneyEffect(weaponprice);

			//�v���C���[�̕����Ԃ�ύX���Ă���
			PlayScenePhaseBase::GetPlayer()->ChangePlayerActionStateAttackEnemy();
			PlayScenePhaseBase::GetPlayer()->GetAttackEnemy()->UseStrongWeapon();

			//����������ς���
			PlayScenePhaseBase::GetPlayer()->GetAttackEnemy()->ChangeStrongWeapon
			(
				static_cast<eWeaponType>(mSelectWeaponNum)
			);

			//����摜��ύX����
			PlayScenePhaseBase::GetUI()->ChangeActionInfoTexture(ePlayerActionState::ATTACK_ENEMY);
			PlayScenePhaseBase::GetUI()->
				ChangeActionInfoTexture(static_cast<eWeaponType>(mSelectWeaponNum));
		}
	}
}

/*========================================
����Ή���������ɐ؂�ւ���:private
=========================================*/
void PScenePhaseWeaponShop::ChangeInfoSelectWeapon()
{

	//�Ώۂ̕���̑��e�����擾
	mSelectWeaponBulletNum = mpWeaponManager->
		GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->GetBulletNum();

	//�Ώۂ̕���̋��z���擾
	mSelectWeaponPrice = mpWeaponManager->
		GetWeapon(static_cast<eWeaponType>(mSelectWeaponNum))->GetWeaponPrice();

	//�Ώۂ̕���̍U���͂��擾
	mSelectWeaponAttackNum = PlayScenePhaseBase::GetBulletManager()->GetBulletType()->
		GetBulletInfomation(static_cast<eWeaponType>(mSelectWeaponNum))->mBulletAttackNum;
}
