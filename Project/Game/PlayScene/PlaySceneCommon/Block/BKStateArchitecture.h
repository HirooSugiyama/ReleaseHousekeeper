/*
�ǂ����񂾂񗧂����̕ǒǉ�����
�쐬���F2021/07/21
*/
#pragma once


//���N���X
#include"BlockKindBase.h"

class BKStateArchitecture :public BlockKindBase
{
private:
	//�萔
	//���z���x
	static const float BLOCK_CREATE_SPEED;
	//�ϐ�
	//Block�I�u�W�F�N�g�֕ۑ��p�̃|�C���^
	Block* mpBlock;

	//������������Y���W
	float mFinishPositionY;

	//���܂�����Ԃ�Y���W
	float mBeginPositionY;

	//���z�X�s�[�h
	float mDefenseHouseSpeed;


public:

	//�R���X�g���N�^
	BKStateArchitecture();
	//�f�X�g���N�^
	~BKStateArchitecture()override;

	//������
	void Initialize(Block* pBlock)override;
	//�X�V
	bool Update() override;

	//����������(�������֌W�ȊO)
	void Reset();

private:
	//�ړ�����
	void DefenseHouse();
	//�����蔻��X�V����
	void UpdateCollider();

	//�����O�̒n�ʂɖ��܂�����Ԃ�Y���W���Z�o
	void CreateBeforePositionY();
	//State�ڍs����
	bool ChangeStateBlock();

};
