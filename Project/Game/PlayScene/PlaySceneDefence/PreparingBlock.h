/*
�v���C���[�̃u���b�N��������̏���
�쐬���F2021/06/18
*/
#pragma once
#include <SimpleMath.h>

//����
#include"../PlaySceneCommon/ObjectModel/BoxModel.h"

//�֐����Ŏg�p
class GridLineManager;

class PreparingBlock
{
private:

	//�萔
	//�u���b�N�����K�v���ސ�
	static const int BLOCK_CREATE_MONEY_NUM;

	//�v���C���[���班�����炷���W
	static const DirectX::SimpleMath::Vector3 BLOCK_SHIFT_PLAYERPOSITION;

	//�~���̔��a
	static const float SAMPLEBLOCK_COLLIDER_RADIUS;

	//�u���b�N�̊g�嗦
	static const DirectX::SimpleMath::Vector3 SAMPLEBLOCK_SCALE;
	//�u���b�N�̏������W
	static const DirectX::SimpleMath::Vector3 SAMPLEBLOCK_INIT_POSITION;



	/*�ړ�����*/
		//���{�u���b�N�̈ړ���(X)
	static const float SAMPLEBLOCK_MOVE_VELOCITY_X;
	//���{�u���b�N�̈ړ���(Y)
	static const float SAMPLEBLOCK_MOVE_VELOCITY_Y;
	//���{�u���b�N�̈ړ���(Z)
	static const float SAMPLEBLOCK_MOVE_VELOCITY_Z;

	//�ϐ�
		//�z�u���{�u���b�N�\���p���f��
	std::unique_ptr<BoxModel> mpSampleModel;
	//����p���C���Ƃ̏Փ˔���p�����蔻��
	std::unique_ptr<Circle> mpCircleCollider;

	//�ړ��t���O
	bool mMoveFlag;

public:
	//�֐�
	//�R���X�g���N�^
	PreparingBlock();
	//�f�X�g���N�^
	~PreparingBlock();
	//������
	void Initialize();
	//�X�V
	void Update(DirectX::SimpleMath::Vector3 const& movevel, GridLineManager* pGridLineMnager);
	//�`��
	void Draw();

	//�ړ�����
	void Move(DirectX::SimpleMath::Vector3 const& movevel, GridLineManager* pGridLineMnager);

	//���f���ւ̃A�N�Z�T
	BoxModel* GetBoxModel() const { return mpSampleModel.get(); }

	//�Փ˔���̃A�N�Z�T
	Circle* GetCircleCollider() const { return mpCircleCollider.get(); }

	//�ړ��t���O�̃A�N�Z�T
	void SetMoveFlag(bool const& flag) { mMoveFlag = flag; }

	//����p���C���ɏd�Ȃ��Ă��Ȃ��Ƃ��ɏ�������u���b�N���ޕύX�֐�
	void ChangeNotUseBlock();

private:
	//���ނ�����Ă��Ȃ��Ƃ���������u���b�N�̎��ޕύX�֐�
	void ChangeNotEnoughMat();

	//�����蔻�萶������
	void CircleColliderUpdate();

};