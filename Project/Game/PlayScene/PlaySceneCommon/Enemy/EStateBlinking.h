/*
�G�s���p�^�[��
�쐬���F2021/08/31
*/
#pragma once

#include"EnemyStateBase.h"
#include"../DamageTimer.h"

class EStateBlinking :public EnemyStateBase
{
private:
	//�G�_�ŃC���^�[�o��
	static const int ENEMY_BLINKING_INTERVAL;

	//�ۑ��p�ϐ�
	Enemy* mpEnemy;

	std::unique_ptr<DamageTimer> mpDamageTimer;

public:
	//�R���X�g���N�^
	EStateBlinking();

	//�f�X�g���N�^
	~EStateBlinking()override;

	//����������
	 void Initialize(Enemy * pEnemy)override;

	//�X�V����
	 void Update()override;

	//State�J�n���̏���������
	 void Reset()override;

private:
	//�����蔻���ݒ肷��
	void SetAABBCollider()override {}
};