/*
�h�q�t�F�[�Y
�쐬���F2021/06/16
*/

#include"pch.h"
#include "PScenePhaseDefense.h"

//������
#include"../PlayScene.h"



//��񋤗L�Ŏg�p
#include"Game/Interface/SceneInterface/PtoRSceneInterface.h"

//�G�t�F�N�g�̕`��Ŏg�p
#include"../Effect/EffectManager.h"

//�֐��̎g�p
#include"../PlaySceneCommon/Player/Player.h"
#include "../PlaySceneCommon/Player/PlayerActionState.h"
#include"../PlaySceneCommon/ObjectModel/BoxModel.h"
#include"../PlaySceneCommon/Enemy/EnemyManager.h"
#include"../PlaySceneCommon/Player/ActionStateBase.h"
#include"../PlaySceneCommon/Administrator/Administrator.h"
#include"../PlaySceneCommon/Administrator/Score.h"
#include"../PlaySceneCommon/Block/BlockManager.h"
#include"../PlaySceneCommon/GroundObject/GroundObjectManager.h"
#include"../PlaySceneCommon/Wall/WallManager.h"
#include"../PlaySceneCommon/GridLine/GridLineManager.h"
#include"../PlaySceneCommon/Administrator/Timer.h"
#include"../PlaySceneCommon/Player/ActionStateAttackEnemy.h"
#include"../PlaySceneCommon/Administrator/CelestialSphere.h"
#include"../PlayScenePhase/PScenePhaseEndAnimation.h"
#include"../PlaySceneCommon/Player/ActionStateDefenseHouse.h"
#include"../PlaySceneCommon/Bullet/BulletManager.h"
#include"../../UI/UI.h"

#include"Libraries/MyLibraries/CameraBase.h"

//�T�E���h�֌W
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"





//�J�������W
const DirectX::SimpleMath::Vector3 PScenePhaseDefense::PIXED_CAMERA_POSITION(0.0f, 55.0f, 1.0f);

/*=====================
�R���X�g���N�^
=====================*/
PScenePhaseDefense::PScenePhaseDefense()
	:
	PlayScenePhaseBase(),
	mpPlayScene(nullptr),
	mpDangerousLine(nullptr),
	mpSampleBlock(nullptr),
	mRedAssertFlag(false),
	mPhaseCount(1),
	mAllPhaseNum(0),
	mShopOpenFlag(false),
	mDefenseState(eDefenseState::MOVE),
	mMoveCameraSavePosition(DirectX::SimpleMath::Vector3::Zero),
	mWipeFlag(false)
{
	mpDangerousLine = std::make_unique<DangerousLine>();
	mpSampleBlock = std::make_unique<PreparingBlock>();
}

/*=====================
�f�X�g���N�^
=====================*/
PScenePhaseDefense::~PScenePhaseDefense()
{
}

/*=============================
����������
�����F�v���C�V�[���̃|�C���^
===============================*/
void PScenePhaseDefense::Initialize(PlayScene* pPlayScene)
{
	//�|�C���^�̕ۑ�
	mpPlayScene = pPlayScene;

	//�x�����C���̏���������
	mpDangerousLine->Initialize();
	//���{�u���b�N�̏���������
	mpSampleBlock->Initialize();

	//�|�C���^�̓s���ケ����ŏ�����
	PlayScenePhaseBase::GetPlayer()->Initialize
	(
		PlayScenePhaseBase::GetBlockManager(),
		PlayScenePhaseBase::GetAdministrator(),
		mpSampleBlock.get(),
		PlayScenePhaseBase::GetUI()
	);

	//�|�C���^�̕ۑ�
	PlayScenePhaseBase::GetPlayer()->GetAttackEnemy()->
		SetWeaponManagerPointer(PlayScenePhaseBase::GetWeaponManager());

	PlayScenePhaseBase::GetPlayer()->GetAttackEnemy()->
		SetBulletManagerPointer(PlayScenePhaseBase::GetBulletManager());

	mAllPhaseNum = mpPlayScene->GetMaxPhaseNum();
}

