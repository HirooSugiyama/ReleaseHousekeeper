/*
�����o���Ԃ̃��f�����Ǘ�����N���X
�쐬���F2021/08/19
*/
#pragma once

//���N���X
#include"IGroundObject.h"

//����
#include"../ObjectModel/ObjectModel.h"


class GroundObjectMoveCar :public IGroundObject
{
private:

	//���f���̊g�嗦
	static const DirectX::SimpleMath::Vector3 MOVE_CAR_SCALE;

	//�����ԃ��f����Y���W
	static const float MOVE_CAR_MODEL_POSITION_Y;

	//�����ԃ��f��
	std::unique_ptr<ObjectModel> mpMoveCarModel;

public:
	//�R���X�g���N�^
	GroundObjectMoveCar();

	//�f�X�g���N�^
	~GroundObjectMoveCar()override;

	//������
	void Initialize()override;

	//�X�V����
	void Update()override;

	//�`��
	void Draw()override;

	//���f���̍��W��ݒ肷��
	void SetMoveCarModelPosition(DirectX::SimpleMath::Vector3 const& pos);

	//Y���W��ϊ�����
	float GetMoveCarModelPositionY() const { return MOVE_CAR_MODEL_POSITION_Y; };

	//�g�嗦���擾
	DirectX::SimpleMath::Vector3 GetMoveCarScale()const { return MOVE_CAR_SCALE; }
};