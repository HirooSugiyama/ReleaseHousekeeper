/*
�u�[�������̈ړ�����
�쐬���F2021/10/16
*/

#pragma once

//�񋓌^�̎g�p
#include"../Weapon/BoomerangState.h"

//���N���X
#include"BulletStateBase.h"
//����
#include"../Administrator/Timer.h"

//�O���錾
class Player;	//�|�C���^�擾

class BulletStateBoomerang :public BulletStateBase
{
private:

	//���ł�������
	static const float BOOMERANG_FLY_DISTANCE;

	//��؎���
	static const int BOOMERANG_STAGNATION;

	//���W�ŏ��l
	static const float BULLET_MIN_POSITION_Z;

	//��]���x
	static const float BULLET_ROT_VELOCITY;

	//���x���ފ���
	static const float BULLET_VELOCITY_DECLINE;

	//�Œᑬ�x
	static const float BULLET_MIN_VELOCITY;

	//�u�[�������̔򋗗��ǉ��l
	static const float BULLET_FLY_DIS_UP_NUM;

	//���ԉ�
	eBoomerangState mState;

	//���ł�������
	float mFlyDistance;

	//�e�̔�ԕ���
	DirectX::SimpleMath::Vector3 mBoomerangAngle;

	//�e�̑��x
	float mBoomerangVelocity;

	//�|�C���^�ۑ��p�ϐ�
	Player* mpPlayer;
	std::unique_ptr<Timer> mpTimer;

	//��O�t���O
	bool mOutOfRangeFlag;


	float mFlyDistanceNum;

public:

	//�R���X�g���N�^
	BulletStateBoomerang();

	//�f�X�g���N�^
	~BulletStateBoomerang()override = default;

	//�ړ�����
	bool Move()override;

	//�u�[�������̏�Ԃ̃A�N�Z�T
	void ChangeBoomerangState(eBoomerangState const& state) { mState = state; }
	eBoomerangState GetBoomerangState()const { return mState; }

	//�v���C���[�̍��W�̃|�C���^��ۑ�����
	void SavePlayerPointer(Player* pPlayer) {mpPlayer = pPlayer;}

	//���Z�b�g����
	void Reset();

	//��O�t���O�̃A�N�Z�T
	bool GetOutOfRangeFlag() const { return mOutOfRangeFlag; }

	//�򋗗��ǉ�
	void DistanceAddValue();

private:
	//�e�̉�]����
	void RotBullet();

	//���x���ޏ���
	void SlowDown();

};