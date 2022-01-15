/*
�v���C���[�N���X
*/

#pragma once

//�񋓌^�̎g�p
#include"PlayerActionState.h"


//���ۂɏ���
#include"../ObjectModel/BoxModel.h"
#include"../Shadow.h"

//�ړ����State
enum class ePlayerState
{
	STAND,	//�������(�W��)
	WALK,	//�ړ����
	DAMAGE,	//�_���[�W���

};


//�O���錾
class PStateStand;				//��ԕ���
class PStateWalk;				//��ԕ���
class PStateDamage;				//��ԕ���
class PlayerStateBase;			//��ԕ������N���X

class ActionStateDefenseHouse;	//�s����ԕ���
class ActionStateAttackEnemy;	//�s����ԕ���
class ActionStateBase;			//�s����Ԋ��N���X



class BlockManager;				//�|�C���^�ۑ��p
class PreparingBlock;			//�|�C���^�ۑ��p
class Administrator;			//�|�C���^�ۑ��p
class ScarecrowManager;			//�|�C���^�ۑ��p
class PreparingScarecrow;		//�|�C���^�ۑ��p
class UI;						//�|�C���^�ۑ��p

class Player
{
private:
	//�萔
	//�������W
	static const DirectX::SimpleMath::Vector3 PLYAER_INIT_POSITION;

	//���f���̊g�嗦
		//�����ڗp
	static const DirectX::SimpleMath::Vector3 PLAYER_MODEL_SCALE;

	//�v���C���[�͏c���Ȃ̂œ����蔻����c�ɐL�΂�
	static const float PLAYER_COLLIDER_EXTEND_Y;
	//���ۂ̃v���C���[��Z�l�͂ƂĂ��������̂ŏ���������
	static const float PLAYER_COLLIDER_EXTEND_Z;

	//�V�[���h�p�j�b�V���p�Q�[�W�K�v��
	static const int BLOCKBREAK_USE_GAUGENUM;
	//�V�[���h�p�j�b�V���p�g�嗦
	static const DirectX::SimpleMath::Vector3 BLOCKBREAK_SCALE;


	//�ϐ�
	//���f���`��N���X
	std::unique_ptr<BoxModel> mpPlayerModel;

	//�u���b�N����̏���������N���X
	PreparingBlock* mpPreparingBlock;

	//�����ς݃|�C���^�ۑ��ϐ�
	BlockManager* mpBlockManager;
	Administrator* mpAdministrator;
	UI* mpUI;
	PreparingScarecrow* mpPreparingScarecrow;

	//��ԕ����X�e�[�g�p�^�[��
	std::unique_ptr<PStateStand> mpStand;
	std::unique_ptr<PStateWalk> mpWalk;
	std::unique_ptr<PStateDamage> mpDamage;
	// ���݂̏��
	PlayerStateBase* mpPlayerState;
	ePlayerState mState;


	//�s����ԕ����X�e�[�g�p�^�[��
	std::unique_ptr<ActionStateDefenseHouse> mpDefenseHouse;
	std::unique_ptr<ActionStateAttackEnemy> mpAttackEnemy;
	//���݂̏��
	ActionStateBase* mpPlayerActionState;
	ePlayerActionState mActionState;

	//1�t���[���O�̃v���C���[�̍��W
	DirectX::SimpleMath::Vector3 mOneFrameBeforePosition;

	//�e
	std::unique_ptr<Shadow> mpPlayerShadow;

	//�v���C���[�U���p���[���h���W�ۑ��p�ϐ�
	DirectX::SimpleMath::Matrix mPlayerAttackWorldMatrix;

public:
	//�֐�
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();
	//������
	void Initialize(BlockManager* pBlockManager,
		Administrator* pAdministrator,
		PreparingBlock* pPreparingBlock,
		UI* pUI);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�I������
	void Finalize();


	//�A�N�Z�T�֘A
	//��ԕ���
	void ChangeStateStand() { mpPlayerState = (PlayerStateBase*)mpStand.get(); }
	void ChangeStateWalk()	{ mpPlayerState = (PlayerStateBase*)mpWalk.get(); }
	void ChangeStateDamage(){ mpPlayerState = (PlayerStateBase*)mpDamage.get(); }
	
	void SetState(ePlayerState const& state) { mState = state; }
	ePlayerState GetPlayerState()const { return mState; }

	PStateWalk* GetStateWalk()const {return mpWalk.get();}


	void ChangePlayerActionStateDefenseHouse()
	{ 
		mpPlayerActionState = (ActionStateBase*)mpDefenseHouse.get();
		mActionState = ePlayerActionState::BLOCK_CREATE;
	}
	void ChangePlayerActionStateAttackEnemy() 
	{
		mpPlayerActionState = (ActionStateBase*)mpAttackEnemy.get();
		mActionState = ePlayerActionState::ATTACK_ENEMY; 
	}
	ActionStateBase* GetActionStateBase() const { return mpPlayerActionState; }
	
	ActionStateAttackEnemy* GetAttackEnemyPointer() const { return mpAttackEnemy.get(); }

	void SetActionState(ePlayerActionState const& state) { mActionState = state; }
	ePlayerActionState GetActionState()const { return mActionState; }

	//�����蔻���Ԃ�
	BoxModel* GetPlayerModel()const { return mpPlayerModel.get(); }

	//�s��State�̃A�N�Z�T
	ActionStateDefenseHouse* GetDefenseHouse() const { return mpDefenseHouse.get(); }
	ActionStateAttackEnemy* GetAttackEnemy() const { return mpAttackEnemy.get(); }


	//1�t���[���O�̃v���C���[�̍��W�̃A�N�Z�T
	DirectX::SimpleMath::Vector3 GetOneFrameBeforePosition()const { return mOneFrameBeforePosition; }
	void SetOneFrameBeforePosition(DirectX::SimpleMath::Vector3 const&pos) { mOneFrameBeforePosition = pos; }

	//�����蔻��̍����̒萔�̃A�N�Z�T
	float GetPlayerColliderExtendY()const { return PLAYER_COLLIDER_EXTEND_Y; }


	//�����蔻��X�V����
	void UpdateCollider();

	UI* GetUIPointer()const { return mpUI; }

	//�v���C���[�̍U���p���[���h���W�̃A�N�Z�T
	DirectX::SimpleMath::Matrix GetPlayerAttackWorldMatrix() const { return mPlayerAttackWorldMatrix; }

private:

	//�s��State�ύX
	void ChangeAction();

	//�U���p���[���h���W�̌v�Z
	void CalculationAttackMat();

};