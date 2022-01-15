/*
�G�N���X
*/

#include<pch.h>
#include "Enemy.h"

//�O���錾
#include"../../../Common/ObjectTexture.h"




//���\�[�X�̎擾
#include"../../Effect/EffectManager.h"
#include"../../Effect/Effect.h"






//�萔

//���f���̊g�嗦
//�����ڗp
const DirectX::SimpleMath::Vector3 Enemy::ENEMY_SCALE(0.5f, 0.5f, 0.5f);

	//�ړ����x
const float Enemy::ENEMY_MOVE_SPEED = 0.01f;


//���f���ɍ��킹�ē����蔻��p�̊g�嗦���߂�
//�v���C���[��Z������Y�����ɒ����̂œ����蔻���Z������Y�����ɐL�΂�
const float Enemy::ENEMY_COLLIDER_EXTEND_Y = 3.f;
const float Enemy::ENEMY_COLLIDER_EXTEND_Z = 4.f;


//���f���������~�X�̏C��
const float Enemy::ENMEY_MODELMISS_FIX_ROT = 180.f;

//���f���`��͈͎w��
const float Enemy::ENEMY_MDEL_DROW_AREA = -70.f;



//�u���b�N�ԍ���O����
const int Enemy::ENEMY_SAVE_BLOCKNUMBER_EXCE_NUM = -1;

//�G���f���������I�ɉ��Ɍ�����(�������]����ۂɎg�p)
const float Enemy::ENEMY_MODEL_FORCED_BESIDE = 270.f;


//�G��HP
const int Enemy::ENEMY_HP = 20;

//�G�̍ő唽�]��
const int Enemy::ENEMY_REVERSE_MAX_NUM = 2;

//�G�t�F�N�g�\�����W
const DirectX::SimpleMath::Vector3 Enemy::EFFECT_SHIFT_POSITION(0.f, 1.f, 1.f);


//�_���[�W�l�̕`����W
const DirectX::SimpleMath::Vector3 Enemy::FLOATNUMBER_DISTANCE_POSITION(0.f, 4.5f, 0.f);

/*===================================
�R���X�g���N�^
===================================*/
Enemy::Enemy()
	: 
	mpEnemyModel(),
	mEnemyUseFlag(false),
	mMovePhaseNumber(),
	mpEnemyMoveState(nullptr),
	mStateEnemy(eStateEnemy::WALK),
	mpRotation(nullptr),
	mpWalk(nullptr),
	mpKnockBack(nullptr),
	mpAppearance(nullptr),
	mpAttack(nullptr),
	mpBuried(nullptr),
	mEnemyModelAngle(eAngleEnemy::STRAIGHT),
	mEnemyDamage(0),
	mEffectFlag(false),
	mpEnemyShadow(nullptr),
	mReverseNum(0),
	mEffectAddressFlag(nullptr),
	mEnemyGroundObjectHitFlag(false),
	mBoomerangHitFlag(false),
	mSaveBulletNumber(Utility::EXCEPTION_NUM),
	mpFloatNumber(nullptr),
	mWalkState(eEnemyWalkState::GENERALLY),
	mSaveScarecrowNumber(Utility::EXCEPTION_NUM),
	mPlayerChaseFlag(false)
{
	mpEnemyModel = std::make_unique<BoxModel>();

	mpRotation = std::make_unique<EStateRotation>();
	mpWalk = std::make_unique<EStateWalk>();
	mpKnockBack = std::make_unique<EStateKnockBack>();
	mpAppearance = std::make_unique<EStateAppearance>();
	mpAttack = std::make_unique<EStateAttack>();
	mpBuried = std::make_unique<EStateBuried>();
	mpBlinking = std::make_unique<EStateBlinking>();

	mpEnemyShadow = std::make_unique<Shadow>();
	mpFloatNumber = std::make_unique<FloatNumber3D>();
}

