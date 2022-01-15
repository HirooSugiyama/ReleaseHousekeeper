/*
��������e�̈ړ�����
�쐬���F2021/10/16
*/

#include"pch.h"
#include "BulletStateExplosion.h"

//�O���錾
#include"Bullet.h"

//�֐��̎g�p
#include"../ObjectModel/SphereModel.h"

//�G�t�F�N�g�̎擾
#include"../../Effect/EffectManager.h"
#include"../../Effect/Effect.h"

//�d�͒萔�̎g�p
#include"../../PlaySceneDefence/Gravity.h"

//�d�͒萔
const float BulletStateExplosion::GRAVITY = Gravity::mGravityConstant;

//�������x
const float BulletStateExplosion::FIRST_VELOCITY = 0.3f;

//�ŏ��̍���
const float BulletStateExplosion::FIRST_HEIGHT = 1.f;


//�G�t�F�N�g���o����������W
const DirectX::SimpleMath::Vector3 BulletStateExplosion::EFFECT_SHIFT_POSITION(0.f, 2.5f, 0.f);

/*==================
�R���X�g���N�^
==================*/
BulletStateExplosion::BulletStateExplosion()
	:
	BulletStateBase(),
	mBulletVelocity(FIRST_VELOCITY),
	mBulletHeight(FIRST_HEIGHT)
{
}

/*======================================
�ړ�����
�Ԃ�l�F������͖��g�p(��State��Ŏg�p)
=======================================*/
bool BulletStateExplosion::Move()
{
	//���������t���O�������Ă�����
	if (BulletStateBase::GetBullet()->GetExplosionFlag())
	{
		//�G�t�F�N�g�𔭐�������
		//�G�t�F�N�g�}�l�[�W���[�̎擾
		auto pEM = EffectManager::GetInstance();

		auto effect = pEM->GetEffect(eEffectType::BOMB);
		effect->SetPosition(BulletStateBase::GetBullet()->GetBulletModel()->GetPosition() + EFFECT_SHIFT_POSITION);
		effect->SetScale(effect->GetScale());
		effect->SetSpriteFlag(true);
		effect->SetLoopFlag(false);
		//���g�p��ԂƂ���
		this->Reset();
		return true;
	}


	mBulletVelocity -= GRAVITY;
	mBulletHeight += mBulletVelocity;

	//����p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 movevel =
		DirectX::SimpleMath::Vector3(0.f, 0.f, -BulletStateBase::GetBullet()->GetBulletVelocity());

	//���W�֔��f
	BulletStateBase::GetBullet()->GetBulletModel()->Move(movevel);

	DirectX::SimpleMath::Vector3 pos = BulletStateBase::GetBullet()->GetBulletModel()->GetPosition();
	pos.y = mBulletHeight;

	BulletStateBase::GetBullet()->GetBulletModel()->SetPosition(pos);
	

	//�n�ʂ�艺�ɍs������
	if (pos.y <= 0.f)
	{
		//�����t���O�����Ă�
		BulletStateBase::GetBullet()->SetExplosionFlag(true);
		BulletStateBase::GetBullet()->SetDoubleCollider();
	}

	return false;	
}

/*======================================
�`�揈��
=======================================*/
void BulletStateExplosion::Draw()
{

}

/*======================================
���Z�b�g����
=======================================*/
void BulletStateExplosion::Reset()
{
	mBulletVelocity = FIRST_VELOCITY;
	mBulletHeight = FIRST_HEIGHT;
}