/*=====================
�X�V����
=====================*/
void PScenePhaseDefense::Update()
{
	//�J��������ۑ�
	CameraInfoIF& pCiIF = CameraInfoIF::GetCameraInfoIFInstance();

	//�I�u�W�F�N�g�̍X�V����
	this->ObjectUpdate();

	//�ԐF�_�ŃG�t�F�N�g�����邩�ǂ���
	this->RedAssertSet();

	//�J�����؂�ւ�����
	this->ChangeCamera();

	//�p�h���̏���E�o
	DirectX::SimpleMath::Vector3 playerpos
		= PlayScenePhaseBase::GetPlayer()->GetPlayerModel()->GetPosition();

	//�J�����̍X�V
	mpPlayScene->GetCameraPointer()->Update(playerpos);

	//�t�F�[�Y�X�V����
	this->PhaseToUpdate();

	//�J�����̈ʒu��ۑ�����
	DirectX::SimpleMath::Vector3 cameraPosition(DirectX::SimpleMath::Vector3::Zero);
	cameraPosition = mpPlayScene->GetCameraPointer()->GetEyePosition();
	pCiIF.SetCameraPosition(cameraPosition);


	//�v���C���[�̍U�����菈��
	//�U�����Ă��Ȃ�������ʂ��Ȃ�
	if (PlayScenePhaseBase::GetPlayer()->GetActionState() == ePlayerActionState::ATTACK_ENEMY)
	{
		PlayScenePhaseBase::GetEnemyManager()->
			ChackHitNormalAttackPlayerEnemy(PlayScenePhaseBase::GetPlayer());
	}	

	//�����蔻��̏���
	this->ColliderUpdate();

}

/*============================
State�ύX�O�̃��Z�b�g����
=============================*/
void PScenePhaseDefense::Reset()
{
	//�G�Ǘ��N���X�̃t�F�[�Y���X�V����
	PlayScenePhaseBase::GetEnemyManager()->SetNowPhaseNum(mPhaseCount);
	//�V����ς���
	PlayScenePhaseBase::GetAdministrator()->DirectAcceserCelestialSphere()->
		ChangeSphereModelNight();

	//�J������ύX
	mpPlayScene->ChangeMainCamera();

	//�J�����s����擾
	CameraInfoIF& pPVIf = CameraInfoIF::GetCameraInfoIFInstance();

	//��_�J�����ɕύX����
	pPVIf.SetProjection(mpPlayScene->GetCameraPointer()->GetProjectionMatrix());
	pPVIf.SetView(mpPlayScene->GetCameraPointer()->GetViewMatrix());
}

/*==============================
�`�揈��
================================*/
void PScenePhaseDefense::Draw()
{
	//�I�u�W�F�N�g�̕`�揈��
	this->ObjectDraw();

	/*������艺��Effect�̏����������Ȃ��ƕ\������Ȃ��I(�`�揇�̊֌W)*/
	//UI�̕`�揈��
	PlayScenePhaseBase::GetUI()->Draw();
	//�v���C���[�̏�Ԃ̕`��
	PlayScenePhaseBase::GetPlayer()->GetActionStateBase()->Draw();

	//�G�t�F�N�g�̕`�揈��
	EffectManager* pEM = EffectManager::GetInstance();
	pEM->Draw();
	
}

