/*
�����o���Ԃ̃��f�����Ǘ�����N���X
�쐬���F2021/08/19
*/

#include"pch.h"

#include "GroundObjectMoveCar.h"

//���f���̊g�嗦
const DirectX::SimpleMath::Vector3 GroundObjectMoveCar::MOVE_CAR_SCALE(3.f,3.f,3.f);
	//�j�t�����f����Y���W
const float GroundObjectMoveCar::MOVE_CAR_MODEL_POSITION_Y = 1.f;



/*======================
�R���X�g���N�^
======================*/
GroundObjectMoveCar::GroundObjectMoveCar()
	:
	IGroundObject(),
	mpMoveCarModel(nullptr)
{
	mpMoveCarModel = std::make_unique<ObjectModel>();
}

/*======================
�f�X�g���N�^
======================*/
GroundObjectMoveCar::~GroundObjectMoveCar()
{
}

/*======================
������
======================*/
void GroundObjectMoveCar::Initialize()
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("GreenCar");

	//���f���̐ݒ�
	mpMoveCarModel->SetModel(model);
	//�g�嗦�̐ݒ�
	mpMoveCarModel->SetScale(MOVE_CAR_SCALE);
}

/*======================
�X�V����
======================*/
void GroundObjectMoveCar::Update()
{


}

/*======================
�`�揈��
======================*/
void GroundObjectMoveCar::Draw()
{
	mpMoveCarModel->Draw();
}

/*====================================
���f���̍��W��ݒ肷��
�����F���f���̍��W
====================================*/
void GroundObjectMoveCar::SetMoveCarModelPosition(DirectX::SimpleMath::Vector3 const& pos)
{
	mpMoveCarModel->SetPosition(pos);
}
