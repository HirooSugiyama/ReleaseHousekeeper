/*
�ǃN���X
*/

#pragma once


//�萔�Q
#include"WallConstant.h"

//�O���錾
#include"../ObjectModel/BoxModel.h"

class Wall
{
private:
	//�ϐ�

	//���f���`��N���X
	std::unique_ptr<BoxModel> mpWallModel;

public:
	//�֐�
	//�R���X�g���N�^
	Wall();
	//�f�X�g���N�^
	~Wall();
	//������
	void Initialize(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 scale);

	//�`��
	void Draw();

	//�����蔻���Ԃ�
	BoxModel* GetWallModel()const { return mpWallModel.get(); }
};