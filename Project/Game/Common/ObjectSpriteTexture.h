/*
�ړI�̏ꏊ�ɉ摜�𕽖ʕ`�悷��N���X
(�X�v���C�g�摜�͂�����)
�쐬���F2021/06/21
*/
#pragma once

//���N���X
#include"ITexture.h"

namespace DirectX
{
	class SpriteBatch;
}
class ObjectSpriteTexture:public ITexture
{
private:
	//�ϐ�============================

	//�؂�����W
	RECT mSrc;

	//�ۑ��p�X�v���C�g�o�b�`
	DirectX::SpriteBatch* mpSpriteBatch;

	//�X�v���C�g�؂���P��
	DirectX::SimpleMath::Vector2 mSpriteSrc;

	//�֐�============================

public:
	//�R���X�g���N�^
	ObjectSpriteTexture(RECT src,								//�؂�����W
		DirectX::SimpleMath::Vector2 pos = { 0.f,0.f },			//�\�����W						
		DirectX::SimpleMath::Vector2 scale = { 1.f,1.f },		//�\���g�嗦											
		float rot = 0.f,										//��]					
		float alpha = 1.f);										//�����x	


	//�f�X�g���N�^
	~ObjectSpriteTexture();

	//������
	void Initialize()override;

	//�`��
	void Draw()override;

	//�؂���ʒu�ύX����
	void SetRect(RECT const& rect) { mSrc = rect; }

	//�w��̕��������ɉ摜���ړ�������
	void Beside(float const& size,int const& shiftnum)
	{
		mSrc.right += static_cast<LONG>(size* shiftnum);
		mSrc.left += static_cast<LONG>(size * shiftnum);
	}
};