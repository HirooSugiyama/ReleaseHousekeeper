/*
���ʃ|���S���`����N���X
�쐬���F2021/11/13
*/
#pragma once
#include <SimpleMath.h>




class FlatPolygonBase
{
protected:


	//�R���X�g���N�^
	FlatPolygonBase() = default;
	//�f�X�g���N�^
	virtual ~FlatPolygonBase() = default;

public:

	//������
	virtual void Initialize() = 0;

	//�`��
	virtual void Draw(DirectX::SimpleMath::Vector3 pos) = 0;

	//�g�嗦�̃A�N�Z�T
	virtual void SetScale(DirectX::SimpleMath::Vector2 scale) = 0;


};
