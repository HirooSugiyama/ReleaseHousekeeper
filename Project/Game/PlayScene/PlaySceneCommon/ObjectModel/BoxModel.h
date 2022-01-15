/*
AABB�̓����蔻������������f���N���X
�쐬���F2021/06/12
*/
#pragma once

#include"ObjectModel.h"

class BoxModel :public ObjectModel
{
private:
	//�萔
	//�������l
	static const DirectX::SimpleMath::Vector3 InitCollider;

	//�g�嗦�𔼕��ɂ���
	static const int SCALE_HALF;


	//�ϐ�
	std::unique_ptr<AABB> mpAABBCollider;

public:
	//�R���X�g���N�^
	BoxModel();
	//�f�X�g���N�^
	~BoxModel();

	//�g�嗦�̔�����Ԃ�(AABB�̎Z�o�Ɏg�p)
	DirectX::SimpleMath::Vector3 ReturnHalfSize(
		DirectX::SimpleMath::Vector3 const& scale);


	//�A�N�Z�T
	AABB* GetAABBCollider()const { return mpAABBCollider.get(); }

	void SetAABBCollider(DirectX::SimpleMath::Vector3 const& min,
		DirectX::SimpleMath::Vector3 const& max);
};

