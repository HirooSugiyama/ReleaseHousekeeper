/*
�G�s���p�^�[��
�쐬���F2021/08/31
*/


#include"pch.h"
#include "EStateAttack.h"

//�֐��̎g�p
#include"../ObjectModel/BoxModel.h"

//�U���C���^�[�o��
const int EStateAttack::ENEMY_ATTACK_INTERVAL = 60;

//�G�̍U����
const int EStateAttack::ENEMY_ATTACK_POWER = 1;


/*============================
�R���X�g���N�^
============================*/
EStateAttack::EStateAttack()
	:
	EnemyStateBase(),
	mpAttackCollider(nullptr),
	mpEnemy(nullptr),
	mCurrentNum(0),
	mAttackBlockIndexNum(Utility::EXCEPTION_NUM)
{
}

/*============================
�f�X�g���N�^
============================*/
EStateAttack::~EStateAttack()
{
}

/*============================
����������
�����F�G�̃|�C���^
============================*/
void EStateAttack::Initialize(Enemy* pEnemy)
{
	//�|�C���^�̕ۑ�
	mpEnemy = pEnemy;
}

/*============================
�X�V����
============================*/
void EStateAttack::Update()
{
	mCurrentNum++;
}

/*============================
State�J�n���̏���������
============================*/
void EStateAttack::Reset()
{

}

/*=============================================
�U������^�C�~���O�v���֐�
�Ԃ�l�F�U�����邩�ۂ�(true�F�U������)
=============================================*/
bool EStateAttack::AttackTiming()
{

	//�U������^�C�~���O��������
	if (mCurrentNum >= ENEMY_ATTACK_INTERVAL)
	{
		//�l������������
		mCurrentNum = 0;

		return true;
	}

	return false;
}
