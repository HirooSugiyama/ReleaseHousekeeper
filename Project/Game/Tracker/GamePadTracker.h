/*
�R���g���[���[�̎擾(�V���O���g��)
�{�^�����͂͋ɗ͐��𑝂₵�����Ȃ��̂ŁA�����Ēǉ����ɂ����`�ō쐬���Ă��܂��B
*/

#pragma once

#include<GamePad.h>

class GamePadTracker
{
public:

	//�������g�̎擾
	static GamePadTracker* GetGamePadTrackerInstance()
	{
		static GamePadTracker gpt;

		return &gpt;
	}

private:

	//�v���C���[�P
	static const int PLAYER_ONE;

	//�g�p����{�^���ꗗ
	enum class eUseButton
	{
		LT,RT,				//�㕔�g���K�[

		RIGHT_STICK_LEFT,	//�E�X�e�B�b�N������
		RIGHT_STICK_RIGHT,	//�E�X�e�B�b�N�E����
		RIGHT_STICK_UP,		//�E�X�e�B�b�N�����
		RIGHT_STICK_DOWN,	//�E�X�e�B�b�N������

		LEFT_STICK_LEFT,	//���X�e�B�b�N������
		LEFT_STICK_RIGHT,	//���X�e�B�b�N�E����
		LEFT_STICK_UP,		//���X�e�B�b�N�����
		LEFT_STICK_DOWN,	//���X�e�B�b�N������

		CROSS_BUTTON_LEFT,	//�\���{�^��������
		CROSS_BUTTON_RIGHT,	//�\���{�^���E����
		CROSS_BUTTON_UP,	//�\���{�^�������
		CROSS_BUTTON_DOWN,	//�\���{�^��������


		BACK,				//�߂�{�^��
		START,				//�J�n�{�^��
		XBOX_BUTTON			//Xbox�{�^��
	};


	//�g���b�J�[
	DirectX::GamePad::ButtonStateTracker  mTracker;

	// �{�^��
	std::unique_ptr<DirectX::GamePad> mpGamePad;


	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete�B
	GamePadTracker(GamePadTracker const& kt) = delete;
	GamePadTracker operator=(GamePadTracker const& kt) = delete;

	//�R���X�g���N�^
	GamePadTracker();
	//�f�X�g���N�^
	~GamePadTracker() = default;

	//�{�^������(�x�[�X�ƂȂ�֐�)
	bool PushButton(eUseButton button);
	bool PressButton(eUseButton button);

	//�����I��
	//bool Quit() { return this->PushButton(eUseButton::XBOX_BUTTON); }

public:
	//�X�V����
	void ButtonUpdate();

	//�g�p�p�r�̐������֐����쐬����

	//����
	bool Decision() { return this->PushButton(eUseButton::START); }
	//�߂�
	bool Back() { return this->PushButton(eUseButton::BACK); }

	//�J�[�\���ړ�
	bool ChangeCursorDown() { return this->PushButton(eUseButton::CROSS_BUTTON_DOWN); }
	bool ChangeCursorUp() { return this->PushButton(eUseButton::CROSS_BUTTON_UP); }


	//�ړ�
	bool MoveLeft() { return this->PressButton(eUseButton::LEFT_STICK_LEFT); }
	bool MoveRight() { return this->PressButton(eUseButton::LEFT_STICK_RIGHT); }
	bool MoveUp() { return this->PressButton(eUseButton::LEFT_STICK_UP); }
	bool MoveDown() { return this->PressButton(eUseButton::LEFT_STICK_DOWN); }
	bool Move()
	{
		return this->MoveLeft() || this->MoveRight() || this->MoveUp() || this->MoveDown();
	}
	
	//�v���C���[�̏�ԕύX
	bool ChangePlayerActionUp() { return this->PushButton(eUseButton::RIGHT_STICK_UP); }
	bool ChangePlayerActionDown(){return this->PushButton(eUseButton::RIGHT_STICK_DOWN);}

	//�v���C���[�̕���ύX
	bool ChangePlayerWeapon()
	{
		return this->PushButton(eUseButton::RIGHT_STICK_LEFT) || this->PushButton(eUseButton::RIGHT_STICK_RIGHT);
	}

	//�v���C���[�̍s���{�^��
	bool ActionPlayer() { return this->PressButton(eUseButton::RT); }

	bool AttackStrongPlayer() { return this->PushButton(eUseButton::RT); }

	//�J�����ύX����
	bool ChangeCamera() { return this->PushButton(eUseButton::LT); }

	//�X�L�b�v
	bool Skip() { return this->PushButton(eUseButton::START); }


private:

	//���s�I������
	void ForcedTermination();
};