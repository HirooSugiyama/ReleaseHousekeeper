/*
�v���C�V�[��
*/
#pragma once

#include "../IScene.h"
#include "Game/GameMain.h"

#include"PlaySceneCommon/Wall/WallManager.h"
#include"PlaySceneCommon/Player/Player.h"
#include"PlaySceneCommon/Enemy/EnemyManager.h"
#include"PlaySceneCommon/Protecter.h"
#include"PlaySceneCommon/Administrator/Administrator.h"
#include"PlaySceneDefence/PreparingBlock.h"
#include"PlaySceneCommon/Ground.h"
#include"PlaySceneCommon/GroundObject/GroundObjectManager.h"
#include"PlaySceneCommon/GridLine/GridLineManager.h"
#include"PlaySceneCommon/Weapon/WeaponManager.h"
#include"PlaySceneCommon/Bullet/BulletManager.h"
#include"PlaySceneCommon/DamageTimer.h"
#include"PlaySceneCommon/Block/BlockManager.h"
#include"../UI/UI.h"
#include"Libraries/MyLibraries/FixedPointCamera.h"
#include"Libraries/MyLibraries/Camera.h"
#include"Libraries/MyLibraries/RotationCamera.h"

//#include"../Common/ObjectTexture.h"

//��Ԑ؂�ւ����N���X
#include"PlayScenePhase/PlayScenePhaseBase.h"

//��Ԑ؂�ւ��h���N���X
#include"PlayScenePhase/PScenePhaseDefense.h"
#include"PlayScenePhase/PScenePhaseCountDown.h"
#include"PlayScenePhase/PScenePhaseRotationCamera.h"
#include"PlayScenePhase/PScenePhaseResult.h"
#include"PlayScenePhase/PScenePhaseWeaponShop.h"
#include"PlayScenePhase/PScenePhaseEndAnimation.h"	



//�X�e�[�g�Ǘ�
#include"PlayScenePhase/PlayScenePhase.h"

//�O���錾
namespace DirectX
{
	class BasicEffect;
}

//�I�u�W�F�N�g�֌W
class WallManager;


//��Ԋ��N���X
class PlayScenePhaseBase;
//�J�������N���X
class CameraBase;

class PlayScene : public IScene
{
private:

	//���C�g���Ƃ炷����
	static const DirectX::SimpleMath::Vector3 LIGHT_DIRECTION;

	//�J����
	CameraBase* mpCamera;
	std::unique_ptr<FixedPointCamera> mpFixedCamera;
	std::unique_ptr<Camera> mpMainCamera;
	std::unique_ptr<RotationCamera> mpRotCamera;

	//�x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> mpBasicEffect;

	//�C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mpInputLayout;

	//�ǂ̃t�F�[�Y�ł��g�p����Q�[���I�u�W�F�N�g
	//�ǊǗ�
	std::unique_ptr<WallManager> mpWallManager;
	//�v���C���[
	std::unique_ptr<Player>	mpPlayer;
	//�G�Ǘ�
	std::unique_ptr<EnemyManager> mpEnemyManager;
	//�u���b�N�Ǘ�
	std::unique_ptr<BlockManager> mpBlockManager;
	//��
	std::unique_ptr<Protecter> mpProtecter;
	//�Ǘ��҃N���X
	std::unique_ptr<Administrator> mpAdministrator;
	//�n��
	std::unique_ptr<Ground> mpGround;
	//�n��I�u�W�F�N�g�Ǘ�
	std::unique_ptr<GroundObjectManager> mpGroundObjectManager;
	//�O���b�h���Ǘ�
	std::unique_ptr<GridLineManager> mpGridLineManager;
	//����Ǘ�
	std::unique_ptr<WeaponManager> mpWeaponManager;
	//�e�Ǘ�
	std::unique_ptr <BulletManager> mpBulletManager;
	//UI�Ǘ�
	std::unique_ptr <UI> mpUI;


	//state
	std::vector<std::unique_ptr<PlayScenePhaseBase>> mpPhaseVector;

	//Phase�p�^�[���̂��ߐ��|�C���^
	PlayScenePhaseBase* mpPSPhase;
	//�Ǘ��p�ϐ�
	ePlayScenePhase mPlayScenePhase;

	//�t�F�[�Y�J�E���g
	int mPhaseCount;

	//�݌v�t�F�[�Y��
	int mAllPhaseNum;

