/*
�j�t���̃��f�����Ǘ�����N���X
�쐬���F2021/08/19
*/
#pragma once

//���N���X
#include"IGroundObject.h"


#include"../ObjectModel/ObjectModel.h"

class GroundObjectShop :public IGroundObject
{
private:

	//�V���b�v���f���̊g�嗦
	static const DirectX::SimpleMath::Vector3 SHOP_SCALE;

	//�V���b�v���f����Y���W
	static const float SHOP_MODEL_POSITION_Y;

	//�V���b�v���f��
	std::unique_ptr<ObjectModel> mpShopModel;


public:
	//�R���X�g���N�^
	GroundObjectShop();

	//�f�X�g���N�^
	~GroundObjectShop()override;
	//������
	void Initialize()override;

	void Update()override {};

	//�`��
	void Draw()override;

	//���f���̍��W��ݒ肷��
	void SetShopModelPosition(DirectX::SimpleMath::Vector3 const& pos);

	//Y���W��Ԃ�
	float GetShopModelPositionY()const { return SHOP_MODEL_POSITION_Y; }

	//�g�嗦���擾
	DirectX::SimpleMath::Vector3 GetConiferScale() const { return SHOP_SCALE; }
};