/*
��������
�쐬���F2021/10/13
*/
#pragma once


#include <SimpleMath.h>


namespace DX
{
	class StepTimer;
}

class MoveNumber
{
private:

	//�����l
	float mFirstNum;

	//�ő�l(��������)
	int mTopNum;

	//������
	float mVelocityNum;

	//1�b������̑�����
	float mOneSecondVelocityNum;


public:

	//�R���X�g���N�^
	MoveNumber();
	//�f�X�g���N�^
	~MoveNumber();
	//����������
	void Initialize(int firstNum, float moveSecondSpeed, int maxNum);
	//�X�V����
	int Update( DX::StepTimer const& timer,bool fallflag=false);

	//���݂̐��l�̃A�N�Z�T
	int GetMoveNum() { return static_cast<int>(mFirstNum); }

	//�w��̒l�ɋ����ύX
	void ForcedChangeMoveNum() { mFirstNum = static_cast<float>(mTopNum); }

};
