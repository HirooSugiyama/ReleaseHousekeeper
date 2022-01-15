/*
�x�����N���X
�쐬���F2021/10/06
*/
#pragma once

//����
#include"../PlaySceneCommon/ObjectModel/ObjectModel.h"

class DangerousLine
{
private:
	//���W
	static const DirectX::SimpleMath::Vector3 ASSETLINE_MODEL_POSITION;
	//�g�嗦
	static const DirectX::SimpleMath::Vector3 ASSETLINE_MODEL_SCALE;

	//���f�����
	std::unique_ptr<ObjectModel> mpAssertLineModel;

public:

	//�R���X�g���N�^
	DangerousLine();
	//�f�X�g���N�^
	~DangerousLine();
	//����������
	void Initialize();
	//�`�揈��
	void Draw();

	//Z���W�̎擾(�G�t�F�N�g��������W)(�֐��̓s����CPP�ŏ���)
	float GetLinePositionZ();
};
