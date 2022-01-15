/*
�X�e�[�W�I���V�[��
*/

#include "pch.h"

#include "../GameMain.h"
#include "DeviceResources.h"

#include "StageSelectScene.h"


//�T�E���h�֌W
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"






//�ԍ��̏c�ړ�
const int StageSelectScene::SELECTNUM_VERTICAL_SHIFT = 5;

//�J�[�\���̊g�嗦
const DirectX::SimpleMath::Vector2 StageSelectScene::CURSOR_SCALE(0.6f,0.5f);
//�������W						  
const DirectX::SimpleMath::Vector2 StageSelectScene::CURSOR_INIT_POSITION(150.f,20.f);
//�ړ���							
const DirectX::SimpleMath::Vector2 StageSelectScene::CURSOR_VELOCITY(530.f, 150.f);
//�^�O�̏������W
const DirectX::SimpleMath::Vector2 StageSelectScene::TAG_INIT_POSITION(113.f, 142.f);
//��
const float StageSelectScene::TAG_SHIFT = 100.f;
//�m�F��ʗp�J�[�\���̊�{���
//�g�嗦
const DirectX::SimpleMath::Vector2 StageSelectScene::SELECT_CURSOR_SCALE(2.5f, 2.5f);
//�������W
const DirectX::SimpleMath::Vector2 StageSelectScene::SELECT_CURSOR_INIT_POSITION(30.f, 137.f);
//�ړ���
const float StageSelectScene::SELECT_CURSOR_SHIFT = 98.f;

//��̈ʒu
const DirectX::SimpleMath::Vector2 StageSelectScene::NAME_POSITION(450.f,15.f);
const DirectX::SimpleMath::Vector2 StageSelectScene::NAME_SCALE(2.f, 2.f);


/*=========================================
�R���X�g���N�^
=========================================*/
StageSelectScene::StageSelectScene()
	:
	mSelectNum(1),
	mpCursor(),
	mpStageInfo(),
	mpTag(),
	mpConfirScreen(),
	mpTextureBlinking(),
	mSelectFlag(false),
	mBGMID(Utility::EXCEPTION_NUM),
	mpCloud(nullptr),
	mpStageSelectNameTexture(nullptr)
{
	mpCursor = std::make_unique<Cursor>();
	mpStageInfo = std::make_unique<StageInfomation>();
	mpConfirScreen = std::make_unique<ConfirmationScreen>();
	mpTextureBlinking = std::make_unique<Blinking>();
	mpCloud = std::make_unique<Cloud>();
	mpStageSelectNameTexture = std::make_unique<ObjectTexture>();

	for (int i = 0; i< SCREEN_STEGE_MAX_NUM; i++)
	{
		mpTag[i] = std::make_unique<StageNumberTag>();
	}
}
/*========================================
�f�X�g���N�^
=========================================*/
StageSelectScene::~StageSelectScene()
{

}

/*=========================================
������
=========================================*/
void StageSelectScene::Initialize()
{
	// ���\�[�X�֌W�̏����ݒ�
	//���\�[�X�}�l�[�W���ɉ摜��ۑ�����
	auto pRM = ResourceManager::GetInstance();
	pRM->SetuseScene(eLoadScene::STAGE_SELECT);//�v���C�V�[���Ŏg�����\�[�X�̎w��
	pRM->Initialize(L"Resources/CSV/Resources.csv");

	// �e�N�X�`���̓ǂݍ���
	mpTexture = pRM->GetTexture("StageSelect");

	mpStageSelectNameTexture->SetTexture(pRM->GetTexture("StageSelectName"));
	mpStageSelectNameTexture->Initialize();
	mpStageSelectNameTexture->SetPosition(NAME_POSITION);
	mpStageSelectNameTexture->SetScale(NAME_SCALE);

	//�J�[�\���̏���������
	mpCursor->Initialize(
		SELECT_CURSOR_INIT_POSITION,
		SELECT_CURSOR_SCALE,
		SELECT_CURSOR_SHIFT);

	//�X�e�[�W�e����̏���������
	mpStageInfo->Initialize();

	for (int i = 0;  i < SCREEN_STEGE_MAX_NUM; i++)
	{
		mpTag[i]->Initialize();
	}

	//�X�e�[�W�ԍ���ۑ�����
	this->SetNumberTag();

	//�m�F��ʂ̏���������
	mpConfirScreen->Initialize();

	//�Ȃ𗬂�
	this->PlayBGM();

	//�_�̏���������
	mpCloud->Initialize();
}

