/*
���݂̃u���b�N�̏�Ԃ̏������s�����N���X
�쐬���F2021/06/21
*/
#pragma once

class Block;

class BlockKindBase
{
public:
	//�R���X�g���N�^
	BlockKindBase() {};
	//�f�X�g���N�^
	virtual ~BlockKindBase() = default;
	//������
	virtual void Initialize(Block* pBlock) = 0;
	//�X�V
	virtual bool Update() = 0;

	//����������(�������֌W�ȊO)
	virtual void Reset() = 0;

};