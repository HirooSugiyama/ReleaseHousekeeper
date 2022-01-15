/*
�G�s���p�^�[��
�쐬���F2021/08/31
*/
#pragma once

#include"EnemyStateBase.h"

class EStateKnockBack :public EnemyStateBase
{
private:


	//�G���f�����W����̓����蔻��̍��̋���(�����蔻��̍��W)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_POSITION;

	//�g�嗦(�����蔻��)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_SCALE;


	//�ړ����x
	static const float ENEMY_MOVE_SPEED;

	//���x������
	static const float ENEMY_MOVE_SPEED_DECREASE;

	//���x�ŏ��l
	static const float ENEMY_MIN_VELOCITY;

	//�ړ��x�N�g��������������
	static const float ENEMY_MOVE_VELOCITY_SMALL;

	//�ړ��x�N�g���𔽓]������
	static const float ENEMY_MOVE_VELOCITY_REVERSE;



	//�����蔻��
	std::unique_ptr<AABB> mpKnockBackCollider;


	//�ۑ��p�ϐ�
	Enemy* mpEnemy;

	//�ړ��x�N�g���ۑ��p�ϐ�
	DirectX::SimpleMath::Vector3 mMoveVec;

public:
	//�R���X�g���N�^
	EStateKnockBack();

	//�f�X�g���N�^
	~EStateKnockBack()override;

	//����������
	void Initialize(Enemy* pEnemy)override;

	//�X�V����
	void Update()override;

	//State�J�n���̏���������
	void Reset()override;


	//�����蔻��̃A�N�Z�T
	AABB* GetCollider();	//�w�b�_�[�t�@�C���̓s����CPP�ŏ������s��

	//�ړ��x�N�g���̎擾
	void SetMoveVector(DirectX::SimpleMath::Vector3 movevec);

	//�m�b�N�o�b�N�̑��x��0�ɂ���
	void NoneKnockBackSpeed(){}


private:
	//�����蔻���ݒ肷��
	void SetAABBCollider()override;

	//Vector3�̂����̐�Βl���ł��傫���l��Ԃ��֐�
	float Vector3Max(DirectX::SimpleMath::Vector3 num);

};