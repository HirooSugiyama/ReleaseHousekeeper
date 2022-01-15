/*
�G�s���p�^�[��
�쐬���F2021/08/31
*/
#pragma once

#include"EnemyStateBase.h"

class EStateBuried :public EnemyStateBase
{
private:

	//�e���g��`��
	static const DirectX::SimpleMath::Vector2 ENEMY_SHADOW_SCLAE_UP;
	//�e�̍����𒲐�
	static const float ENEMY_SHADOW_SHIFT_POSITIONY;

	//�ۑ��p�ϐ�
	Enemy* mpEnemy;

public:

	//�R���X�g���N�^
	EStateBuried();

	//�f�X�g���N�^
	~EStateBuried()override;

	//����������
	 void Initialize(Enemy * pEnemy)override;

	//�X�V����
	 void Update()override {};

	//State�J�n���̏���������
	 void Reset()override {};

	 //�`�揈��
	 void Draw()override;

	 //���̏����֓������֐�
	 void ChangeNextState();


private:
	//�����蔻���ݒ肷��
	void SetAABBCollider()override {};
};