/*
�m�F���
�쐬���F2021/10/21
*/
#include"pch.h"

#include"ConfirmationScreen.h"

//�T�E���h�֌W
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"


//�摜�g�嗦
const DirectX::SimpleMath::Vector2 ConfirmationScreen::CONFI_TEX_SCALE(2.f, 2.f);
//�������W
const DirectX::SimpleMath::Vector2 ConfirmationScreen::CONFI_TEX_INIT_POSITION(250.f, 250.f);

//�����`��
//���ʏ���
//�g�嗦
const float ConfirmationScreen::STRING_SCALE = 3.f;
//YES
//���W
const DirectX::SimpleMath::Vector2 ConfirmationScreen::STRING_YES_POSITION(700.f, 350.f);
//No
//���W
const DirectX::SimpleMath::Vector2 ConfirmationScreen::STRING_NO_POSITION =
STRING_YES_POSITION + DirectX::SimpleMath::Vector2(0.f, 60.f);


//�m�F��ʗp�J�[�\���̊�{���
//�g�嗦
const DirectX::SimpleMath::Vector2 ConfirmationScreen::CONFI_CURSOR_SCALE(2.5f, 2.5f);
//�������W
const DirectX::SimpleMath::Vector2 ConfirmationScreen::CONFI_CURSOR_INIT_POSITION =
STRING_NO_POSITION + DirectX::SimpleMath::Vector2(-50.f, 20.f);
//�ړ���
const float ConfirmationScreen::CONFI_CURSOR_SHIFT = 60.f;


//�����e�N�X�`��
//�g�嗦
const  DirectX::SimpleMath::Vector2 ConfirmationScreen::STRING_TEXTURE_SCALE(1.f, 1.f);
//���W
const  DirectX::SimpleMath::Vector2 ConfirmationScreen::STRING_TEXTURE_POSITION =
CONFI_TEX_INIT_POSITION + DirectX::SimpleMath::Vector2(-250.f, -250.f);
/*===================================
�R���X�g���N�^
===================================*/
ConfirmationScreen::ConfirmationScreen()
	:mpConfirTexture()
	, mpCursor()
	, mSelectFlag(false)	//true:Yes,false:No
	, mpStringTexture()
{
	mpConfirTexture = std::make_unique<ObjectTexture>();
	mpCursor = std::make_unique<Cursor>();
	mpStringTexture = std::make_unique<ObjectTexture>();
}

/*==================================
�f�X�g���N�^
===================================*/
ConfirmationScreen::~ConfirmationScreen()
{
}

/*===================================
����������
===================================*/
void ConfirmationScreen::Initialize()
{
	//����������
	mpConfirTexture->Initialize();
	mpStringTexture->Initialize();

	//���\�[�X�̎擾
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture("Confir");

	//�摜�̐ݒ�
	mpConfirTexture->SetTexture(texture);

	//texture = pRM->GetTexture("English");
	texture = pRM->GetTexture("Japanise");
	mpStringTexture->SetTexture(texture);

	//�g�嗦�̐ݒ�
	mpConfirTexture->SetScale(CONFI_TEX_SCALE);
	mpStringTexture->SetScale(STRING_TEXTURE_SCALE);

	//���W�̐ݒ�
	mpConfirTexture->SetPosition(CONFI_TEX_INIT_POSITION);
	mpStringTexture->SetPosition(STRING_TEXTURE_POSITION);

	//�J�[�\���̏���������
	mpCursor->Initialize(
		CONFI_CURSOR_INIT_POSITION,
		CONFI_CURSOR_SCALE,
		CONFI_CURSOR_SHIFT);
}

/*=================================
�`�揈��
===================================*/
void ConfirmationScreen::Update()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//����������A���݂̑I������No�������ꍇ
	if ((pKey->SelectOver() || pGamePad->ChangeCursorUp()) && !mSelectFlag)
	{
		//Yes�Ƃ���
		mSelectFlag = true;

		//�J�[�\�����ړ�����
		mpCursor->CursorUp();
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_SELECT);
	}
	//����������A���݂̑I������Yes�������ꍇ
	else if ((pKey->SelectUnder() || pGamePad->ChangeCursorDown()) && mSelectFlag)
	{
		//No�Ƃ���
		mSelectFlag = false;
		//�J�[�\�����ړ�����
		mpCursor->CursorDown();
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_SELECT);
	}
}

/*==================================
�`�揈��
�����F�_�Ńt���O
===================================*/
void ConfirmationScreen::Draw(bool const& blinkingFlag)
{
	//�摜�̕`��
	mpConfirTexture->Draw();
	mpStringTexture->Draw();

	//�`�揈��
	mpCursor->Draw(true);

	//�����̕`�揈��
	this->DrawString(blinkingFlag);
}

/*==================================
�����̕`�揈��:private
�����F�_�Ńt���O
===================================*/
void ConfirmationScreen::DrawString(bool const& blinkingFlag)
{
	//�I������Yes�̎��_�ł�����
	if (mSelectFlag)
	{
		if (blinkingFlag)
		{
			//[Yes]�̕`��
			Utility::DrawString
			(
				L" Yes",
				STRING_YES_POSITION,
				DirectX::Colors::Black,
				STRING_SCALE
			);

		}
		//[No]�̕`��
		Utility::DrawString
		(
			L" No",
			STRING_NO_POSITION,
			DirectX::Colors::Black,
			STRING_SCALE
		);
	}
	else
	{
		//[Yes]�̕`��
		Utility::DrawString
		(
			L" Yes",
			STRING_YES_POSITION,
			DirectX::Colors::Black,
			STRING_SCALE
		);

		if (blinkingFlag)
		{
			//[No]�̕`��
			Utility::DrawString
			(
				L" No",
				STRING_NO_POSITION,
				DirectX::Colors::Black,
				STRING_SCALE
			);
		}
	}
}
