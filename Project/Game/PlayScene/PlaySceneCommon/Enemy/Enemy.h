/*
�G�N���X
*/

#pragma once


//�񋓌^�̎g�p
#include"StateEnemy.h"
#include"AngleEnemy.h"

//����
#include"../ObjectModel/BoxModel.h"
#include"EStateRotation.h"
#include"EStateWalk.h"
#include"EStateKnockBack.h"
#include"EStateAppearance.h"
#include"EStateAttack.h"
#include"EStateBuried.h"
#include"EStateBlinking.h"
#include"../Shadow.h"
#include"../../PlaySceneDefence/FloatNumber3D.h"

//�O���錾
class EnemyStateBase;	//��ԕ������N���X

struct AABB;			//�֐��̕Ԃ�l�Ŏg�p

class CameraBase;			//����
class Enemy
{
private:
	//�萔
		//�ړ����x
	static const float ENEMY_MOVE_SPEED;
	//�g�嗦
	static const DirectX::SimpleMath::Vector3 ENEMY_SCALE;
	//���f���ɍ��킹�ē����蔻��p�̊g�嗦���߂�
	static const float ENEMY_COLLIDER_EXTEND_Y;
	static const float ENEMY_COLLIDER_EXTEND_Z;
	//���f���������~�X�̏C��
	static const float ENMEY_MODELMISS_FIX_ROT;

	//���f���`��͈͎w��
	static const float ENEMY_MDEL_DROW_AREA;

	//�u���b�N�ԍ��ۑ���
	static const int ENEMY_SAVE_BLOCKNUMBER_MAX_NUM = 3;
		//�u���b�N�ԍ���O����
	static const int ENEMY_SAVE_BLOCKNUMBER_EXCE_NUM;


	//�G���f���������I�ɉ��Ɍ�����(�������]����ۂɎg�p)
	static const float ENEMY_MODEL_FORCED_BESIDE;

	//�G��HP
	static const int ENEMY_HP;

	//�G�̍ő唽�]��
	static const int ENEMY_REVERSE_MAX_NUM;

	//�G�t�F�N�g�\�����W
	static const DirectX::SimpleMath::Vector3 EFFECT_SHIFT_POSITION;

	//�_���[�W�l�̕`����W
	static const DirectX::SimpleMath::Vector3 FLOATNUMBER_DISTANCE_POSITION;


	//�ϐ�

	//���f���`��N���X
	std::unique_ptr<BoxModel> mpEnemyModel;

	//�g�p�t���O
	bool mEnemyUseFlag;

	//�����n�߂�t�F�[�Y�ԍ�
	int mMovePhaseNumber;

	//�s��State�Ǘ��p�ϐ�
	EnemyStateBase* mpEnemyMoveState;
	eStateEnemy mStateEnemy;

	//State����
	std::unique_ptr<EStateRotation> mpRotation;
	std::unique_ptr<EStateWalk> mpWalk;
	std::unique_ptr<EStateKnockBack> mpKnockBack;
	std::unique_ptr<EStateAppearance> mpAppearance;
	std::unique_ptr<EStateAttack> mpAttack;
	std::unique_ptr<EStateBuried> mpBuried;
	std::unique_ptr<EStateBlinking> mpBlinking;

	//���݂̃��f���̌�����\��
	eAngleEnemy mEnemyModelAngle;

	//���݂�HP
	int mEnemyDamage;

	//�G�t�F�N�g�ғ��t���O
	bool mEffectFlag;

	//�e
	std::unique_ptr<Shadow> mpEnemyShadow;

	//�����G�t�F�N�g
	std::unique_ptr<FloatNumber3D> mpFloatNumber;

	//���]��
	int mReverseNum;

	//�G�t�F�N�g�̃A�h���X�ۑ��p�ϐ�
	bool* mEffectAddressFlag;

	//�n��I�u�W�F�N�g�Ƃ̏Փ˃t���O
	bool mEnemyGroundObjectHitFlag;

	//�u�[�������Ƃ̐ڐG�t���O
	bool mBoomerangHitFlag;

	//�ڐG�����e�̔ԍ���ۑ�����ϐ�
	int mSaveBulletNumber;

	//���݂̕��s��Ԃ�\��
	eEnemyWalkState mWalkState;

	//�ڐG�����ĎR�q�̔ԍ���ۑ�����
	int mSaveScarecrowNumber;

	//�v���C���[�ǂ������t���O
	bool mPlayerChaseFlag;


public:
	//�֐�
	//�R���X�g���N�^
	Enemy();
	//�f�X�g���N�^
	~Enemy();
	//������
	void Initialize(DirectX::SimpleMath::Vector3 const& pos,CameraBase* camera);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�I������
	void Finalize();

