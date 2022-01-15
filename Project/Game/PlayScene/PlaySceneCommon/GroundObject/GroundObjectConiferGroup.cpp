/*
�j�t���̃��f�����Ǘ�����N���X
�쐬���F2021/08/19
*/

#include"pch.h"

#include "GroundObjectConiferGroup.h"

//���f���̊g�嗦
const DirectX::SimpleMath::Vector3 GroundObjectConiferGroup::CONIFER_SCALE(2.f,2.f,2.f);
//�j�t���O���[�v���f����Y���W
const float GroundObjectConiferGroup::CONIFER_MODEL_POSITION_Y = 1.f;


/*======================
�R���X�g���N�^
======================*/
GroundObjectConiferGroup::GroundObjectConiferGroup()
	:
	IGroundObject(),
	mpConiferModel(nullptr)
{
	mpConiferModel = std::make_unique<ObjectModel>();
}

/*======================
�f�X�g���N�^
======================*/
GroundObjectConiferGroup::~GroundObjectConiferGroup()
{

}

/*======================
������
======================*/
void GroundObjectConiferGroup::Initialize()
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("ConiferGroup");

	//���f���̐ݒ�
	mpConiferModel->SetModel(model);
	//�g�嗦�̐ݒ�
	mpConiferModel->SetScale(CONIFER_SCALE);
}

/*======================
�`�揈��
======================*/
void GroundObjectConiferGroup::Draw()
{
	mpConiferModel->Draw();
}

/*====================================
���f���̍��W��ݒ肷��
�����F���f���̍��W
====================================*/
void GroundObjectConiferGroup::SetConiferModelPosition(DirectX::SimpleMath::Vector3 const& pos)
{
	mpConiferModel->SetPosition(pos);
}