/*===================================
�f�X�g���N�^
===================================*/
Enemy::~Enemy()
{
}

/*=================================
������
�����F�������W,�J�����̃|�C���^
===================================*/
void Enemy::Initialize(DirectX::SimpleMath::Vector3 const& pos, CameraBase* camera)
{
	//���W�̓��f���ݒ莞�ۑ�

	//���f����ݒ肷��
	this->SetEnemyModel(pos.y);

	//���f����\������
	mpEnemyModel->SetDrawFlag(true);

	mpEnemyModel->SetPosition(pos);
	mpEnemyModel->SetScale(ENEMY_SCALE);
	mpEnemyModel->SetRotationY(ENMEY_MODELMISS_FIX_ROT);	//���f���������~�X�̏C��

	/*�����蔻�萶��*/
	//�g�嗦�̔����̒l�𐶐�
	DirectX::SimpleMath::Vector3 halfsize = mpEnemyModel->ReturnHalfSize(ENEMY_SCALE);
	//���f���̌`�ɍ��킹�ăT�C�Y����
	halfsize.y *= ENEMY_COLLIDER_EXTEND_Y;
	halfsize.z *= ENEMY_COLLIDER_EXTEND_Z;

	//�ݒ�
	mpEnemyModel->SetAABBCollider(pos - halfsize, pos + halfsize);

	//�g�p���ɂ���
	mEnemyUseFlag = true;


	//�e�̏���������
	mpEnemyShadow->WrapInitialize();
	//�e�̊g�嗦�����߂�
	mpEnemyShadow->SetScale(DirectX::SimpleMath::Vector2(ENEMY_SCALE.x, ENEMY_SCALE.z));	//XZ����

	//���ꂼ��̏�Ԃ̏�����
	mpRotation->Initialize(this);
	mpWalk->Initialize(this);
	mpKnockBack->Initialize(this);
	mpAppearance->Initialize(this);
	mpAttack->Initialize(this);
	mpBuried->Initialize(this);
	mpBlinking->Initialize(this);


	//�ŏ��̏�Ԃ͑ҋ@����
	this->ChangeStateBuried();

	mpFloatNumber->Initialize(camera);
}

/*===================================
�X�V
===================================*/
void Enemy::Update()
{
	//�g�p���̎��̂ݒʂ�
	if (mEnemyUseFlag) 
	{
		//State�ŊǗ����ꂽ�ړ��������s��
		mpEnemyMoveState->Update();

		/*�����蔻��̍X�V*/
		//�����ł͕ۑ����ĂȂ����߃��f������Ăяo���B
		DirectX::SimpleMath::Vector3 modelpos, modelscale;
		modelpos = mpEnemyModel->GetPosition();
		modelscale = mpEnemyModel->GetScale();
		//�g�嗦�̔����̒l�𐶐�
		DirectX::SimpleMath::Vector3 halfsize = mpEnemyModel->ReturnHalfSize(modelscale);
		//�ݒ�
		mpEnemyModel->SetAABBCollider(modelpos - halfsize, modelpos + halfsize);


		//�����A�ǂ�2��Ԃ�������(�ǂ���Ă��邱�ƂɋC�Â�����)
		if (mReverseNum == ENEMY_REVERSE_MAX_NUM&&!mEnemyGroundObjectHitFlag)
		{
			//����������
			mReverseNum = 0;

			//��]��������𐳖ʂɐݒ肷��
			this->GetStateRotation()->SetChangeAfterAngle(eChangeAfterAngle::STRAIGHT);
		
			//��Ԃ���]�ɐ؂�ւ���
			this->ChangeStateRotation();
		}
	}

	if (mEffectAddressFlag!=nullptr&&*mEffectAddressFlag==false)
	{
		mEffectFlag = false;
	}

	mpFloatNumber->Update();
}