/*====================================
�I�u�W�F�N�g�̍X�V����:private
====================================*/
void PScenePhaseDefense::ObjectUpdate()
{
	//�v���C���[�̍X�V����
	PlayScenePhaseBase::GetPlayer()->Update();

	//�u���b�N�̍X�V����
	PlayScenePhaseBase::GetBlockManager()->Update();

	//�G�̍X�V����
	PlayScenePhaseBase::GetEnemyManager()->Update();

	//�e�Ǘ��N���X�̏���������
	PlayScenePhaseBase::GetBulletManager()->Update();

	//�����v���C���[���_���[�W���󂯂Ă����珈����ʂ��Ȃ�
	//�U�����Ă���Ƃ���������ʂ��Ȃ�
	if (PlayScenePhaseBase::GetPlayer()->GetPlayerState() != ePlayerState::DAMAGE &&
		PlayScenePhaseBase::GetPlayer()->GetActionState() != ePlayerActionState::ATTACK_ENEMY) 
	{
		//���{�u���b�N�̍X�V����
		mpSampleBlock->Update
		(
			PlayScenePhaseBase::GetPlayer()->GetPlayerModel()->GetPosition(),
			PlayScenePhaseBase::GetGridLineManager()
		);
	}

	//�Ǘ��҂̍X�V����
	PlayScenePhaseBase::GetAdministrator()->Update();

	//UI�ɏ���n��
	int scoreNum = PlayScenePhaseBase::GetAdministrator()->DirectAcceserScore()->GetScoreNum();
	int nowNum = PlayScenePhaseBase::GetEnemyManager()->GetBreakEnemyNum();
	int maxNum = PlayScenePhaseBase::GetEnemyManager()->GetMaxEnemyNum();

	PlayScenePhaseBase::GetUI()->SetAllEnemyNum(maxNum);
	PlayScenePhaseBase::GetUI()->SetRemainingEnemyNum(nowNum);
	PlayScenePhaseBase::GetUI()->SetScoreNum(scoreNum);


}
/*====================================
�����蔻��̏���:private
====================================*/
void PScenePhaseDefense::ColliderUpdate()
{
	//�G�ƃv���C���[�̓����蔻��v��
	PlayScenePhaseBase::GetEnemyManager()->
		ChackHitPlayerEnemy(PlayScenePhaseBase::GetPlayer());

	//���_�ƓG�̓����蔻��v��
	PlayScenePhaseBase::GetEnemyManager()->
		ChackHitProtecterEnemy(PlayScenePhaseBase::GetProtecter());

	//�u���b�N�ƓG�̓����蔻��
	PlayScenePhaseBase::GetBlockManager()->
		RoolEnemyManagerChackHit();

	//�n��I�u�W�F�N�g�ƓG�̓����蔻��
	PlayScenePhaseBase::GetGroundObjectManager()->
		RoolEnemyManagerChackHit(PlayScenePhaseBase::GetEnemyManager());

	// �u���b�N�ƌ��{�u���b�N�̓����蔻��`�u���b�N�̏d�Ȃ��h���`
	PlayScenePhaseBase::GetBlockManager()->
		ChackHitSampleBlockBlock(mpSampleBlock.get(), PlayScenePhaseBase::GetPlayer());

	//�u���b�N�ƃv���C���[�̓����蔻��
	PlayScenePhaseBase::GetBlockManager()->
		ChackhitPlayerBlock(PlayScenePhaseBase::GetPlayer());

	//��ƓG�̓����蔻�����
	PlayScenePhaseBase::GetWallManager()->
		RoolEnemyManagerChackHit(PlayScenePhaseBase::GetEnemyManager());

	//����p���C���ƌ��{�u���b�N�̓����蔻��
	PlayScenePhaseBase::GetGridLineManager()->
		ChackHitPreparingBlockGridLine(PlayScenePhaseBase::GetPlayer(), mpSampleBlock.get());

	//�v���C���[�ƒn��I�u�W�F�N�g�̓����蔻��
	PlayScenePhaseBase::GetGroundObjectManager()->
		ChackHitPlayerGroundObject(PlayScenePhaseBase::GetPlayer());


	//�x�����C���ƓG�̓����蔻��
	mRedAssertFlag = PlayScenePhaseBase::GetEnemyManager()->
		ChackHitDangerousLineEnemy(mpDangerousLine.get());

	//�e�ƓG�̓����蔻��
	PlayScenePhaseBase::GetEnemyManager()->
		RoolBulletManagerChackhit(PlayScenePhaseBase::GetBulletManager());

	//�u���b�N�ƒe�̏Փ˔���
	PlayScenePhaseBase::GetBulletManager()->
		RoolChackHitBlock(PlayScenePhaseBase::GetBlockManager());

	//�e�ƃv���C���[�̏Փ˔���
	PlayScenePhaseBase::GetBulletManager()->
		ChackHitBulletPlayer(PlayScenePhaseBase::GetPlayer());

	//�v���C���[�ƓG�̋�������
	PlayScenePhaseBase::GetEnemyManager()->
		ChackDistanceTargetEnemy(PlayScenePhaseBase::GetPlayer()->GetPlayerModel()->GetPosition(), true);
}

/*====================================
�I�u�W�F�N�g�̕`�揈��:private
====================================*/
void PScenePhaseDefense::ObjectDraw()
{
	//�x�����C���̕`�揈��
	mpDangerousLine->Draw();
}

/*===========================================
�ԐF�_�ŃG�t�F�N�g�����邩�ǂ���:private
===========================================*/
void PScenePhaseDefense::RedAssertSet()
{
	//�����t���O�������Ă�����
	if (mRedAssertFlag)
	{
		PlayScenePhaseBase::GetUI()->RedAssertControl(true);
	}
	//�����Ă��Ȃ�������
	else
	{
		PlayScenePhaseBase::GetUI()->RedAssertControl(false);
	}

}