	//�N���A�t���O
	bool mClearFlag;

	//�X�e�[�W�ԍ�
	std::string mStageNumber;

	//BGM��ID
	int mBGMID;



public:

	/*===========================���N���X�Ő錾�ς݂̊֐�===========================*/

	// �R���X�g���N�^
	PlayScene();

	// �f�X�g���N�^
	~PlayScene();

	// ������
	void Initialize() override;

	// �X�V
	eGameScene Update() override;

	// �`��
	void Draw() override;

	// �I������
	void Finalize() override;

	//�N���A�t���O�����Ă�
	void SetClearFlag(bool flag) { mClearFlag = flag; }

	/*===========================State�֌W�̊֐�===========================*/
private:
	//Phase�؂�ւ��p�A�N�Z�T
	void ChangePhaseToRotationCamera()
	{
		mPlayScenePhase = ePlayScenePhase::ROTATION_CAMERA;
		mpPSPhase = (PlayScenePhaseBase*)mpPhaseVector[static_cast<int>(mPlayScenePhase)].get();
	}
public:
	void ChangePhaseToEndAnimation()
	{ 
		mPlayScenePhase = ePlayScenePhase::END_ANIMATION;
		mpPSPhase = (PlayScenePhaseBase*)mpPhaseVector[static_cast<int>(mPlayScenePhase)].get();
	}
	void ChangePhaseToCountDown() 
	{
		mPlayScenePhase = ePlayScenePhase::COUNTDOWN;
		mpPSPhase = (PlayScenePhaseBase*)mpPhaseVector[static_cast<int>(mPlayScenePhase)].get();
	}
	void ChangePhaseToDefence() 
	{ 
		mPlayScenePhase = ePlayScenePhase::DEFENCE;
		mpPSPhase = (PlayScenePhaseBase*)mpPhaseVector[static_cast<int>(mPlayScenePhase)].get();
	}
	void ChangePhaseToResult()
	{
		mPlayScenePhase = ePlayScenePhase::RESULT;
		mpPSPhase = (PlayScenePhaseBase*)mpPhaseVector[static_cast<int>(mPlayScenePhase)].get();
	}
	void ChangePhaseToWeaponShop() 
	{
		

		mPlayScenePhase = ePlayScenePhase::WEAPON_SHOP;
		mpPSPhase = (PlayScenePhaseBase*)mpPhaseVector[static_cast<int>(mPlayScenePhase)].get();
	}

	PlayScenePhaseBase* GetPhase() { return mpPSPhase; }

	//�X�e�[�W�ԍ��̎擾
	int GetStageNum() { return atoi(mStageNumber.c_str()); }

	//�J�����ύX����
	void ChangeMainCamera() { mpCamera = (CameraBase*)mpMainCamera.get(); }
	void ChangeRotCamera() { mpCamera = (CameraBase*)mpRotCamera.get(); }
	void ChangeFixedCamera() { mpCamera = (CameraBase*)mpFixedCamera.get(); }
	//�J�������擾
	CameraBase* GetCameraPointer() { return mpCamera; }

	PScenePhaseEndAnimation* GetEndAnimation()
	{
		return  (PScenePhaseEndAnimation*)mpPhaseVector[static_cast<int>(ePlayScenePhase::END_ANIMATION)].get();
	}

	//�ő�t�F�[�Y���̎擾
	int GetMaxPhaseNum()const { return mAllPhaseNum; }


	//BGM���~�߂�
	void StopBGM()override;


	/*===========================�֐����𕪊������֐�===========================*/
private:

	//�C���^�[�t�F�[�X��������擾
	void IntarfaceGetInfomation();

	//�I�u�W�F�N�g�̏�����
	void InitializeObject();
	//�I�u�W�F�N�g�̍X�V�A�`��֌W�̏�����State��ɂ�
	
	//���ʂ̍X�V����
	void UpdateCommon();

	//���ʂ̕`�揈��
	void DrawCommon();

	//�I�u�W�F�N�g�̏I������
	void FinalizeObject();

	//�ǂݍ��ޒn�`�I�u�W�F�N�g���Ǘ�����CSV�t�@�C�����w�肷��֐�
	std::string CreateLoadGroundObjectFileName(std::string stagenum);

	//FPS�\��
	void DEBUGString();

	//BGM�𗬂�
	void PlayBGM()override;

};