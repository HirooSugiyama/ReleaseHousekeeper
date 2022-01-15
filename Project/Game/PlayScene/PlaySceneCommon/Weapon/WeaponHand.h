/*
��U���N���X
�쐬���F2021/09/14
*/
#pragma once

//����
#include"../Player/Player.h"
#include"../ObjectModel/SphereModel.h"
#include"../Player/Animation/NormalAttackAnim.h"


//���݂̏�Ԃ��Ǘ�����
enum class eHandState
{
	STAND_BY,
	ATTACK,
	COOL_TIME,
};

class WeaponHand
{
private:


	//�v���C���[�̍��W����U������܂ł̋���
	static const DirectX::SimpleMath::Vector3 ATTACKSTATE_PLAYER_DISTANCE_POSITION;

	//�����蔻��̊g�嗦
	static const DirectX::SimpleMath::Vector3 ATTACKSTATE_COLLIRDEMODEL_SCALE;
	static const float ATTACKSTATE_COLLIRDE_SCALE;

	//�U���ő�t���[����
	static const int ATTACKSTATE_MAX_ATTACK_FRAME;
	//�����ő�t���[����
	static const int ATTACKSTATE_MAX_RECOIL_FRAME;

	//�G�ւ�1��̍U���̃_���[�W�l
	static const int ATTACKSTATE_HAND_DAMAGE;

	//�A�j���[�V�����̍��W�������グ��l
	static const float ATTACK_STATE_SHIFT_ANIMATION;


	//�U��������܂񂾃I�u�W�F�N�g
	std::unique_ptr<SphereModel> mpWeapon;

	//�A�j���[�V�������f���Ǘ��N���X
	std::unique_ptr<NormalAttackAnim> mpAnim;

	//�ۑ��p�ϐ�
	Player* mpPlayer;

	//�\�����[���h���W
	DirectX::SimpleMath::Matrix mWorld;

	//�U������t���O
	eHandState mAttackFlag;
	//�U���t���[���v��
	int mAttackFrameCountNum;

	//�A�j���[�V�����t���O
	bool mAnimationFlag;

	//�U�����W
	DirectX::SimpleMath::Vector3 mColliderPosition;

public:

	//�R���X�g���N�^
	WeaponHand();
	//�f�X�g���N�^
	~WeaponHand();
	//����������
	void Initialize();
	//�X�V����
	void Update();

	//�`�揈��
	void Draw();

	//�|�C���^�̕ۑ�
	void SetPlayerPointer(Player* pPlayer) { mpPlayer=pPlayer; }

	//�����蔻���Ԃ�����
	SphereModel* GetCollider();

	//���݂̏�Ԃ��Ǘ�����t���O�̃A�N�Z�T
	void SetAttackFlag(eHandState const& flag) { mAttackFlag = flag; }
	eHandState GetAttackFlag() const { return mAttackFlag; }

	//�_���[�W�l��Ԃ��֐�
	int GetDamage() const { return ATTACKSTATE_HAND_DAMAGE; }

	//�����蔻��̍쐬
	DirectX::SimpleMath::Vector3 GetColliderPosition()const { return mColliderPosition; }

	//�����蔻���ݒ�
	void SetCollider(bool const& flag = false);

private:
	//�U������ғ�����
	void AttackFrameCount();

	//���Z�b�g����
	void Reset();
	
};
