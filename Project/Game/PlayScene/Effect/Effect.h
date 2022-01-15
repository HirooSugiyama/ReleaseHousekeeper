/*
3D���W��2D�摜��`�悷��ėp�N���X
(�g�p��F�G�t�F�N�g�Ȃ�)
�쐬���F2021/09/02
*/
#pragma once





#include <VertexTypes.h> 
#include <PrimitiveBatch.h>
#include "Libraries/DirectXTK/Inc/Effects.h"



namespace DirectX
{
	class SpriteBatch;
}
class EffectSpriteTexture
{
private:

	//�萔============================
	static const float UV_POSITION_MAX;



	//�ϐ�============================

	//���W
	DirectX::SimpleMath::Vector3 mPosition;
	//�g�嗦
	DirectX::SimpleMath::Vector2 mScale;
	//�ۑ��p�X�v���C�g�o�b�`
	DirectX::SpriteBatch* mpSpriteBatch;

	//�X�v���C�g�^�C�}�[
	int mSpriteTimer;
	//�^�C�}�[(�Œ�l)
	int mConstTimer;
	//�X�v���C�g�^�C�}�[�ғ��t���O
	bool mSpriteFlag;
	//�s��
	int mLineMaxNum;//�s�ő吔
	int mLineNum;	//���݂̍s��

	//���������̕ۑ�
	int mHorizontalCutNum;
	//���݂̏ꏊ
	int mWidthNum;
	//������
	float mWidthIncreaseNum;	//����
	float mHeightIncreaseNum;	//�c��




	//�X�v���C�g�؂���P��
	DirectX::SimpleMath::Vector2 mSpriteSrc;

	//�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;

	//�C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;

	// �v���~�e�B�u�o�b�` 
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> mpPrimitiveBatch;

	//�x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> mpBasicEffect;



	//���W�֌W(�|���S��)
	DirectX::SimpleMath::Matrix mWorld;
	DirectX::SimpleMath::Vector3  mCamera;

	//�J��Ԃ��t���O
	bool mLoopFlag;

	//�����x
	float mAlpha;


	//�֐�============================

public:


	//�R���X�g���N�^	
	EffectSpriteTexture(int linenum = 1,							//�摜�����s��						
		DirectX::SimpleMath::Vector3 pos = { 0.f,0.f,0.f },		//�\�����W						
		DirectX::SimpleMath::Vector2 scale = { 1.f,1.f });		//�\���g�嗦									


	//�f�X�g���N�^
	~EffectSpriteTexture();

	//�摜�̎w��
	void SetFileName(const wchar_t* filepath);
	void SetTexture(ID3D11ShaderResourceView* texture);

	//������
	void Initialize();

	//�X�V����
	void Update();

	//�X�v���C�g�^�C�}�[�̐ݒ�
	void SetConstTimer(int timer) { mConstTimer = timer; }

	//�`��
	void ExtendDraw();

	//�I������
	void Finalize();


	//�J�������W�̕ۑ�
	void SetCameraEyePosition(DirectX::SimpleMath::Vector3 eyePosition)
	{
		mCamera = eyePosition;
	}


	//�A�N�Z�T

	//���W�̃A�N�Z�T
	void SetPosition(DirectX::SimpleMath::Vector3 pos) { mPosition = pos; }
	DirectX::SimpleMath::Vector3 GetPosition() { return mPosition; }

	//�g�嗦�̃A�N�Z�T
	void SetScale(DirectX::SimpleMath::Vector2 scale) { mScale = scale; }
	DirectX::SimpleMath::Vector2 GetScale() { return mScale; }


	//�X�v���C�g����t���O�̃A�N�Z�T
	bool GetSpriteFlag() { return mSpriteFlag; }
	bool* GetSpriteFlagAddress() { return &mSpriteFlag; }
	void SetSpriteFlag(bool flag) { mSpriteFlag = flag; }
	//�X�v���C�g�ʒu�̃A�N�Z�T
	void SetWidthNum(int num) { mWidthNum = num; }
	int GetWidthNum() { return mWidthNum; }


	//���������̃A�N�Z�T
	int GetHorizontalCutNum() { return mHorizontalCutNum; }
	void SetHorizontalCutNum(int num)
	{
		mHorizontalCutNum = num;

		//�P/�������ő����ʂ����߂���(�Đݒ�)
		mWidthIncreaseNum = 1.f / static_cast<float>(mHorizontalCutNum);
	};


	//�摜�����擾����
	ID3D11ShaderResourceView* GetTexture() { return mTexture.Get(); }

	//�X�v���C�g�̃^�C�}�[�l���擾����
	int GetConstTimer() { return mConstTimer; }

	//�J��Ԃ��p�t���O�̃A�N�Z�T
	void SetLoopFlag(bool flag) { mLoopFlag = flag; }

	//�����x�̃A�N�Z�T
	void SetAlpha(float alpha) { mAlpha = alpha; }
};