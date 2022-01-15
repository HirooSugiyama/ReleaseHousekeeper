/*
�ǂ����Ă铮��
�쐬���F2021/11/13
*/
#pragma once

class Player;					//�|�C���^�ۑ��p
class BlockManager;				//�|�C���^�ۑ��p
class PreparingBlock;			//�|�C���^�ۑ��p

class DefenseActionBlockCreate
{
private:

	//�u���b�N�̔�p
	static const int BLOCK_COST;

	//�|�C���^�ۑ��p�ϐ�
	Player* mpPlayer;
	PreparingBlock* mpPreparingBlock;
	BlockManager* mpBlockManager;


	//�u���b�N�̏d�Ȃ�t���O
	bool mOverLappingFlag;

	//����p���C���ƌ��{�p�u���b�N�̏d�Ȃ�t���O(true���d�Ȃ��Ă���)
	bool mGridLineFlag;


public:

	//�R���X�g���N�^
	DefenseActionBlockCreate();
	//�f�X�g���N�^
	~DefenseActionBlockCreate();
	//����������
	void Initialize(Player* pPlayer);


	//�|�C���^�ۑ�����
	void SetPointer(PreparingBlock* pPreparingBlock, BlockManager* pBlockManager);


	//�u���b�N����
	void Create();

	//�`�揈��
	void Draw();

	//�ǐ����t���O�̃A�N�Z�T
	void SetmOverLappingFlag(bool const& flag) { mOverLappingFlag = flag; }

	//����p���C���ƌ��{�p�u���b�N�̏d�Ȃ�t���O�̃A�N�Z�T
	void SetGridLineFlag(bool const& flag) { mGridLineFlag = flag; }
};