/*===========================================
�t�F�[�Y�X�V����:private
===========================================*/
void PScenePhaseDefense::PhaseToUpdate()
{
	//�ȗ����ϐ��̐錾
	int nowtime = PlayScenePhaseBase::GetAdministrator()->DirectAcceserTimer()->GetMainTimer();
	int maxtime = PlayScenePhaseBase::GetAdministrator()->DirectAcceserTimer()->GetMaxTime();
	
	if (nowtime == maxtime)
	{
		//�t�F�[�Y�J�E���g���ő�ɂȂ�����
		if (mPhaseCount == mAllPhaseNum) 
		{
			//�X�R�A�̎擾
 			PtoRSceneInterface& pPR = PtoRSceneInterface::GetPtoRIFInstance();
			pPR.SetScoreNum(PlayScenePhaseBase::GetAdministrator()->DirectAcceserScore()->GetScoreNum());
			mpPlayScene->GetEndAnimation()->SetUseAnim(eUseEndAnim::WIN_TIME);
			mpPlayScene->ChangePhaseToEndAnimation();
			mpPlayScene->GetPhase()->Reset();
		}

		//�����J�E���g���X�V
		mPhaseCount++;
		//�G�Ǘ��N���X�̃t�F�[�Y���X�V����
		PlayScenePhaseBase::GetEnemyManager()->SetNowPhaseNum(mPhaseCount);

		//�T�E���h�Đ�
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_ENEMYSPAWN);

		//�^�C�}�[�����Z�b�g����
		PlayScenePhaseBase::GetAdministrator()->DirectAcceserTimer()->ResetMainTimer();
	}


	//�V���b�v�ւ̈ڍs����
	if (PlayScenePhaseBase::GetGroundObjectManager()->GetPlayerShopTouchFlag()&&
		mShopOpenFlag == false)
	{


		//��Ԉڍs�������s��
		mpPlayScene->ChangePhaseToWeaponShop();
		mpPlayScene->GetPhase()->Reset();

		//�t���O��t����
		mShopOpenFlag = true;
	}
	else if (!PlayScenePhaseBase::GetGroundObjectManager()->GetPlayerShopTouchFlag()&&
		mShopOpenFlag == true)
	{
		//�t���O���~�낷
		mShopOpenFlag = false;
	}


	
}

/*===========================================
�J�������_�ύX����:private
===========================================*/
void PScenePhaseDefense::ChangeCamera()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (!pKey->ChangeCamera()|| !pGamePad->ChangeCamera())
	{
		return;
	}

	switch (mDefenseState)
	{
		//�ړ���Ԃ������ꍇ
		case eDefenseState::MOVE:
		{
			mDefenseState = eDefenseState::PIXED;
			mMoveCameraSavePosition = mpPlayScene->GetCameraPointer()->GetEyePosition();

			//��_�J�����ɕύX����
			mpPlayScene->ChangeFixedCamera();
			mpPlayScene->GetCameraPointer()->SetEyePosition(PIXED_CAMERA_POSITION);			//���W�w��
			mpPlayScene->GetCameraPointer()->CalculationMatrix();

			//�J�����s����擾
			CameraInfoIF& pPVIf = CameraInfoIF::GetCameraInfoIFInstance();
			
			//��_�J�����ɕύX����
			pPVIf.SetProjection(mpPlayScene->GetCameraPointer()->GetProjectionMatrix());
			pPVIf.SetView(mpPlayScene->GetCameraPointer()->GetViewMatrix());
			break;
		}
		//��_�J�����������ꍇ
		case eDefenseState::PIXED:
		{
			mDefenseState = eDefenseState::MOVE;
			//��_�J�����ɕύX����
			mpPlayScene->ChangeMainCamera();
			mpPlayScene->GetCameraPointer()->SetEyePosition(mMoveCameraSavePosition);			//���W�w��
			//�J�����s����擾
			CameraInfoIF& pPVIf = CameraInfoIF::GetCameraInfoIFInstance();
			
			//��_�J�����ɕύX����
			pPVIf.SetProjection(mpPlayScene->GetCameraPointer()->GetProjectionMatrix());
			pPVIf.SetView(mpPlayScene->GetCameraPointer()->GetViewMatrix());

			break;
		}
	}
}
