/*
�J�E���g�_�E���t�F�[�Y
�쐬���F2021/09/30
*/

#include"pch.h"
#include"PScenePhaseCountDown.h"

//������
#include"../PlayScene.h"

//�O���錾
#include"../PlaySceneCommon/Administrator/Timer.h"

//�֐������̎g�p
#include"Libraries/MyLibraries/Camera.h"
#include"../PlaySceneCommon/Player/Player.h"
#include"../PlaySceneCommon/ObjectModel/BoxModel.h"

//�J�E���g�_�E������
const int PScenePhaseCountDown::CountDown_MAX_NUM = 3;

//��ʒ����l
const DirectX::SimpleMath::Vector2 PScenePhaseCountDown::WINDOW_CENTER(1280.f / 2.f, 780.f / 2.f);


/*=====================
�R���X�g���N�^
=====================*/
PScenePhaseCountDown::PScenePhaseCountDown()
	:
	mpPlayScene(nullptr),
	mpCountDownTimer(nullptr),
	mpCountDownString(nullptr)
{
	mpCountDownTimer = std::make_unique<Timer>();
	mpCountDownString = std::make_unique<SpriteNumber2D>();
}

/*=====================
�f�X�g���N�^
=====================*/
PScenePhaseCountDown::~PScenePhaseCountDown()
{
}

/*===============================
����������
�����F�v���C�V�[���̃|�C���^
===============================*/
void PScenePhaseCountDown::Initialize(PlayScene* pPlayScene)
{
	//�|�C���^�̕ۑ�
	mpPlayScene = pPlayScene;

	//�J�E���g�_�E���ő厞�Ԃ�ݒ肷��
	mpCountDownTimer->SetMaxTime(CountDown_MAX_NUM);

	mpCountDownString->SetTextureKey("MoneyNumberFont");
	mpCountDownString->Initialize();

	mpCountDownString->SetScale(Utility::STRING_SIZE_SMALL);
}

/*=====================
�X�V����
=====================*/
void PScenePhaseCountDown::Update()
{
	//���Ԕ���p�ϐ�
	bool flag = mpCountDownTimer->Update();

	//�v���C���[�̈ʒu����E�o
	DirectX::SimpleMath::Vector3 playerpos =
		PlayScenePhaseBase::GetPlayer()->GetPlayerModel()->GetPosition();
	
	//�J�����̍X�V
	mpPlayScene->GetCameraPointer()->Update(playerpos);
	

	//�����J�E���g�_�E�����I�������
	if (flag)
	{
		//����State��
		mpPlayScene->ChangePhaseToDefence();
		mpPlayScene->GetPhase()->Reset();
	}
}

/*===============================
�`�揈��
===============================*/
void PScenePhaseCountDown::Draw()
{
	//�J�E���g�_�E����`�悷��
	int drawNum = mpCountDownTimer->GetMaxTime() - mpCountDownTimer->GetMainTimer();

	mpCountDownString->Create(drawNum, WINDOW_CENTER);
	mpCountDownString->Draw();
}

/*=====================
�`�揈��
=====================*/
void PScenePhaseCountDown::Reset()
{
	//�J������ύX
	mpPlayScene->ChangeMainCamera();

	//�J�����s����擾
	CameraInfoIF& pPVIf = CameraInfoIF::GetCameraInfoIFInstance();

	//��_�J�����ɕύX����
	pPVIf.SetProjection(mpPlayScene->GetCameraPointer()->GetProjectionMatrix());
	pPVIf.SetView(mpPlayScene->GetCameraPointer()->GetViewMatrix());
}
