/*
�v���C���[�̍s����ԕ����X�e�[�g�p�^�[��
�쐬���F2021/09/14
*/
#pragma once


//���N���X
#include"ActionStateBase.h"

//�񋓌^�̎g�p
#include"Defense/eDefenseActionState.h"

//����
#include"Defense/DefenseActionBlockCreate.h"


class BlockManager;					//�|�C���^�ۑ��p
class PreparingBlock;				//�|�C���^�ۑ��p
class PreparingScarecrow;			//�|�C���^�ۑ��p

class ActionStateDefenseHouse :public ActionStateBase
{
private:

	//�ǌ�����
	std::unique_ptr<DefenseActionBlockCreate> mpBlockCreate;

	//���݂̏��
	eDefenseActionState mDefenseHouseState;

public:

	//�R���X�g���N�^
	ActionStateDefenseHouse();
	//�f�X�g���N�^
	~ActionStateDefenseHouse();
	//����������
	void Initialize(Player * pPlayer);

	//�|�C���^�ۑ�����
	void SetCreateBlockPointer(PreparingBlock* pPreparingBlock,
		BlockManager* pBlockManager);


	//�X�V����
	void Update();
	//State�J�n���̏���������
	void Reset();
	//�`�揈��
	void Draw();

	//�ǌ������ւ̃A�N�Z�X��
	DefenseActionBlockCreate* GetBlockCreate() {return mpBlockCreate.get();	}

	//���݂̏��
	eDefenseActionState GetDefenseHouseState(){return mDefenseHouseState;}
};
