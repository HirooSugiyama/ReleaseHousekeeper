/*
�ړI�̏ꏊ�ɉ摜�𕽖ʕ`�悷��N���X
(�P��摜�͂�����)
�쐬���F2021/06/05
*/
#pragma once

//���N���X
#include"ITexture.h"

namespace DirectX
{
	class SpriteBatch;
}
class ObjectTexture:public ITexture
{
private:
	//�ϐ�============================
	
	DirectX::SimpleMath::Vector4 mColor;

	//�ۑ��p�X�v���C�g�o�b�`
	DirectX::SpriteBatch* mpSpriteBatch;

	//�֐�============================

public:
	//�R���X�g���N�^
	ObjectTexture(DirectX::SimpleMath::Vector2 pos = { 0.f,0.f },
					DirectX::SimpleMath::Vector2 scale = { 1.f,1.f },
					float rot = 0.f, float alpha = 1.f);
	//�f�X�g���N�^
	~ObjectTexture();


	//������
	void Initialize()override;
	//�`��
	void Draw()override;

};