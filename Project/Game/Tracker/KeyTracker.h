/*
�L�[�{�[�h�g���b�J�[�̎擾(�V���O���g��)
�L�[���͂͋ɗ͐��𑝂₵�����Ȃ��̂ŁA�����Ēǉ����ɂ����`�ō쐬���Ă��܂��B
*/
#pragma once

#include<Keyboard.h>

class KeyTracker
{
public:
	//�������g�̎擾
	static KeyTracker* GetKeyTrackerInstance()
	{
		static KeyTracker kt;

		return &kt;
	}

private:

	//�g�p����L�[�ꗗ
	enum class eUseKey
	{
		ENTER,			//�e�팈��
		W, A, S, D,		//�ړ�
		SPACE,			//�s��
		UP, DOWN,		//�s���؂�ւ�
		LEFT, RIGHT,	//����؂�ւ�

		DEBUG_G,	//�f�o�b�O����
		DEBUG_R,	//�f�o�b�O����
	};


	//�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker mTracker;

	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> mKeybord;

	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete�B
	KeyTracker(KeyTracker const& kt) = delete;
	KeyTracker operator=(KeyTracker const& kt) = delete;

	//�R���X�g���N�^
	KeyTracker();
	//�f�X�g���N�^
	~KeyTracker() = default;

	//�L�[����(�x�[�X�ƂȂ�֐�)
	bool PushKey(eUseKey key);
	bool PressKey(eUseKey key);

public:
	//�X�V����
	void KeyUpdate();

	//�g�p�p�r�̐������֐����쐬����

	//����
	bool Decision() { return this->PushKey(eUseKey::ENTER); }

	//����
	bool SelectUnder() { return this->PushKey(eUseKey::DOWN); }

	//���
	bool SelectOver() { return this->PushKey(eUseKey::UP); }

	//���s
	bool WalkForward() { return this->PressKey(eUseKey::W); }
	bool WalkBack() { return this->PressKey(eUseKey::S); }
	bool WalkLeft() { return this->PressKey(eUseKey::A); }
	bool WalkRight() { return this->PressKey(eUseKey::D); }

	bool Walk()
	{
		return this->WalkForward() || this->WalkBack() || this->WalkLeft() || this->WalkRight();
	}


	//���U��
	bool PushActionStrongAttack() { return this->PushKey(eUseKey::SPACE); }
	bool PressActionStrongAttack() { return this->PressKey(eUseKey::SPACE); }

	//��U��
	bool ActionWeekAttack() { return this->PushKey(eUseKey::SPACE); }
	//�ǂ����Ă�
	bool ActionDefenseHouse() { return this->PushKey(eUseKey::SPACE); }

	//����؂�ւ�
	//�U����Ԃ�؂�ւ�
	bool SwitchToWeapon()
	{
		bool flag = false;
		if (this->PushKey(eUseKey::LEFT) || this->PushKey(eUseKey::RIGHT))	flag = true;
		return flag;
	}

	//�s����Ԑ؂�ւ�
	//�U����ԂɕύX
	bool SwitchToAttack() { return this->PushKey(eUseKey::UP); }
	//�h���Ԃɐ؂�ւ�
	bool SwitchToDefenseHouse() { return this->PushKey(eUseKey::DOWN); }

	//�X�L�b�v
	bool Skip() { return this->PushKey(eUseKey::ENTER); }

	//�߂�
	bool Back() { return this->PushKey(eUseKey::LEFT); }

	//����]
	bool LeftRotation() { return this->PressKey(eUseKey::LEFT); }

	//�E��]
	bool RightRotation() { return this->PressKey(eUseKey::RIGHT); }

	//�J�����؂�ւ�����
	bool ChangeCamera() { return this->PushKey(eUseKey::ENTER); }

	//Debug����
	bool DEBUGPRESS() { return this->PressKey(eUseKey::DEBUG_G); }
	bool DEBUGPUSH() { return this->PushKey(eUseKey::DEBUG_R); }

private:

	//���s�I������
	void ForcedTermination();
};