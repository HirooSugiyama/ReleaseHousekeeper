/*
�j�t���̃��f�����Ǘ�����N���X
�쐬���F2021/08/19
*/

#include"pch.h"

#include "GroundObjectShop.h"


//�V���b�v���f���̊g�嗦
const DirectX::SimpleMath::Vector3 GroundObjectShop::SHOP_SCALE(4.f, 4.f, 4.f);
//�V���b�v���f����Y���W
const float GroundObjectShop::SHOP_MODEL_POSITION_Y = 1.f;


/*======================
�R���X�g���N�^
======================*/
GroundObjectShop::GroundObjectShop()
	:
	IGroundObject(),
	mpShopModel(nullptr)
{
	mpShopModel = std::make_unique<ObjectModel>();
}

/*======================
�f�X�g���N�^
======================*/
GroundObjectShop::~GroundObjectShop()
{

}

/*======================
������
======================*/
void GroundObjectShop::Initialize()
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("Shop");

	//���f���̐ݒ�
	mpShopModel->SetModel(model);
	//�g�嗦�̐ݒ�
	mpShopModel->SetScale(SHOP_SCALE);
}

/*======================
�`�揈��
======================*/
void GroundObjectShop::Draw()
{
	mpShopModel->Draw();
}

/*====================================
���f���̍��W��ݒ肷��
�����F���f���̍��W
====================================*/
void GroundObjectShop::SetShopModelPosition(DirectX::SimpleMath::Vector3 const& pos)
{
	mpShopModel->SetPosition(pos);
}
