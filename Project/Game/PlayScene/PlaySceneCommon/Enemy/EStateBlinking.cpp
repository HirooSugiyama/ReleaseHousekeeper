/*
�G�s���p�^�[��
�쐬���F2021/11/04
*/

#include"pch.h"
#include "EStateBlinking.h"

//�O���錾
#include"Enemy.h"

#include"../ObjectModel/BoxModel.h"

//�v���C���[�_�ŃC���^�[�o��
const int EStateBlinking::ENEMY_BLINKING_INTERVAL = 10;

/*============================
�R���X�g���N�^
============================*/
EStateBlinking::EStateBlinking()
	:
	EnemyStateBase(),
	mpEnemy(nullptr)
{
	mpDamageTimer = std::make_unique<DamageTimer>();
}

/*============================
�f�X�g���N�^
============================*/
EStateBlinking::~EStateBlinking()
{
}

/*============================
����������
�����F�G�̃|�C���^
============================*/
void EStateBlinking::Initialize(Enemy* pEnemy)
{
	//�|�C���^�̕ۑ�
	mpEnemy = pEnemy;
}

/*===========================
�X�V����
============================*/
void EStateBlinking::Update()
{
	//�_�ŏ�����������ɑ���
	bool flag = mpDamageTimer->RegularIntervalTimer(ENEMY_BLINKING_INTERVAL);
	mpEnemy->GetBoxModel()->SetDrawFlag(flag);

	//���Ԃ�������
	if (mpDamageTimer->Update())
	{
		mpEnemy->GetBoxModel()->SetDrawFlag(true);
		//���Ԃ������痧����Ԃɖ߂�
		mpEnemy->ChangeStateWalk();
	}
}

/*============================
State�J�n���̏���������
============================*/
void EStateBlinking::Reset()
{

}