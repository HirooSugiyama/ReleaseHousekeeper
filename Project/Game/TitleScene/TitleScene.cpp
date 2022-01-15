/*
�^�C�g���V�[��
*/

#include "pch.h"

#include <WICTextureLoader.h>
#include <SimpleMath.h>

#include "../GameMain.h"
#include "DeviceResources.h"

#include "TitleScene.h"

#include"Game/Common/Cloud.h"

//�T�E���h�֌W
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"

//���S�̍��W
const DirectX::SimpleMath::Vector2 TitleScene::TITLE_LOGO_POSITION(190.f, 160.f);


/*=========================================
�R���X�g���N�^
=========================================*/
TitleScene::TitleScene()
	:
	mpCloud(),
	mBGMID(Utility::EXCEPTION_NUM)
{
	//�_�̐���
	mpCloud = std::make_unique<Cloud>();
}

/*=========================================
�f�X�g���N�^
=========================================*/
TitleScene::~TitleScene()
{
}

/*=========================================
������
=========================================*/
void TitleScene::Initialize()
{
	// ���\�[�X�֌W�̏����ݒ�
	//���\�[�X�}�l�[�W���ɉ摜��ۑ�����
	auto pRM = ResourceManager::GetInstance();
	pRM->SetuseScene(eLoadScene::TITLE);//�v���C�V�[���Ŏg�����\�[�X�̎w��
	pRM->Initialize(L"Resources/CSV/Resources.csv");

	// �e�N�X�`���̓ǂݍ���
	mpTexture = pRM->GetTexture("TitleTexture");
	mpLogo = pRM->GetTexture("TitleLogo");
	
	//�����_�̏���������
	mpCloud->Initialize();

	//BGM�𗬂�
	this->PlayBGM();
}

/*=========================================
�X�V
����	�F�^�C�}�[�̃w���p�[�֐�
�߂�l	�F���̃V�[���ԍ�
=========================================*/
eGameScene TitleScene::Update()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();


	// �}�E�X���͏����擾����
	auto mouseState = DirectX::Mouse::Get().GetState();

	mpCloud->Update();

	// �T�E���h�̍X�V
	ADX2::GetInstance().Update();

	if (pKey->Decision()|| pGamePad->Decision())//�L�[���͂��s��ꂽ��
	{
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_CHOICE);
		//�Ȃ��~�߂�
		this->StopBGM();
		return eGameScene::STAGE_SELECT;//���̃V�[����
	}

	return eGameScene::NONE;
}

/*=========================================
�`��
=========================================*/
void TitleScene::Draw()
{
	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();
	//�`��J�n
	pDxIF.GetSpriteBatch()->Begin
	(
		DirectX::SpriteSortMode_Deferred,
		pDxIF.GetCommonStates()->NonPremultiplied()
	);

	DirectX::SimpleMath::Vector2 pos{ 0.f,0.f };

	pDxIF.GetSpriteBatch()->Draw(mpTexture.Get(), pos);
	
	mpCloud->Draw();

	pDxIF.GetSpriteBatch()->Draw(mpLogo.Get(), TITLE_LOGO_POSITION);
	

	pDxIF.GetSpriteBatch()->End();
}

/*=========================================
�I������
=========================================*/
void TitleScene::Finalize()
{
	// ���\�[�X�֌W�̏�����
	auto pRM = ResourceManager::GetInstance();
	pRM->Finalize();

	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();
	pDxIF.Destroy();
}

/*========================================
���y�𗬂�:private
=========================================*/
void TitleScene::PlayBGM()
{
	mBGMID = ADX2::GetInstance().Play(CRI_CUESHEET_0_BGM_TITLE);
}

/*=========================================
���y���~�߂�:private
=========================================*/
void TitleScene::StopBGM()
{
	ADX2::GetInstance().Stop(mBGMID);
}
