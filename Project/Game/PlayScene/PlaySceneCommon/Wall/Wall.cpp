/*
�ǃN���X
*/

#include<pch.h>
#include"Wall.h"

/*===================================
�R���X�g���N�^
===================================*/
Wall::Wall()
	:
	mpWallModel(nullptr)
{
	//���f���̃������m��
	mpWallModel = std::make_unique<BoxModel>();
}

/*===================================
�f�X�g���N�^
===================================*/
Wall::~Wall()
{
}
/*===================================
����������
�����Fpos(���W)�Ascale(�g�嗦)
===================================*/
void Wall::Initialize(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 scale)
{

	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("Wall");
	mpWallModel->SetModel(model);
	mpWallModel->SetPosition(pos);
	mpWallModel->SetScale(scale);

		/*�����蔻�萶��*/
	//�g�嗦�̔����̒l�𐶐�
	DirectX::SimpleMath::Vector3 halfsize = mpWallModel->ReturnHalfSize(scale);
	//�ݒ�
	mpWallModel->SetAABBCollider(pos - halfsize, pos + halfsize);
}

/*===================================
�`�揈��
===================================*/
void Wall::Draw()
{
	mpWallModel->Draw();
}