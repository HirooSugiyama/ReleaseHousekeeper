/*
�R���g���[���[�̎擾(�V���O���g��)
�{�^�����͂͋ɗ͐��𑝂₵�����Ȃ��̂ŁA�����Ēǉ����ɂ����`�ō쐬���Ă��܂��B
*/


#include"pch.h"
#include "GamePadTracker.h"

//�v���C���[�P
const int GamePadTracker::PLAYER_ONE = 0;

/*==========================================================
�R���X�g���N�^
==========================================================*/
GamePadTracker::GamePadTracker()
	:
	mTracker(),
	mpGamePad(nullptr)
{
	// �{�^���֘A
	if (mpGamePad == nullptr)
	{
		mpGamePad = std::make_unique<DirectX::GamePad>();
	}	
}

/*========================================================
�{�^������(�x�[�X�ƂȂ�֐�)(�P����������)
�����F���͂���{�^��
�Ԃ�l�Ftrue�������Ă���	false��������Ă��Ȃ�
==========================================================*/
bool GamePadTracker::PushButton(eUseButton button)
{
	//�ȗ���
	using ButtonState = DirectX::GamePad::ButtonStateTracker::ButtonState;

	switch (button)
	{
		//���{�^��
		case eUseButton::LT:
		{
			if (mTracker.leftTrigger == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}

		case eUseButton::RT:
		{
			if (mTracker.rightTrigger == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}

		//�E�X�e�B�b�N
		case eUseButton::RIGHT_STICK_LEFT:
		{
			if (mTracker.rightStickLeft == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		case eUseButton::RIGHT_STICK_RIGHT:
		{
			if (mTracker.rightStickRight == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		case eUseButton::RIGHT_STICK_UP:
		{
			if (mTracker.rightStickUp == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		case eUseButton::RIGHT_STICK_DOWN:
		{
			if (mTracker.rightStickDown == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}

		//�\���L�[
		case eUseButton::CROSS_BUTTON_LEFT:
		{
			if (mTracker.dpadLeft == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		case eUseButton::CROSS_BUTTON_RIGHT:
		{
			if (mTracker.dpadRight == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		case eUseButton::CROSS_BUTTON_UP:
		{
			if (mTracker.dpadUp == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		case eUseButton::CROSS_BUTTON_DOWN:
		{
			if (mTracker.dpadDown == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		

		//�߂�{�^��
		case eUseButton::BACK:
		{
			if (mTracker.back == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		//�J�n�{�^��
		case eUseButton::START:
		{
			if (mTracker.start == ButtonState::PRESSED)
			{
				return true;
			}
			break;
		}
		//�P���������Ȃ��{�^���������ꍇ�͏������s��Ȃ�
		default:
		{
			break;
		}
	}

	return false;
}

/*==========================================================
�{�^������(�x�[�X�ƂȂ�֐�)(����������)
�����F���͂���{�^��
�Ԃ�l�Ftrue�������Ă���	false��������Ă��Ȃ�
==========================================================*/
bool GamePadTracker::PressButton(eUseButton button)
{
	//�ȗ���
	using ButtonState = DirectX::GamePad::ButtonStateTracker::ButtonState;

	// �{�^�����͏����擾����
	auto buttonState = mpGamePad.get()->GetState(PLAYER_ONE);

	switch (button)
	{

		case eUseButton::RT:
		{
			if (mTracker.rightTrigger == ButtonState::HELD)
			{
				return true;
			}
			break;
		}

		case eUseButton::LEFT_STICK_LEFT:
		{
			if (mTracker.leftStickLeft == ButtonState::HELD)
			{
				return true;
			}
			break;
		}
		case eUseButton::LEFT_STICK_RIGHT:
		{
			if (mTracker.leftStickRight == ButtonState::HELD)
			{
				return true;
			}
			break;
		}
		case eUseButton::LEFT_STICK_UP:
		{
			if (mTracker.leftStickUp == ButtonState::HELD)
			{
				return true;
			}
			break;
		}		
		case eUseButton::LEFT_STICK_DOWN:
		{
			if (mTracker.leftStickDown == ButtonState::HELD)
			{
				return true;
			}
			break;
		}

		//���������Ȃ��{�^���������ꍇ�͏������s��Ȃ�
		default:
		{
			break;
		}
	}


	return false;
}
/*==========================================================
�X�V����
==========================================================*/
void GamePadTracker::ButtonUpdate()
{
	// �{�^�����͏����擾����
	auto buttonState = mpGamePad.get()->GetState(PLAYER_ONE);
	if (!buttonState.IsConnected())return;

	mTracker.Update(buttonState);

	//�����I������
	this->ForcedTermination();
}


/*==========================================================
���s�I������
==========================================================*/
void GamePadTracker::ForcedTermination()
{
	// �{�^�����͏����擾����
	auto buttonState = mpGamePad.get()->GetState(PLAYER_ONE);
	//����Back�{�^���������ꂽ��
	//if (this->Quit())
	//{
	//	//�����I������
	//	PostQuitMessage(0);
	//}
}