/*=========================================
�X�V
����	�F�^�C�}�[�̃w���p�[�֐�
�߂�l	�F���̃V�[���ԍ�
=========================================*/
eGameScene StageSelectScene::Update()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//�X�e�[�W�I��
	this->StageSelect();

	//�_�ŏ���
	mpTextureBlinking->Update();

	//�_�̍X�V����
	mpCloud->Update();

	//�I����ʂȂ�
	if (mSelectFlag)
	{
		//�m�F��ʂ̍X�V����
		mpConfirScreen->Update();
	}


	if (pKey->Decision()|| pGamePad->Decision())		//����
	{	
		//�m�F��ʂȂ��
		if (mSelectFlag)
		{
			if (mpConfirScreen->GetSelectFlag())
			{
				//�v���C�V�[����
				//�X�e�[�W�I����ʂ���̏�񋤗L�Ǘ��N���X�̎擾
				StoPSceneInterface& pStoP = StoPSceneInterface::GetStoPIFInstance();

				pStoP.SetStageCSV(this->SetFileName());
				//�X�e�[�W�ԍ��������ɕۑ����Ă���
				pStoP.SetStageNumber(std::to_string(mSelectNum));

				ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_CHOICE);
				//�Ȃ��~�߂�
				this->StopBGM();

				ScreenTransitionInterface& pSTI = ScreenTransitionInterface::GetScreenTransitionInstance();
				pSTI.SetFadeUseFlag(true);
				pSTI.GetFade()->SetClose();

				return eGameScene::PLAY;	//���ڃv���C�V�[����
			}
			else
			{
				mSelectFlag = false;
			}
			
		}
		else
		{

			ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_CHOICE);
			mSelectFlag = true;
		}		
	}

	return eGameScene::NONE;
}

/*=======================================
�`��
=========================================*/
void StageSelectScene::Draw()
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

	//�_�̕`�揈��
	mpCloud->Draw();

	//��̕`��
	mpStageSelectNameTexture->Draw();
	

	//�I����ʂł͂Ȃ��Ȃ�
	if (!mSelectFlag)
	{
		//�J�[�\���̕`��
		mpCursor->Draw();

		//�X�e�[�W���̕`��
		mpStageInfo->Draw(mSelectNum);

		//�X�e�[�W�ԍ������ۑ�
		int stageScreenNum = mSelectNum;
		//����2��ʖڈȍ~�̃X�e�[�W�Ȃ�
		if (stageScreenNum >= static_cast<int>(eSelectNum::_7))
		{
			//1��ʕ��l�����炷
			stageScreenNum -= static_cast<int>(eSelectNum::_6);
		}

		for (int i = 0; i < SCREEN_STEGE_MAX_NUM; i++)
		{
			//�I�����Ă���X�e�[�W�̂ݓ_�ł�����
			if (stageScreenNum - 1 == i)
			{
				mpTag[i]->Draw(mpTextureBlinking->GetBlinkingFlag());
			}
			else
			{
				//����ȊO�͒ʏ�`��
				mpTag[i]->Draw();
			}

		}
	}
	else
	{
		//�J�[�\���̕`��
		mpCursor->Draw();

		//�X�e�[�W���̕`��
		mpStageInfo->Draw(mSelectNum);
		//�e�X�e�[�W�ԍ��̕`��
		for (int i = 0; i < SCREEN_STEGE_MAX_NUM; i++)
		{
			//����ȊO�͒ʏ�`��
			mpTag[i]->Draw();
		}
		
		mpConfirScreen->Draw(mpTextureBlinking->GetBlinkingFlag());
	}

	pDxIF.GetSpriteBatch()->End();
}

/*=========================================
�I������
=========================================*/
void StageSelectScene::Finalize()
{
	auto pRM = ResourceManager::GetInstance();
	pRM->Finalize();
	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();
	pDxIF.Destroy();
}


/*=========================================
���[�h�I��:private
=========================================*/
void StageSelectScene::StageSelect()
{
	//�I����ʂłȂ��Ȃ珈�����s��
	if (!mSelectFlag)
	{
		//�J�[�\�����グ��
		this->CursorUp();

		//�J�[�\����������
		this->CursorDown();
	}
}


