/*
���ɓ��ʂȏ����������Ȃ��ǃN���X
�쐬���F2021/06/21
*/
#pragma once

//���N���X
#include"BlockKindBase.h"


class BKStateNormal:public BlockKindBase
{
private:
	//�ϐ�
	//Block�I�u�W�F�N�g�֕ۑ��p�̃|�C���^
	Block* mpBlock;

public:
	//�R���X�g���N�^
	BKStateNormal()
		:BlockKindBase()
		, mpBlock(nullptr)
	{}
	//�f�X�g���N�^
	~BKStateNormal()=default;
	//������
	void Initialize(Block* pBlock) override
	{
		mpBlock = pBlock;
	
	}
	//�X�V
	bool Update()override { return false; }

	//����������(�������֌W�ȊO)
	void Reset() {}
};