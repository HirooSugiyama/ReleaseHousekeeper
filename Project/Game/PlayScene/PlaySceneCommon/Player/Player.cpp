/*
�v���C���[�N���X
*/

#include<pch.h>

#include "Player.h"

//�O���錾
//State��������
#include"PStateStand.h"
#include"PStateWalk.h"
#include"PStateDamage.h"

//ActionState��������
#include"ActionStateDefenseHouse.h"
#include"ActionStateAttackEnemy.h"


//�|�C���^�ۑ��p
#include"../Block/BlockManager.h"
#include"../Administrator/Administrator.h"
#include"../../PlaySceneDefence/PreparingBlock.h"
#include"../../../UI/UI.h"

//�������W
const DirectX::SimpleMath::Vector3 Player::PLYAER_INIT_POSITION(0.5f,1.f,1.f);

//���f���̊g�嗦
	//�����ڗp
const DirectX::SimpleMath::Vector3 Player::PLAYER_MODEL_SCALE(0.5f, 0.5f, 0.5f);

//�v���C���[�͏c���Ȃ̂œ����蔻����c�ɐL�΂�
const float Player::PLAYER_COLLIDER_EXTEND_Y = 3.f;
//���ۂ̃v���C���[��Z�l�͂ƂĂ��������̂ŏ���������
const float Player::PLAYER_COLLIDER_EXTEND_Z = 0.2f;

//�V�[���h�p�j�b�V���p�Q�[�W�K�v��
const int Player::BLOCKBREAK_USE_GAUGENUM = 50;


//�V�[���h�p�j�b�V���p�g�嗦
const DirectX::SimpleMath::Vector3 Player::BLOCKBREAK_SCALE(30.f, 5.f, 0.5f);


/*===================================
�R���X�g���N�^
===================================*/
Player::Player()
	: 
	mpPlayerModel(),
	mpPreparingBlock(nullptr),
	mpBlockManager(nullptr),
	mpAdministrator(nullptr),
	mpUI(nullptr),
	mpStand(nullptr),
	mpWalk(nullptr),
	mpDamage(nullptr),
	mpPlayerState(nullptr),
	mState(ePlayerState::STAND),
	mpDefenseHouse(nullptr),
	mpAttackEnemy(nullptr),
	mpPlayerActionState(nullptr),
	mActionState(ePlayerActionState::BLOCK_CREATE),
	mOneFrameBeforePosition(DirectX::SimpleMath::Vector3::Zero),
	mpPlayerShadow(nullptr),
	mPlayerAttackWorldMatrix(DirectX::SimpleMath::Matrix::Identity)
{
	//��ԃI�u�W�F�N�g�𐶐�
	mpPlayerModel = std::make_unique<BoxModel>();

	mpStand = std::make_unique<PStateStand>();
	mpWalk = std::make_unique<PStateWalk>();
	mpDamage = std::make_unique<PStateDamage>();



	mpDefenseHouse = std::make_unique<ActionStateDefenseHouse>();
	mpAttackEnemy = std::make_unique<ActionStateAttackEnemy>();
	mpPlayerShadow = std::make_unique<Shadow>();
}

/*===================================
�f�X�g���N�^
===================================*/
Player::~Player()
{
}

/*===================================
����������
����	�FpBlockManager(�u���b�N�Ǘ��N���X�̃|�C���^)�ApAdministrator(�Ǘ��҃N���X�̃|�C���^)
		�@pPreparingBlock(���{�u���b�N�̃|�C���^)
===================================*/
void Player::Initialize
(
	BlockManager* pBlockManager,
	Administrator* pAdministrator,
	PreparingBlock* pPreparingBlock,
	UI* pUI
)
{
	//�|�C���^�̕ۑ�
	mpBlockManager = pBlockManager;
	mpAdministrator = pAdministrator;
	mpPreparingBlock = pPreparingBlock;
	mpUI = pUI;

	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();

		//�v���C���[
	auto palyermodel = pRM->GetCmoModel("Player0");
	mpPlayerModel->SetModel(palyermodel);

	//�ϐ��̐錾
	DirectX::SimpleMath::Vector3 rot;
		//�v���C���[
	mpPlayerModel->SetScale(PLAYER_MODEL_SCALE);
	mpPlayerModel->SetPosition(PLYAER_INIT_POSITION);

	/*�����蔻�萶��*/
	//�g�嗦�̔����̒l�𐶐�
	DirectX::SimpleMath::Vector3 halfsize = mpPlayerModel->ReturnHalfSize(PLAYER_MODEL_SCALE);
	halfsize.y *= PLAYER_COLLIDER_EXTEND_Y;
	halfsize.z *= PLAYER_COLLIDER_EXTEND_Z;

	//�ݒ�
	mpPlayerModel->SetAABBCollider(PLYAER_INIT_POSITION - halfsize, PLYAER_INIT_POSITION + halfsize);

	//��ԃI�u�W�F�N�g�̏���������
	mpStand->Initialize(this);
	mpWalk->Initialize(this);
	mpDamage->Initialize(this);

	//�s����ԃI�u�W�F�N�g�̏���������
	mpDefenseHouse->Initialize(this);
	mpDefenseHouse->SetCreateBlockPointer(mpPreparingBlock, mpBlockManager);
	mpAttackEnemy->Initialize(this);

	//�e�N���X�̏���������
	mpPlayerShadow->WrapInitialize();

	//�e�̃T�C�Y�w��
	mpPlayerShadow->SetScale(DirectX::SimpleMath::Vector2(PLAYER_MODEL_SCALE.x, PLAYER_MODEL_SCALE.z));



	//�ŏ��͗�����Ԃɐݒ�
	this->ChangeStateStand();

	//�ŏ��͕ǌ��ď����Őݒ�
	this->ChangePlayerActionStateDefenseHouse();
}

