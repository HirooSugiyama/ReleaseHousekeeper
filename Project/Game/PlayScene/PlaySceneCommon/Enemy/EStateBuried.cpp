/*
�G�s���p�^�[��
�쐬���F2021/08/31
*/


#include"pch.h"
#include "EStateBuried.h"

//�O���錾
#include"Enemy.h"

//�֐��̎g�p
#include"../Shadow.h"
#include"../ObjectModel/BoxModel.h"


//�e���g��`��
const DirectX::SimpleMath::Vector2 EStateBuried::ENEMY_SHADOW_SCLAE_UP(1.5f, 1.5f);

//�e�̍����𒲐�
const float EStateBuried::ENEMY_SHADOW_SHIFT_POSITIONY = 1.f;

/*============================
�R���X�g���N�^
============================*/
EStateBuried::EStateBuried()
	:
	EnemyStateBase(),
	mpEnemy(nullptr)
{
}

/*============================
�f�X�g���N�^
============================*/
EStateBuried::~EStateBuried()
{
}

/*============================
����������
�����F�G�̃|�C���^
============================*/
void EStateBuried::Initialize(Enemy* pEnemy)
{
	//�|�C���^�̕ۑ�
	mpEnemy = pEnemy;

	//�ȗ����ϐ��̐錾
	DirectX::SimpleMath::Vector2 baseScale= DirectX::SimpleMath::Vector2::Zero;

	//XZ���ʂɕϊ�
	baseScale.x = mpEnemy->GetBoxModel()->GetScale().x;
	baseScale.y = mpEnemy->GetBoxModel()->GetScale().z;

	//�e���T�C�Y��ς���
	mpEnemy->GetShadow()->SetScale(baseScale * ENEMY_SHADOW_SCLAE_UP);	//XZ����
}

/*============================
�`�揈��
============================*/
void EStateBuried::Draw()
{
	//�ȗ����ϐ��̐錾
	DirectX::SimpleMath::Vector3 pos = mpEnemy->GetBoxModel()->GetPosition();
	pos.y = ENEMY_SHADOW_SHIFT_POSITIONY;

	mpEnemy->GetShadow()->Draw(pos);
}

/*============================
���̏����֓������֐�
============================*/
void EStateBuried::ChangeNextState()
{

	//�ȗ����ϐ��̐錾
	DirectX::SimpleMath::Vector2 baseScale = DirectX::SimpleMath::Vector2::Zero;

	//XZ���ʂɕϊ�
	baseScale.x = mpEnemy->GetBoxModel()->GetScale().x;
	baseScale.y = mpEnemy->GetBoxModel()->GetScale().z;

	//�e���T�C�Y��ς���
	mpEnemy->GetShadow()->SetScale(baseScale);	//XZ����

	//���̏�����
	mpEnemy->ChangeStateAppearance();
}
