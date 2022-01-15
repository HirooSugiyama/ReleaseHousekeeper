/*
�J�[�\�����Ǘ�����N���X
�쐬���F2021/10/13
*/
#pragma once
//����
#include"../Common/ObjectTexture.h"

class Cursor
{
private:

	//�摜�Ǘ��ϐ�
	std::unique_ptr<ObjectTexture> mpCursorTexture;

	//�ړ����ۑ��p�ϐ�
	float mShiftNum;

	//�������W�ۑ��p�ϐ�
	DirectX::SimpleMath::Vector2 mSaveInitPosition;

public:

	//�R���X�g���N�^
	Cursor();
	//�f�X�g���N�^
	~Cursor();
	//����������
	void Initialize(
		DirectX::SimpleMath::Vector2 const& initPosition,
		DirectX::SimpleMath::Vector2 const& scale,
		float const& shiftPosition,
		float const& rot=0.f);

	//�`�揈��
	void Draw(bool const& flag=true);

	//�J�[�\�������Ɉړ�����
	void CursorDown();

	//�J�[�\������Ɉړ�����
	void CursorUp();

	//�J�[�\���������ʒu�Ƀ��Z�b�g����
	void CursorReset();

	//�J�[�\������ԉ��ɃZ�b�g����
	void CursorSetUnder(int const& screenMaxStageNum);

};