/*=========================================
�t�@�C�����Z�o:private
=========================================*/
std::string StageSelectScene::SetFileName()
{
	std::string filetop = "Resources/CSV/PlayScene",
		filemiddle = "none",
		filebottom=".csv",
		filename="none";

	filemiddle = std::to_string(mSelectNum);
	
	filename = filetop + filemiddle + filebottom;
	return filename;
}

/*=========================================
�J�[�\����������:private
=========================================*/
void StageSelectScene::CursorUp()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (pKey->SelectOver()|| pGamePad->ChangeCursorUp())
	{
		//�ő�X�e�[�W���ł͂Ȃ��Ȃ珈����ʂ�
		if (mSelectNum-1 != static_cast<int>(eSelectNum::NONE))
		{
			//�摜�����
			mpCursor->CursorUp();
			mSelectNum--;
			ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_SELECT);
		}
		//7�ԂɂȂ�����J�[�\���ʒu�����Z�b�g����
		if (mSelectNum == static_cast<int>(eSelectNum::_7))
		{
			mpCursor->CursorReset();
			//�X�e�[�W�ԍ���ۑ�����
			this->SetNumberTag();
		}
		//6�ԂɂȂ�����w��̈ʒu�ɃJ�[�\�����Z�b�g����
		if (mSelectNum == static_cast<int>(eSelectNum::_6))
		{
			mpCursor->CursorSetUnder(static_cast<int>(eSelectNum::_6));
			//�X�e�[�W�ԍ���ۑ�����
			this->SetNumberTag();
		}
	}	
}

/*=========================================
�J�[�\����������:private
=========================================*/
void StageSelectScene::CursorDown()
{

	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();


	if (pKey->SelectUnder()|| pGamePad->ChangeCursorDown())
	{
		//�ŏ��X�e�[�W���ł͂Ȃ��Ȃ珈����ʂ�
		if (mSelectNum+1 != static_cast<int>(eSelectNum::NUM))
		{
			//�摜������
			mpCursor->CursorDown();
			mSelectNum++;
			ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_SELECT);
		}
		//7�ԂɂȂ�����J�[�\���ʒu�����Z�b�g����
		if (mSelectNum == static_cast<int>(eSelectNum::_7))
		{
			mpCursor->CursorReset();
			//�X�e�[�W�ԍ���ۑ�����
			this->SetNumberTag();
		}
		//6�ԂɂȂ�����w��̈ʒu�ɃJ�[�\�����Z�b�g����
		if (mSelectNum == static_cast<int>(eSelectNum::_6))
		{
			mpCursor->CursorSetUnder(static_cast<int>(eSelectNum::_6));
			//�X�e�[�W�ԍ���ۑ�����
			this->SetNumberTag();
		}
	}	
}

/*========================================
�ԍ���ݒ肷��:private
=========================================*/
void StageSelectScene::SetNumberTag()
{
	int index = 0;
	int stagenum = 0;
	//���Z�b�g����
	for (int i = 0; i < SCREEN_STEGE_MAX_NUM; i++)
	{
		mpTag[i]->SetStageNum(Utility::EXCEPTION_NUM);
	}
	
	//�㔼���Ȃ�
	if (mSelectNum <= static_cast<int>(eSelectNum::_6))
	{
		index = 0;
		stagenum = static_cast<int>(eSelectNum::_1);
	}
	else 
	{
		index = 0;
		stagenum = static_cast<int>(eSelectNum::_7);
	}

	//���Z�b�g����
	for (index; index < SCREEN_STEGE_MAX_NUM; index++,stagenum++)
	{
		mpTag[index]->SetStageNum(stagenum);

		mpTag[index]->SetPosition(TAG_INIT_POSITION+ DirectX::SimpleMath::Vector2(0.f,(index *TAG_SHIFT)));
		if (stagenum > static_cast<int>(eSelectNum::_8))
		{
			break;
		}
	}

}

/*=========================================
���y�𗬂�:private
=========================================*/
void StageSelectScene::PlayBGM()
{
	mBGMID = ADX2::GetInstance().Play(CRI_CUESHEET_0_BGM_STAGESELECT);
}

/*=========================================
���y���~�߂�:private
=========================================*/
void StageSelectScene::StopBGM()
{
	ADX2::GetInstance().Stop(mBGMID);
}
