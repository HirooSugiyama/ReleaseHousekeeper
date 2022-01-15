/*
�摜�Ǘ��N���X�̃C���^�[�t�F�[�X�N���X

�쐬���F2021/12/01
*/
#pragma once




class ITexture
{
private:
	//���W
	DirectX::SimpleMath::Vector2 mPosition;
	//�g�嗦
	DirectX::SimpleMath::Vector2 mScale;
	//��]��
	float mRot;
	// �����x
	float mAlpha;

	//�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;

	//�C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;

public:
	//�R���X�g���N�^
	ITexture(DirectX::SimpleMath::Vector2 pos,
		DirectX::SimpleMath::Vector2 scale,
		float rot, float alpha);

	//����������
	virtual void Initialize() = 0;

	//�`�揈��
	virtual void Draw() = 0;

	//�摜�̎w��
	void SetTexture(ID3D11ShaderResourceView* texture) { mTexture = texture; }
	ID3D11ShaderResourceView* GetTexture() { return mTexture.Get(); }



	//���W�̎w��
	void SetPosition(DirectX::SimpleMath::Vector2 const& pos) { mPosition = pos; }
	//�g�嗦�̎w��
	void SetScale(DirectX::SimpleMath::Vector2 const& scale) { mScale = scale; }
	//��]���̎w��
	void SetRot(float const& rot) { mRot = rot; }
	//�����x�̎w��
	void SetAlpha(float const& alpha) { mAlpha = alpha; }
	float GetAlpha()const { return mAlpha; }

	//���W�̎擾
	DirectX::SimpleMath::Vector2 GetPosition()const { return mPosition; }
	//�g�嗦�̎擾
	DirectX::SimpleMath::Vector2 GetScale()const { return mScale; }

protected:
	//��]���̎擾
	float GetRot() { return mRot; }
};
