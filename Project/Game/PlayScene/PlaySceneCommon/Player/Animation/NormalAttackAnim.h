/*
�v���C���[�̒ʏ�U���A�j���[�V�������f�����Ǘ�����N���X
�쐬���F2021/09/05
*/
#pragma once

//����
#include"../../ObjectModel/ObjectModel.h"

class NormalAttackAnim
{

private:

	//Sin�l�g�嗦
	static const float SIN_SCLAE;
	//�A�j���[�V�����̑��x
	static const float ANIM_VELOCITY;
	//�A�j���[�V�����̉����x
	static const float ANIM_ACCEL;
	//�A�j���[�V�����ő�l
	static const float ANIM_MAX_NUM;

	//�A�j���[�V�������f��
	std::unique_ptr<ObjectModel> mpAnimModel;

	//sin�l�Ǘ��p�ϐ�
	float mSinNum;

	//���x
	float mVelocity;

	//�A�j���\�V������`�悷�郏�[���h���W
	DirectX::SimpleMath::Matrix mWorld;

public:


	//�R���X�g���N�^
	NormalAttackAnim();
	//�f�X�g���N�^
	~NormalAttackAnim();
	//������
	void Initialize();
	//���Z�b�g����
	void Reset();
	//�X�V
	bool Update(DirectX::SimpleMath::Matrix const& playerAttackmat);

	//�`��
	void Draw();
};