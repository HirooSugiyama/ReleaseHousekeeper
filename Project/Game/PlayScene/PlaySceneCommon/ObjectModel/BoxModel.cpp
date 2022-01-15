/*
AABB�̓����蔻������������f���N���X
�쐬���F2021/06/12
*/

#include"pch.h"
#include"BoxModel.h"

//�萔
//�������l
const DirectX::SimpleMath::Vector3 BoxModel::InitCollider(-10.f, -10.f, -10.f);

/*===================================
�R���X�g���N�^
===================================*/
BoxModel::BoxModel()
	:
	ObjectModel(),
	mpAABBCollider()
{
	mpAABBCollider = std::make_unique<AABB>();
	mpAABBCollider->mMin = InitCollider;
	mpAABBCollider->mMax = InitCollider;
}

/*===================================
�f�X�g���N�^
===================================*/
BoxModel::~BoxModel()
{
}


/*==================================================
�g�嗦�̔�����Ԃ�(�ŏ��l�A�ő�l�̎Z�o�Ɏg�p)
�����F�g�嗦
�Ԃ�l�F�g�嗦�̔����̒l
====================================================*/
DirectX::SimpleMath::Vector3 BoxModel::ReturnHalfSize(DirectX::SimpleMath::Vector3 const& scale)
{
	DirectX::SimpleMath::Vector3 returnsize;

	returnsize.x = scale.x / Utility::SCALE_HALF;
	returnsize.y = scale.y / Utility::SCALE_HALF;
	returnsize.z = scale.z / Utility::SCALE_HALF;
	return returnsize;
}

/*=========================================
���̃Z�b�^�[
�����Fmin(�ŏ��l)�Amax(�ő�l)
=========================================*/
void BoxModel::SetAABBCollider(DirectX::SimpleMath::Vector3 const& min,
	DirectX::SimpleMath::Vector3 const& max)
{
	mpAABBCollider->mMin = min;
	mpAABBCollider->mMax = max;
}
