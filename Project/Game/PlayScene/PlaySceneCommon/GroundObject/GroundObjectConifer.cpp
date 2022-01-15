/*
�j�t���̃��f�����Ǘ�����N���X
�쐬���F2021/08/19
*/

#include"pch.h"

#include "GroundObjectConifer.h"


	//���f���̊g�嗦
const DirectX::SimpleMath::Vector3 GroundObjectConifer::CONIFER_SCALE(2.f,2.f,2.f);
//�j�t�����f����Y���W
const float GroundObjectConifer::CONIFER_MODEL_POSITION_Y = 1.f;


/*======================
�R���X�g���N�^
======================*/
GroundObjectConifer::GroundObjectConifer()
	:
	IGroundObject(),
	mpConiferModel(nullptr)
{
	mpConiferModel = std::make_unique<ObjectModel>();
}

/*======================
�f�X�g���N�^
======================*/
GroundObjectConifer::~GroundObjectConifer()
{

}

/*======================
������
======================*/
void GroundObjectConifer::Initialize()
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("Conifer");

	//���f���̐ݒ�
	mpConiferModel->SetModel(model);
	//�g�嗦�̐ݒ�
	mpConiferModel->SetScale(CONIFER_SCALE);
}

/*======================
�`�揈��
======================*/
void GroundObjectConifer::Draw()
{
	mpConiferModel->Draw();
}

/*====================================
���f���̍��W��ݒ肷��
�����F���f���̍��W
====================================*/
void GroundObjectConifer::SetConiferModelPosition(DirectX::SimpleMath::Vector3 const& pos)
{
	mpConiferModel->SetPosition(pos);
}