/*===================================
�X�V����
===================================*/
void Player::Update()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();


	//���f���̍X�V����
	mpPlayerModel->Update();

	//������ԂȂ��
	if (mState == ePlayerState::STAND)	//���f���`��̓s���ケ���ňړ�����������B
	{

		//���͂������	
		if (pKey->Walk()||pGamePad->Move())//�R���g���[���[��̑���
		{
			this->ChangeStateWalk();//������Ԃֈڍs
		}
	}

	//���݂̏�Ԃ̍X�V����
	mpPlayerState->Update();
	mpPlayerActionState->Update();

	//�s��State�ύX����
	this->ChangeAction();

	//�U���p���[���h���W�v�Z
	this->CalculationAttackMat();
}

/*===================================
�`�揈��
===================================*/
void Player::Draw()
{

	//������Ԃ̎��̓X�v���C�g�̃��f����`�悷��
	if (mState!=ePlayerState::STAND)
	{
		//���݂̏�Ԃ̕`�揈��
		mpPlayerState->Draw();
	}
	else 
	{
		mpPlayerModel->Draw();
	}

	//�e�N���X�̕`�揈��
	mpPlayerShadow->Draw(mpPlayerModel->GetPosition());
}


/*===================================
�I������
===================================*/
void Player::Finalize()
{
	//��ԃI�u�W�F�N�g�����Z�b�g
	mpStand.reset();
	mpWalk.reset();
	mpDamage.reset();
}


/*===================================
�����蔻��X�V����:pirivate
===================================*/
void Player::UpdateCollider()
{
	/*�����蔻��̍X�V*/
	//�����ł͕ۑ����ĂȂ����߃��f������Ăяo���B
	DirectX::SimpleMath::Vector3 modelpos, modelscale;
	modelpos = mpPlayerModel->GetPosition();
	modelscale = mpPlayerModel->GetScale();

	//�g�嗦�̔����̒l�𐶐�
	DirectX::SimpleMath::Vector3 halfsize = mpPlayerModel->ReturnHalfSize(modelscale);
	halfsize.y *= PLAYER_COLLIDER_EXTEND_Y;
	//�ݒ�
	mpPlayerModel->SetAABBCollider(modelpos - halfsize, modelpos + halfsize);
}

/*===========================
�s��State�ύX:pirivate
============================*/
void Player::ChangeAction()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();


	if (mActionState == ePlayerActionState::ATTACK_ENEMY &&
		( pKey->SwitchToDefenseHouse())|| pGamePad->ChangePlayerActionDown())
	{
		this->ChangePlayerActionStateDefenseHouse();
		mpUI->ChangeActionInfoTexture(mActionState);
	}
	else if (mActionState == ePlayerActionState::BLOCK_CREATE &&
		(pKey->SwitchToAttack())|| pGamePad->ChangePlayerActionUp())
	{
		this->ChangePlayerActionStateAttackEnemy();
		mpUI->ChangeActionInfoTexture(mActionState);
	}
}

/*==========================================
�U���p���[���h���W�̌v�Z:pirivate
===========================================*/
void Player::CalculationAttackMat()
{
	mPlayerAttackWorldMatrix = mpPlayerModel->GetRotationX() *
		mpPlayerModel->GetRotationY() *
		mpPlayerModel->GetRotationX() *
		DirectX::SimpleMath::Matrix::CreateTranslation(mpPlayerModel->GetPosition());
}
