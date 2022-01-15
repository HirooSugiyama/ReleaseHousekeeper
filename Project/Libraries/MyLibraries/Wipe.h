/*
���C�v

�쐬���F2021/12/21
*/
#pragma once

class Wipe
{
private:
	//�S�J��
	static const float FULL_OPEN;
	static const float FULL_CLOSE;


	//�s�N�Z���V�F�[�_�ɓn���萔�o�b�t�@�̍\����
	struct cbChangeEveryFrame
	{
		float radius;		//���a�̔䗦�F�O�`�P
		float aspectRatio;	//�A�X�y�N�g��
		DirectX::SimpleMath::Vector2 dummy;//�p�f�B���O�f�[�^(2�o�C�g��)
	};

	//�萔�o�b�t�@�֘A
	cbChangeEveryFrame mcbChangeEveryFrame;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mCbBuffer;

	//2D�e�N�X�`���o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mTextureBuffer;

	//�V�F�[�_�\���\�[�X�r���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mShaderResourceView;

	//�I�[�v���܂��̓N���[�Y����܂ł̃��C�v����
	float mInterval;

	//����(0�`1)�F0�̏ꍇ���Ă���
	float mRate;

	//�I�[�v���t���O:true�̏ꍇ�I�[�v��
	bool mFlagOpen;


	//�s�N�Z���V�F�[�_�֘A
	Microsoft::WRL::ComPtr<ID3DBlob> mpBlob;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mpPixelShader;

public:

	//�R���X�g���N�^
	Wipe(float interval = 1.f, float rate = 1.f);
	//�f�X�g���N�^
	~Wipe();
	//����������
	void Initialize();
	//�X�V����
	bool Update(float elaspedTime);
	//�`�揈��
	void Draw();

	//�A�N�Z�T
	void SetOpen()
	{
		mFlagOpen = true; 
	}
	void SetClose()
	{
		mFlagOpen = false; 
	}
	bool IsOpen();
};