	//���g���폜����B
	void SelfDestroy();

	
	//�A�N�Z�T�֘A
	//��ԕ���
	void ChangeStateWalk() 
			{mpEnemyMoveState = (EnemyStateBase*)mpWalk.get(); mStateEnemy = eStateEnemy::WALK;}
	void ChangeStateRotation()
			{ mpEnemyMoveState = (EnemyStateBase*)mpRotation.get();  mStateEnemy = eStateEnemy::ROTATION;}
	void ChangeStateKnockBack()
			{ mpEnemyMoveState = (EnemyStateBase*)mpKnockBack.get();  mStateEnemy = eStateEnemy::KNOCK_BACK;}
	void ChangeStateAppearance()
			{ mpEnemyMoveState = (EnemyStateBase*)mpAppearance.get();  mStateEnemy = eStateEnemy::APPEARANCE;}
	void ChangeStateAttack()
			{ mpEnemyMoveState = (EnemyStateBase*)mpAttack.get();  mStateEnemy = eStateEnemy::ATTACK;}
	void ChangeStateBuried()
			{ mpEnemyMoveState = (EnemyStateBase*)mpBuried.get();  mStateEnemy = eStateEnemy::BURIED;}
	void ChangeStateBlinking()
			{ mpEnemyMoveState = (EnemyStateBase*)mpBlinking.get();  mStateEnemy = eStateEnemy::BLINKING;}
	EStateRotation* GetStateRotation() const { return mpRotation.get(); }
	EStateWalk* GetStateWalk()const { return mpWalk.get(); }
	EStateKnockBack* GetStateKnockBack() const { return mpKnockBack.get(); }
	EStateAppearance* GetStateAppearance() const { return mpAppearance.get(); }
	EStateAttack* GetStateAttack()const { return mpAttack.get(); }
	EStateBuried* GetStateBuried() const { return mpBuried.get(); }


	AABB* GetWalkCollider()const;
	AABB* GetRotationCollider()const;

	//���݂̏�Ԃ̃A�N�Z�T
	eStateEnemy GetStateEnemy() const { return mStateEnemy; }

	//�����蔻���Ԃ�
	BoxModel* GetBoxModel()const {return mpEnemyModel.get();}

	//�g�p�t���O��Ԃ��֐�
	bool GetEnemyUseFlag() const { return mEnemyUseFlag; }

	//�n������t�F�[�Y�ԍ��̃A�N�Z�T
	void SetMovePhaseNumber(int const& num){ mMovePhaseNumber = num; }
	int GetMovePhaseNumber()const {return mMovePhaseNumber;}

	//���]���̃A�N�Z�T
	void SetReverseNumUp()
	{
		mReverseNum++;
	}
	int GetRecerseNum()const { return mReverseNum; }

	//���f����ݒ肷��
	void SetEnemyModel(float const& posy);


	//���f���̌����̃A�N�Z�T
	eAngleEnemy GetAngleEnemy()const { return mEnemyModelAngle; }
	void SetAngleEnemy(eAngleEnemy const& angle) { mEnemyModelAngle = angle; }

	//�ړ�����
	void Move();

	//���݂�HP�̃A�N�Z�T
	int GetEnemyDamage()const { return mEnemyDamage; }
	//�_���[�W��^���鏈��
	bool Damage(int const& damagenum);


	//�G�t�F�N�g�ғ��t���O�̃A�N�Z�T
	bool GetEffectFlag() const { return mEffectFlag; }
	void SetEffectFlag(bool const& flag) { mEffectFlag=flag; }

	//�G�t�F�N�g�̃A�h���X��Ⴄ
	void SetSpriteFlagAddress(bool* flagAddress) { mEffectAddressFlag = flagAddress; }

	//�e�̃A�N�Z�T
	Shadow* GetShadow()const { return mpEnemyShadow.get(); }

	//�n��I�u�W�F�N�g�Ƃ̐ڐG�t���O�̃A�N�Z�T
	void SetEnemyGroundObjectHitFlag(bool const& flag) { mEnemyGroundObjectHitFlag = flag; }
	bool GetEnemyGroundObjectHitFlag() const { return mEnemyGroundObjectHitFlag; }


	//�u�[�������ڐG�t���O�̃A�N�Z�T
	void SetBoomerangHitFlag(bool const& flag) { mBoomerangHitFlag = flag; }
	bool GetBoomerangHitFlag() const { return mBoomerangHitFlag; }


	//�ڐG�����e�̔ԍ���ۑ�����ϐ��̃A�N�Z�T
	int GetSaveBulletNumber()const { return mSaveBulletNumber; }
	void SetSaveBulletNumber(int const& num) { mSaveBulletNumber = num; }

	//�G�t�F�N�g���쐬����
	void CreateNumberEffect(int damageNum);
	//�G�t�F�N�g�����Z�b�g����
	void ResetNumberEffect();


	void SetEnemyWalkState(eEnemyWalkState state) { mWalkState = state; }
	eEnemyWalkState GetEnemyWalkState() { return mWalkState; }

	//�ڐG�����ĎR�q�̔ԍ���ۑ�����
	int GetSaveScarecrowNumber()const { return mSaveScarecrowNumber; }
	void SetSaveScarecrowNumber(int const& num) { mSaveScarecrowNumber = num; }
	void ResetSaveScarecrowNumber() { mSaveScarecrowNumber = Utility::EXCEPTION_NUM; }

	//�v���C���[�ǂ������t���O
	bool GetPlayerChaseFlag()const { return mPlayerChaseFlag; }
	void SetPlayerChaseFlag(bool const& flag) { mPlayerChaseFlag = flag; }
};
