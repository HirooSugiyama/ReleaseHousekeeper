/*
�G�s���p�^�[��
�쐬���F2021/08/31
*/
#pragma once

#include"EnemyStateBase.h"

//�O���錾
struct AABB;	//�Փ˔���p

class EStateAttack :public EnemyStateBase
{
private:

	//�U���C���^�[�o��
	static const int ENEMY_ATTACK_INTERVAL;

	//�G�̍U����
	static const int ENEMY_ATTACK_POWER;


	//�����蔻��ۑ��p�ϐ�
	AABB* mpAttackCollider;

	//�ۑ��p�ϐ�
	Enemy* mpEnemy;

	//�v���ϐ�
	int mCurrentNum;

	//�U�����̕ǔԍ�
	int mAttackBlockIndexNum;

public:

	//�R���X�g���N�^
	EStateAttack();

	//�f�X�g���N�^
	~EStateAttack()override;

	//����������
	 void Initialize(Enemy * pEnemy)override;

	//�X�V����
	 void Update()override;

	//State�J�n���̏���������
	 void Reset()override;

	 //�����蔻��̃A�N�Z�T
	 AABB* GetCollider() { return mpAttackCollider; }

	 //�O�����瓖���蔻������ہX���炤
	 void SetCollider(AABB* pAABB) { mpAttackCollider = pAABB; }


	 //�U������^�C�~���O�v���֐�
	 bool AttackTiming();

	 //�U���͂�Ԃ�
	 int GetAttackPower() { return ENEMY_ATTACK_POWER; }

	 //�U�����̕ǔԍ���ۑ�����
	 void SetAttackBlockNum(int i) { mAttackBlockIndexNum = i; }
	 int GetAttackBlockNum() { return mAttackBlockIndexNum; }
	 //�U�����̕ǔԍ�������������
	 void ResetAttackBlockNum() { mAttackBlockIndexNum = Utility::EXCEPTION_NUM; }


private:
	//�����蔻���ݒ肷��
	void SetAABBCollider()override {}
};