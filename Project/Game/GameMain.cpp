//
// Scene.cpp
//
#include "pch.h"

#include "DeviceResources.h"
#include "GameMain.h"


#include "Game/TitleScene/TitleScene.h"
#include "Game/StageSelect/StageSelectScene.h"
#include "Game/PlayScene/PlayScene.h"

//�e��V�[���C���^�[�t�F�[�X
#include"Game/Interface/SceneInterface/PtoRSceneInterface.h"
#include"Game/Interface/SceneInterface/StoPSceneInterface.h"


//�������̎擾
#include"Money/Money.h"
#include"Libraries/MyLibraries/Adx2.h"

//�Q�[���p�b�h�A�C�R��
//���W
const DirectX::SimpleMath::Vector2 GameMain::GAMEPAD_ICON_POSITION(0.f,0.f);
//�g�嗦
const DirectX::SimpleMath::Vector2 GameMain::GAMEPAD_ICON_SCALE(0.f,0.f);


/*=========================================
�R���X�g���N�^
=========================================*/
GameMain::GameMain()
	: 
	mNextScene(eGameScene::TITLE),		// �����V�[���̐ݒ�
	mpScene(nullptr)
{
}


/*=========================================
�f�X�g���N�^
=========================================*/
GameMain::~GameMain()
{
	this->Finalize();

	// �T�E���h�̏I������
	ADX2::GetInstance().Finalize();
}


/*=========================================
����������
=========================================*/
void GameMain::Initialize()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	// �}�E�X
	mMouse = std::make_unique<DirectX::Mouse>();
	mMouse->SetWindow(pDR->GetHwnd());

	// �T�E���h�̏�����
	ADX2::GetInstance().Initialize
	("Resources/Audio/Housekeeper_Sound.acf", "Resources/Audio/CueSheet_0.acb");

	//���C�v����
	ScreenTransitionInterface& pSTI = ScreenTransitionInterface::GetScreenTransitionInstance();
	pSTI.GetWipe()->Initialize();
	pSTI.GetFade()->Initialize();


	// �V�[���쐬
	this->CreateScene();

}

/*=========================================
�X�V
=========================================*/
void GameMain::Update(const DX::StepTimer& timer)
{
	//�L�[�{�[�h�̍X�V����
	this->KeyboardUpdate();

	//�Q�[���p�b�h�̍X�V����
	this->GamePadUpdate();

	//�^�C�}�[�̍X�V
	TimerInterface& pTM = TimerInterface::GetTimerInstance();
	pTM.SetTimer(timer);

	//���C�v����
	ScreenTransitionInterface& pSTI = ScreenTransitionInterface::GetScreenTransitionInstance();
	bool flag{ false };
	if (pSTI.GetWipeUseFlag())
	{
		flag = pSTI.GetWipe()->Update(static_cast<float>(pTM.GetTimer().GetElapsedSeconds()));
		if (flag)pSTI.SetWipeUseFlag(false);
	}
	else if (pSTI.GetFadeUseFlag())
	{
		//�t�F�[�h����
		flag = pSTI.GetFade()->Update(static_cast<float>(pTM.GetTimer().GetElapsedSeconds()));
		if (flag)pSTI.SetFadeUseFlag(false);
	}
	
	

	//���C�v���Ȃ珈�������Ȃ�
	if (pSTI.GetWipeUseFlag())return;

	//�t�F�[�h�C�����Ȃ珈�������Ȃ�
	if (pSTI.GetFadeUseFlag()&&!pSTI.GetFade()->GetFlagOpen())return;

	// ���̃V�[�����ݒ肳��Ă�����V�[���؂�ւ�
	if (mNextScene != eGameScene::NONE)
	{
		// �V�[���폜
		DeleteScene();

		//���\�[�X�}�l�[�W���̓��e�̍폜
		auto pRM = ResourceManager::GetInstance();
		pRM->Finalize();//�������̊J��


	
		// �V�[���쐬
		CreateScene();
	}
	
	// ���Ԃ�����΍X�V
	if (mpScene != nullptr)
	{
		mNextScene = mpScene->Update();
	}

}


/*=========================================
�`��
=========================================*/
void GameMain::Render()
{
	// ���Ԃ�����Ε`��
	if (mpScene != nullptr)
	{
		mpScene->Draw();
	}

	//���C�v����
	ScreenTransitionInterface& pSTI = ScreenTransitionInterface::GetScreenTransitionInstance();
	pSTI.GetWipe()->Draw();
	pSTI.GetFade()->Draw();
}


/*=========================================
�I������
=========================================*/
void GameMain::Finalize()
{
	this->DeleteScene();

	//�e�V�[���C���^�[�t�F�[�X�̏��̍폜����
	//���V�[���J�ڂ��Ȃ������ꍇ�f�[�^�������Ă��Ȃ����ꂪ���邽�߂����Ŋm���ɍ폜����
	auto& pStoP = StoPSceneInterface::GetStoPIFInstance();
	pStoP.Destroy();
	auto& pPtoR = PtoRSceneInterface::GetPtoRIFInstance();
	pPtoR.Destroy();
	//���C�v����
	ScreenTransitionInterface& pSTI = ScreenTransitionInterface::GetScreenTransitionInstance();
	pSTI.Destroy();

	//�������̍폜����
	auto& pM = Money::GetMoneyInstance();
	pM.Destroy();

	//�^�C�}�[�Ǘ��̔j��
	TimerInterface& pTM = TimerInterface::GetTimerInstance();
	pTM.Destroy();
}

/*=========================================
�V�[���̍쐬:private
=========================================*/
void GameMain::CreateScene()
{
	// �V�[�����쐬����Ă���Ƃ��͏������Ȃ�
	if (mpScene != nullptr)
	{
		return;
	}

	// ���V�[���̍쐬
	switch (mNextScene)
	{
		case eGameScene::TITLE:
		{
			mpScene = new TitleScene();
			break;
		}
		case eGameScene::STAGE_SELECT:
		{
			mpScene = new StageSelectScene();
			break;
		}
		case eGameScene::PLAY:
		{
			mpScene = new PlayScene();
			break;
		}
		default:
		{
			// ��O�Ȃ̂ŏ����𒆒f
			return;
		}
	}

	// �쐬�����V�[����������
	mpScene->Initialize();

	//���ւ�Scene����������
	mNextScene = eGameScene::NONE;
}

/*=========================================
�V�[���̍폜�Fprivate
=========================================*/
void GameMain::DeleteScene()
{
	// �V�[�����쐬����Ă��Ȃ���Ώ������Ȃ�
	if (mpScene == nullptr)
	{
		return;
	}

	// ���V�[���̏I������
	mpScene->Finalize();

	// ���V�[���̍폜
	delete mpScene;
	mpScene = nullptr;
}

/*=========================================
�L�[�{�[�h�̍X�V����:private
=========================================*/
void GameMain::KeyboardUpdate()
{
	//�g���b�J�[�̎擾
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	pKey->KeyUpdate();
}

/*=========================================
�Q�[���p�b�h�̍X�V����:private
=========================================*/
void GameMain::GamePadUpdate()
{
	//�g���b�J�[�̎擾
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();
	pGamePad->ButtonUpdate();
}
