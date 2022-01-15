/*
�J��������t�F�[�Y
�쐬���F2021/10/11
*/

#include"pch.h"
#include"PScenePhaseRotationCamera.h"

//������
#include"../PlayScene.h"

//�֐������̎g�p
#include"../PlaySceneCommon/Administrator/Timer.h"
#include"../PlaySceneCommon/Player/Player.h"
#include"../PlaySceneCommon/ObjectModel/BoxModel.h"
#include"../../Common/ObjectTexture.h"

//�G�t�F�N�g�̕`��Ŏg�p
#include"../Effect/EffectManager.h"


//�J�E���g�_�E������
const int PScenePhaseRotationCamera::COUNTDOWN_MAX_NUM = 20;

//�X�L�b�v�{�^���̍��W
const DirectX::SimpleMath::Vector2 PScenePhaseRotationCamera::SKIPBOTTON_POSITION(0.f,0.f);

const DirectX::SimpleMath::Vector2 PScenePhaseRotationCamera::SKIPBOTTON_SCALE(0.15f,0.15f);

/*=====================
�R���X�g���N�^
=====================*/
PScenePhaseRotationCamera::PScenePhaseRotationCamera()
	:
	mpPlayScene(nullptr),
	mpCountDownTimer(nullptr),
	mpRotationCamera(nullptr),
	mpSkipButton(nullptr),
	mpSkipButtonBlinking(nullptr),
	mState(eRotationState::ROTATION)
{
	mpCountDownTimer = std::make_unique<Timer>();
	mpRotationCamera = std::make_unique<RotationCamera>();
	mpSkipButton = std::make_unique<ObjectTexture>();
	mpSkipButtonBlinking = std::make_unique<Blinking>();
}

/*=====================
�f�X�g���N�^
=====================*/
PScenePhaseRotationCamera::~PScenePhaseRotationCamera()
{
}

/*=====================
����������
=====================*/
void PScenePhaseRotationCamera::Initialize(PlayScene* pPlayScene)
{
	//���\�[�X�̎擾
	ResourceManager *pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture("Skip");

	mpSkipButton->SetTexture(texture);
	mpSkipButton->Initialize();
	mpSkipButton->SetPosition(SKIPBOTTON_POSITION);
	mpSkipButton->SetScale(SKIPBOTTON_SCALE);


	//�|�C���^�̕ۑ�
	mpPlayScene = pPlayScene;

	//�J�E���g�_�E���ő厞�Ԃ�ݒ肷��
	mpCountDownTimer->SetMaxTime(COUNTDOWN_MAX_NUM);

	//�V���O���g���֎擾(�擾�Ɠ����ɃJ��������l��Ⴂ�ۑ�����)
	CameraInfoIF& pCiIF = CameraInfoIF::GetCameraInfoIFInstance();
	pCiIF.SetView(mpRotationCamera->GetViewMatrix());
	pCiIF.SetProjection(mpRotationCamera->GetProjectionMatrix());

	ScreenTransitionInterface& pSTI = ScreenTransitionInterface::GetScreenTransitionInstance();
	pSTI.SetFadeUseFlag(true);
	pSTI.GetFade()->SetOpen();
}

/*=====================
�X�V����
=====================*/
void PScenePhaseRotationCamera::Update()
{
	//�_�ŏ����̍X�V
	mpSkipButtonBlinking->Update();

	//�X�L�b�v����
	bool skipFlag = this->Skip();

	bool timerFlag = false;

	switch (mState)
	{
		case eRotationState::ROTATION:
		{
			//���Ԕ���p�ϐ�
			timerFlag = mpCountDownTimer->Update();

			//�J�����̍X�V����
			mpRotationCamera->Update();
			break;
		}
		case eRotationState::FREE:
		{
			mpRotationCamera->Move();
			break;
		}
	}

	//�����X�L�b�v���ꂽ��
	if (skipFlag)
	{
		//����State��
		mpPlayScene->ChangePhaseToCountDown();	//�J�E���g�_�E����Ԃ�
		mpPlayScene->GetPhase()->Reset();
	}


	//�����J�E���g�_�E�����I�������
	if (timerFlag)
	{
		DirectX::SimpleMath::Vector3 playerpos =
			PlayScenePhaseBase::GetPlayer()->GetPlayerModel()->GetPosition();

		mpRotationCamera->Reset(playerpos);
		mState = eRotationState::FREE;
	}
}

/*====================
�`�揈��
=====================*/
void PScenePhaseRotationCamera::Draw()
{
	//�G�t�F�N�g�̕`�揈��
	EffectManager* pEM = EffectManager::GetInstance();
	pEM->Draw();

	if (mpSkipButtonBlinking->GetBlinkingFlag())
	{
		mpSkipButton->Draw();
	}
	
}

/*=================================
���Z�b�g����
=================================*/
void PScenePhaseRotationCamera::Reset()
{
	EffectManager* pEM = EffectManager::GetInstance();
	pEM->SetCameraPointer(mpRotationCamera.get());
}

/*=================================
�X�L�b�v����:private
�Ԃ�l�F�X�L�b�v���邩���Ȃ���
=================================*/
bool PScenePhaseRotationCamera::Skip()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//����Space�������ꂽ��
	if (pKey->Skip()|| pGamePad->Skip())
	{
		//���̏�Ԃ�
		return true;
	}

	return false;
}
