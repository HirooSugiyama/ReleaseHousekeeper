/*
�v���C���[�̏�ԕ����X�e�[�g�p�^�[���F�ړ����
�쐬���F2021/06/15
*/
#pragma once
#include"PlayerStateBase.h"

//����
#include"../ObjectModel/ObjectSpriteModel.h"

class PStateWalk:public PlayerStateBase
{
private:

	//�萔 	
	//�ǂ͈̔�
	static const float MAX_POSITION_X;
	static const float MAX_POSITION_Z;
	static const float MIN_POSITION_Z;
	//�X�v���C�g�̐�
	static const int WALKPLAYER_SPRITE_NUM;
	//�X�v���C�g�̃T�C�N��
	static const int WALKPLAYER_SPRITE_CYCLE;


	//�v���C���[�̈ړ���(X)
	static const float PLAYER_MOVE_VELOCITY_X;
	//�v���C���[�̈ړ���(Y)
	static const float PLAYER_MOVE_VELOCITY_Y;
	//�v���C���[�̈ړ���(Z)
	static const float PLAYER_MOVE_VELOCITY_Z;

	//�ړ��ʂ̑�����
	static const float PLAYER_MOVE_INCREASE_VELOCITY;


	//�v���C���[�̌�������

	//��
	static const int PLAYER_CHARACTER_ANGLE_L;
	//�E		
	static const int PLAYER_CHARACTER_ANGLE_R;
	//��	
	static const int PLAYER_CHARACTER_ANGLE_U;
	//��		
	static const int PLAYER_CHARACTER_ANGLE_D;
	//����
	static const int PLAYER_CHARACTER_ANGLE_LU;
	//�E��	   
	static const int PLAYER_CHARACTER_ANGLE_RU;
	//����	   
	static const int PLAYER_CHARACTER_ANGLE_LD;
	//�E��	  
	static const int PLAYER_CHARACTER_ANGLE_RD;

	//�ϐ�
	//Player�I�u�W�F�N�g�֕ۑ��p�̃|�C���^
	Player* mpPlayer;

	//�X�v���C�g���f��
	std::unique_ptr<ObjectSpriteModel> mpWalkSpriteModel;

	//���ۂ̃v���C���[�̑��x
	float mActualPlayerVelocityX;
	float mActualPlayerVelocityY;
	float mActualPlayerVelocityZ;

	//�ړ���̃v���C���[�̓����蔻��
	std::unique_ptr<AABB> mpDestinationPlayerCollider;

	//�n��I�u�W�F�N�g�ɓ������Ă��Ȃ������肷��t���O
	bool mGroundObjectHitFlag;
	//�u���b�N�ɓ������Ă��Ȃ������肷��t���O
	bool mBlockHitFlag;

public:
	//�֐�
	//�R���X�g���N�^
	PStateWalk();
	//����������
	void Initialize(Player* pPlayer)override;
	//State�J�n���̏���������
	void Reset()override {};
	//�X�V����
	void Update()override;
	//�`�揈��
	void Draw()override;

	//�ړ��x�N�g�����Z�o
	DirectX::SimpleMath::Vector3 CalculationMoveVelocity();


	//�ړ���̃v���C���[�̓����蔻���Ԃ�(�ړ��͂��Ȃ�)
	AABB* GetDestinationPlayerCollider();

	//�n��I�u�W�F�N�g�ɓ������Ă��Ȃ������肷��t���O�̃A�N�Z�T	
	void SetGroundObjectHitFlag(bool flag) { mGroundObjectHitFlag = flag; }
	//�u���b�N�ɓ������Ă��Ȃ������肷��t���O�̃A�N�Z�T
	void SetBlockHitFlag(bool flag) { mBlockHitFlag = flag; }

private:
	//�S�ẴI�u�W�F�N�g�ɓ������Ă��Ȃ��ꍇ�̂ݏ�����ʂ��֐�
	void AllObjectHit();

	//�ړ�����
	void Move();

	//���f����ݒ肷��
	void SetSpriteModel();

	//���W���擾���X�v���C�g���f���ɑ������
	void SetSpriteModelPosition();

	//�X�v���C�g�̃^�C�~���O�Ń��f���������ւ��鏈��
	void ReplacementSpriteModel();
	
	//�ړ��ʂ������x�I�ɑ���������
	void ConstantAcceleration();


	//�g�p��������x�����ׂď�����
	void AllActualPlayerVelocityInit();
};