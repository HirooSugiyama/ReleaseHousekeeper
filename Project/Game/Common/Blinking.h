/*
�_�ŏ����N���X

�쐬���F2021/11/01
*/
#pragma once

class Blinking
{
private:

	//�_�Ńt���O
	bool mBlinkingFlag;
	//sin�l
	float mSinfNum;
	//�_�ŊԊu
	float mBlinkingInterval;
	//�v���l
	float mBlinkingNum;

public:

	//�R���X�g���N�^
	Blinking(float intervalNum = 0.1f);
	//�f�X�g���N�^
	~Blinking();
	//�X�V����
	void Update();

	//�t���O�̃A�N�Z�T
	//�Ԃ�l�F�_�Ńt���O
	bool GetBlinkingFlag() { return mBlinkingFlag; }
};
