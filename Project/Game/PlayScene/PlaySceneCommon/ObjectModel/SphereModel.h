/*
���̓����蔻������������f���N���X
�쐬���F2021/06/12
*/
#pragma once

#include"ObjectModel.h"

class SphereModel :public ObjectModel
{
private:
	//�����蔻�菉���l
	static const float InitCollider;

	//�ϐ�
	std::unique_ptr<Sphere> mpSphereCollider;

public:
	//�R���X�g���N�^
	SphereModel();
	//�f�X�g���N�^
	~SphereModel();

	//�A�N�Z�T
	Sphere* GetSphereCollider() { return mpSphereCollider.get(); }

	void SetSphereCollider(const DirectX::SimpleMath::Vector3& center, float radius);
};
