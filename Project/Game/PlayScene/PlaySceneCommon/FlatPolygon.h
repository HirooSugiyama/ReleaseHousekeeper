/*
�摜�𕽖ʕ`�悷��N���X
�쐬���F2021/11/13
*/
#pragma once


#include <PrimitiveBatch.h>

//���N���X
#include"FlatPolygonBase.h"

namespace DirectX
{
	class BasicEffect;
	struct VertexPositionTexture;
}

class FlatPolygon :public FlatPolygonBase
{
private:

	//�ϐ�============================

	//�g�嗦
	DirectX::SimpleMath::Vector2 mScale;

	//�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;

	//�C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> mpPrimitiveBatch;

	//�x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> mpBasicEffect;


	//�֐�============================

public:
	//�R���X�g���N�^	
	FlatPolygon();

	//�f�X�g���N�^
	~FlatPolygon()override;

	//������
	void Initialize()override;

	//�`��
	void Draw(DirectX::SimpleMath::Vector3 pos)override;

	//�g�嗦�̃A�N�Z�T
	void SetScale(DirectX::SimpleMath::Vector2 scale)override { mScale = scale; }

	//�摜��ݒ肷��
	void SetTexture(std::string texPath);
};
