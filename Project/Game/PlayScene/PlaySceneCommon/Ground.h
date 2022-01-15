/*
�n�ʂ̃N���X
�쐬���F2021/06/28
*/
#pragma once


//����
#include"../PlaySceneCommon/ObjectModel/ObjectModel.h"

class Ground
{
private:
	//�萔
	//�n�ʂ̒��S���W
	static const DirectX::SimpleMath::Vector3 GROUND_POSITION;
	//�n�ʂ̊g�嗦
	static const DirectX::SimpleMath::Vector3 GROUND_SCALE;

	//�ϐ�
	//���f���`��N���X
	std::unique_ptr<ObjectModel> mpGroundModel;

public:
		//�֐�
	//�R���X�g���N�^
	Ground();
	//�f�X�g���N�^
	~Ground();
	//������
	void Initialize();
	//�`��
	void Draw();

};