/*===================================
�`��
===================================*/
void Enemy::Draw()
{
	if (!mEnemyUseFlag)
	{
		return;
	}

	//���f�����w��͈͂ɓ����Ă�����`�悷��
	if (mpEnemyModel->GetPosition().z >= ENEMY_MDEL_DROW_AREA)
	{
		//�e�̕`��
		mpEnemyShadow->Draw(mpEnemyModel->GetPosition());

		//���f���̕`��
		mpEnemyModel->Draw();

		//State��̕`��
		mpEnemyMoveState->Draw();
	}

	mpFloatNumber->Draw();
}

/*===================================
�I������
===================================*/
void Enemy::Finalize()
{
	mpEnemyModel.reset();
}

/*==================================
���g���폜(�|�C���^�Ȃǂ͏��ł��Ȃ�)
===================================*/
void Enemy::SelfDestroy()
{
	//�`�撆�ł����
	if (mpEnemyModel->GetDrawFlag())
	{
		mpEnemyModel->SetDrawFlag(false);

		//�����蔻��������l��
		mpEnemyModel->SetAABBCollider
		(
			DirectX::SimpleMath::Vector3::Zero,
			DirectX::SimpleMath::Vector3::Zero
		);

		//���g�p��Ԃɂ���
		mEnemyUseFlag = false;

	}
}

/*==================================
������Ԃ̍ۂ̓����蔻��̃A�N�Z�T
�Ԃ�l�F�����蔻��
===================================*/
AABB* Enemy::GetWalkCollider()const
{
	return mpWalk.get()->GetCollider();
}

/*===================================
��]��Ԃ̍ۂ̓����蔻��̃A�N�Z�T
�Ԃ�l�F�����蔻��
===================================*/
AABB* Enemy::GetRotationCollider()const
{
	return mpRotation.get()->GetCollider();;
}

/*===================================
���f����ݒ肷��:private
�����F�G�̍���
===================================*/
void Enemy::SetEnemyModel(float const& posy)
{
	posy;
	//���\�[�X�}�l�[�W���̏���
	//�����ɍ��킹�����f����ݒ肷��
	auto pRM = ResourceManager::GetInstance();
	
	//�G��ɍ��킹�����f����ݒ肷��
	auto model = pRM->GetCmoModel("Enemy2");

	//�ݒ肷��
	mpEnemyModel->SetModel(model);
}


/*===================================
�ړ�����
===================================*/
void Enemy::Move()
{
	DirectX::SimpleMath::Vector3 vel;
	vel.z = ENEMY_MOVE_SPEED;

	mpEnemyModel->Move(vel);
}

/*=================================
�_���[�W��^���鏈��
�����F�_���[�W�l
�Ԃ�l�F���j�������ǂ���(true�F���j)
===================================*/
bool Enemy::Damage(int const& damagenum)
{
	//�_���[�W��^����
	mEnemyDamage += damagenum;

	if (mEnemyDamage >= ENEMY_HP)
	{
		//���g�p��Ԃɂ���
		this->SelfDestroy();
		//�G�t�F�N�g�}�l�[�W���[�̎擾
		auto pEM = EffectManager::GetInstance();

		auto effect = pEM->GetEffect(eEffectType::DISAPPEAR);
		effect->SetPosition(mpEnemyModel->GetPosition() + EFFECT_SHIFT_POSITION);
		effect->SetSpriteFlag(true);
		effect->SetLoopFlag(false);
		return true;
	}
	return false;
}

/*=================================
�G�t�F�N�g���쐬����
�����G�_���[�W�l
===================================*/
void Enemy::CreateNumberEffect(int damageNum)
{
	mpFloatNumber->Create
	(
		damageNum,
		mpEnemyModel->GetPosition()+
		FLOATNUMBER_DISTANCE_POSITION
	);
}

/*=================================
�G�t�F�N�g�����Z�b�g����
===================================*/
void Enemy::ResetNumberEffect()
{
	mpFloatNumber->Reset();
}
