/*
�摜�Ǘ��N���X�̃C���^�[�t�F�[�X�N���X

�쐬���F2021/12/01
*/

#include"pch.h"
#include"ITexture.h"

/*===============================================
�R���X�g���N�^
�����F���W�A�g�嗦�A��]���A�����x
===============================================*/
ITexture::ITexture(DirectX::SimpleMath::Vector2 pos,
				DirectX::SimpleMath::Vector2 scale,
				float rot, float alpha)
	:
	mPosition(pos),
	mScale(scale),
	mRot(rot),
	mAlpha(alpha),
	mTexture(nullptr),
	mInputLayout(nullptr)
{
}
