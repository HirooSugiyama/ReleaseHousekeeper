/*
�X�v���C�g���f���`��N���X
�쐬���F2021/04/18
*/
#pragma once

#include"IModel.h"

namespace DirectX
{
	class SpriteBatch;
}

class ObjectSpriteModel:public IModel
{
protected:
	//�萔
	// ���f���̃X�v���C�g�ԍ����ő�l�𒴂������������������邽�߂̌W��
	static const int SPRITE_REVERSE_NUM;	//�ڂ�����CPP�ɂ�
	
	//�ϐ�

	// �R�����X�e�[�g
	DirectX::CommonStates* mpCommonState;
	// �X�v���C�g�o�b�`
	DirectX::SpriteBatch* mpSpriteBatch;
	// �X�v���C�g�t�H���g
	DirectX::SpriteFont* mpSpriteFont;

	//���f���֌W
	DirectX::SimpleMath::Matrix mWorld;

	DirectX::SimpleMath::Matrix mView;
	DirectX::SimpleMath::Matrix mProj;

	std::unique_ptr<DirectX::IEffectFactory> mFxFactory;
	std::vector<DirectX::Model*> mModel;

	//���W
	DirectX::SimpleMath::Matrix mPosition;
	DirectX::SimpleMath::Matrix mScale;
	DirectX::SimpleMath::Matrix mRot;

	DirectX::SimpleMath::Vector3 mPosition3;
	DirectX::SimpleMath::Vector3 mScale3;

	//�\���t���O:true	�\��	false:��\��
	bool mDrawFlag;

	//�X�v���C�g�^�C�}�[
	int mSpriteTimer;
	//�^�C�}�[(�Œ�l)
	int mConstTimer;
	//�X�v���C�g�^�C�}�[�ғ��t���O
	bool mSpriteFlag;
	//���ݎg�p���Ă��郂�f���̔ԍ�
	int mUseModelNum;

	//�X�v���C�g�ő吔
	int mMaxSpriteNum;

	//�X�v���C�g���]�t���O
	bool mReverseFlag;

	//�֐�
public:
	//�R���X�g���N�^
	ObjectSpriteModel(int const& maxspritenum);

	//�f�X�g���N�^
	~ObjectSpriteModel();

	//���f���̎w��
	void SetSpriteModel(int const& spritenum,DirectX::Model* model);
	//���W�̎w��
	void SetPosition( DirectX::SimpleMath::Vector3 const& pos);
	//�g�嗦�̎w��
	void SetScale( DirectX::SimpleMath::Vector3 const& scale);
	//��]�̎w��
	void SetRotationX(float const& rot);
	void SetRotationY(float const& rot);
	void SetRotationZ(float const& rot);

	//���W�̎擾
	DirectX::SimpleMath::Vector3 GetPosition()const;
	//�g�嗦�̎擾
	DirectX::SimpleMath::Vector3 GetScale()const;

	//�ړ�
	void Move(DirectX::SimpleMath::Vector3 const& vel);

	//�X�V����
	virtual void Update()override {}
	void SpriteUpdate();
	//�`��
	virtual void Draw(DirectX::SimpleMath::Matrix* world = nullptr)override;

	//�\����\���̐؂�ւ��̃A�N�Z�T
	bool GetDrawFlag() const { return mDrawFlag; }
	void SetDrawFlag(bool const& flag) { mDrawFlag = flag; }

	//���݂̃��f���̔ԍ���Ԃ�
	int GetUseModelNum()const { return mUseModelNum; }

	//�X�v���C�g�̎����̎w��
	void SetConstTimer(int const& timer) { mConstTimer = timer; }

	//�X�v���C�g���f�����񂷂��ǂ����̃A�N�Z�T
	void SetSpriteFlag(bool const& flag) { mSpriteFlag = flag; }
		
	//�X�v���C�g���f���̍ő吔
	void SetMaxSpriteNum(int const& num) { mMaxSpriteNum = num; }

};
