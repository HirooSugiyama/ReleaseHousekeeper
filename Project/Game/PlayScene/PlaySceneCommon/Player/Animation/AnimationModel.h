/*
�A�j���[�V������p���f���`��N���X
�쐬���F2021/09/05
*/
#pragma once

#include"../../ObjectModel/IModel.h"

namespace DirectX
{
	class SpriteBatch;
}

class AnimationModel:public IModel
{
protected:
	//�萔

	//���������̒萔
	static const DirectX::SimpleMath::Vector3 INIT_POSITION;
	//���g�p���̒萔
	static const DirectX::SimpleMath::Vector3 NOT_USE_POSITION;
	
	//�ϐ�

	// �R�����X�e�[�g
	DirectX::CommonStates* mpCommonState;
	// �X�v���C�g�o�b�`
	DirectX::SpriteBatch* mpSpriteBatch;
	// �X�v���C�g�t�H���g
	DirectX::SpriteFont* mpSpriteFont;

	//���f���֌W
	DirectX::SimpleMath::Matrix mWorld;

	//�r���[�s��
	DirectX::SimpleMath::Matrix mView;
	//�ˉe�s��
	DirectX::SimpleMath::Matrix mProj;

	//�G�t�F�N�g�t�@�N�g���[
	std::unique_ptr<DirectX::IEffectFactory> mFxFactory;
	//���f���̕ۑ���
	DirectX::Model* mModel;

	//���W
	DirectX::SimpleMath::Matrix mPosition;
	DirectX::SimpleMath::Matrix mScale;
	DirectX::SimpleMath::Matrix mRotX;
	DirectX::SimpleMath::Matrix mRotY;
	DirectX::SimpleMath::Matrix mRotZ;

	//�\���t���O:true	�\��	false:��\��
	bool mDrawFlag;

	//�֐�
public:
	//�R���X�g���N�^
	AnimationModel();

	//�f�X�g���N�^
	~AnimationModel();

	//���f���̎w��
	void SetModel(DirectX::Model* model);
	//���f�����̃A�N�Z�T
	DirectX::Model* GetModel()const  {return mModel;}

	//���W�̎w��
	void SetPosition(DirectX::SimpleMath::Vector3 const& pos);
	//�g�嗦�̎w��
	void SetScale(DirectX::SimpleMath::Vector3 const& scale);
	//��]�̎w��
	void SetRotationX(float const& rot);
	void SetRotationY(float const& rot);
	void SetRotationZ(float const& rot);

	//���W�̎擾
	DirectX::SimpleMath::Matrix GetPosition()const;

	//�g�嗦�̎擾
	DirectX::SimpleMath::Matrix GetScale()const;

	//��]�̎w��
	DirectX::SimpleMath::Matrix GetRotationX()const;
	DirectX::SimpleMath::Matrix GetRotationY()const;
	DirectX::SimpleMath::Matrix GetRotationZ()const;


	//���[���h���W�̐ݒ�
	void SetWorld(DirectX::SimpleMath::Matrix const& world);


	//�X�V����
	virtual void Update()override {};
	//�`��
	virtual void Draw(DirectX::SimpleMath::Matrix* world = nullptr)override;

	//�\����\���̐؂�ւ��̃A�N�Z�T
	bool GetDrawFlag() const { return mDrawFlag; }
	void SetDrawFlag(bool const&flag) { mDrawFlag = flag; }

};
