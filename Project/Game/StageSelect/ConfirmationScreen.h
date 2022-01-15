/*
�m�F���
�쐬���F2021/10/21
*/
#pragma once

//�O���錾
#include"../Common/ObjectTexture.h"
#include"../Common/Cursor.h"

class ConfirmationScreen
{
private:

	//�摜�g�嗦
	static const DirectX::SimpleMath::Vector2 CONFI_TEX_SCALE;
	//�������W
	static const DirectX::SimpleMath::Vector2 CONFI_TEX_INIT_POSITION;

	//�����`��
	//���ʏ���
	//�g�嗦
	static const float STRING_SCALE;
	//YES
	//���W
	static const  DirectX::SimpleMath::Vector2 STRING_YES_POSITION;
	//No
	//���W
	static const  DirectX::SimpleMath::Vector2 STRING_NO_POSITION;

	//�m�F��ʗp�J�[�\���̊�{���
	//�g�嗦
	static const DirectX::SimpleMath::Vector2 CONFI_CURSOR_SCALE;
	//�������W
	static const DirectX::SimpleMath::Vector2 CONFI_CURSOR_INIT_POSITION;
	//�ړ���
	static const float CONFI_CURSOR_SHIFT;

	//�����e�N�X�`��
	//�g�嗦
	static const  DirectX::SimpleMath::Vector2 STRING_TEXTURE_SCALE;
	//���W
	static const  DirectX::SimpleMath::Vector2 STRING_TEXTURE_POSITION;

	//�摜
	std::unique_ptr<ObjectTexture> mpConfirTexture;

	//�I���J�[�\��
	std::unique_ptr<Cursor> mpCursor;

	//���ݑI�����Ă���I����
	bool mSelectFlag;

	//�����e�N�X�`��
	std::unique_ptr<ObjectTexture> mpStringTexture;

public:

	//�R���X�g���N�^
	ConfirmationScreen();
	//�f�X�g���N�^
	~ConfirmationScreen();
	//����������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw(bool const& blinkingFlag);

	//�I���t���O�̃A�N�Z�T
	bool GetSelectFlag() const { return mSelectFlag; }


private:

	//�����̕`��
	void DrawString(bool const& blinkingFlag);

};

