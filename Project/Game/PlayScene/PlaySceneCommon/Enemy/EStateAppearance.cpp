/*
�G�s���p�^�[��
�쐬���F2021/08/31
*/


#include"pch.h"
#include "EStateAppearance.h"

//�O���錾
#include"Enemy.h"

//�O���錾
#include"../../Effect/Effect.h"

//�֐��̎g�p
#include"../ObjectModel/BoxModel.h"
#include"../../Effect/EffectManager.h"
#include"Libraries/MyLibraries/Camera.h"


//���f���ړ��X�s�[�h
const float EStateAppearance::ENEMY_MODEL_MOVE_VELOCITY = 0.02f;
//���f��Y���ő�l
const float EStateAppearance::ENEMY_MODEL_MAX_POSITIONY = 1.f;

/*============================
�R���X�g���N�^
============================*/
EStateAppearance::EStateAppearance()
	:
	EnemyStateBase(),
	mpEnemy(nullptr),
	mpCamera(nullptr),
	mpAppearanceEffect(nullptr)
{
}

/*============================
�f�X�g���N�^
============================*/
EStateAppearance::~EStateAppearance()
{
}

/*============================
����������
�����F�G�̃|�C���^
============================*/
void EStateAppearance::Initialize(Enemy* pEnemy)
{
	//�|�C���^�̕ۑ�
	mpEnemy = pEnemy;

	//�G�t�F�N�g�̐ݒ�
	this->SetEffect();
}

/*============================
�X�V����
============================*/
void EStateAppearance::Update()
{
	//�^�ϊ��p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 castpos = DirectX::SimpleMath::Vector3::Zero;
	castpos.y += ENEMY_MODEL_MOVE_VELOCITY;

	//���f�����ړ�������
	mpEnemy->GetBoxModel()->Move(castpos);

	//����Y�����ő�l�ƂȂ�����
	if (mpEnemy->GetBoxModel()->GetPosition().y >= ENEMY_MODEL_MAX_POSITIONY)
	{
		mpEnemy->ChangeStateWalk();

		//�G�t�F�N�g���̃t���O������
		mpAppearanceEffect->SetSpriteFlag(false);
	}
}

/*============================
�`�揈��
============================*/
void EStateAppearance::Draw()
{
}

/*============================
State�J�n���̏���������
============================*/
void EStateAppearance::Reset()
{

}

/*============================
�G�t�F�N�g�̐ݒ�:private
============================*/
void EStateAppearance::SetEffect()
{
	DirectX::SimpleMath::Vector3 pos = mpEnemy->GetBoxModel()->GetPosition();
	pos.y = ENEMY_MODEL_MAX_POSITIONY;

	//�G�t�F�N�g�}�l�[�W���[�̎擾
	auto pEM = EffectManager::GetInstance();

	mpAppearanceEffect = pEM->GetEffect(eEffectType::SPAWN);
	mpAppearanceEffect->SetPosition(pos);
	mpAppearanceEffect->SetSpriteFlag(true);
}

