/*
�j�t���̃��f�����Ǘ�����N���X
�쐬���F2021/08/19
*/
#pragma once

//���N���X
#include"IGroundObject.h"
//����
#include"../ObjectModel/ObjectModel.h"


class GroundObjectConifer :public IGroundObject
{
private:

	//���f���̊g�嗦
	static const DirectX::SimpleMath::Vector3 CONIFER_SCALE;

	//�j�t�����f����Y���W
	static const float CONIFER_MODEL_POSITION_Y;

	//�j�t�����f��
	std::unique_ptr<ObjectModel> mpConiferModel;


public:
	//�R���X�g���N�^
	GroundObjectConifer();

	//�f�X�g���N�^
	~GroundObjectConifer()override;
	//������
	void Initialize()override;

	void Update()override {};

	//�`��
	void Draw()override;

	//���f���̍��W��ݒ肷��
	void SetConiferModelPosition(DirectX::SimpleMath::Vector3 const& pos);

	//Y���W��ϊ�����
	float GetConiferModelPositionY() const{ return CONIFER_MODEL_POSITION_Y; };

	//�g�嗦���擾
	DirectX::SimpleMath::Vector3 GetConiferScale() const{ return CONIFER_SCALE; }
};