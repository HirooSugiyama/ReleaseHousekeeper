/*
�ǂ�u������p���C���̃N���X
�쐬���F2021/08/28
*/
#pragma once





//�񋓌^�̎g�p
#include"GridLineType.h"

//����
#include"../ObjectModel/ObjectModel.h"

class GridLine
{
private:
	//�萔

	//���C���̍��W
	//X���W(�Ֆʒ��S���W)
	static const float LINE_MODEL_CENTER_POSITION_X;
	//Y���W(����)
	static const float LINE_MODEL_POSITION_Y;
	//Z���W(�Ֆʒ��S���W)
	static const float LINE_MODEL_CENTER_POSITION_Z;

	//���C�����f���̊g�嗦
	//���ʊg�嗦
	static const float LINE_MODEL_SCALE_Y;
	static const DirectX::SimpleMath::Vector3 VERTICAL_LINE_MODEL_SCALE;
	static const DirectX::SimpleMath::Vector3 HORIZONTAL_LINE_MODEL_SCALE;


	//���̃��f��
	std::unique_ptr<ObjectModel> mpLineModel;

	//���C���̓����蔻��
	std::unique_ptr<LineSegment> mpLineCollider;


public:
	
	//�R���X�g���N�^
	GridLine();
	//�f�X�g���N�^
	~GridLine();
	//������
	void Initialize(eGridLineType const& lineType);
	//�`�揈��
	void Draw();

	//���W��ݒ肷��
	void SetLineModelPosition(eGridLineType const& lineType,float const& pos);

	//�����蔻��̃A�N�Z�T
	LineSegment* GetLineCollider()const { return mpLineCollider.get(); };

private:

	//�����蔻���ݒ肷��
	void ColliderSet();

	//�c���̍��W�ݒ菈��
	void SetModelPositionX(float const& posX);
	//�����̍��W�ݒ菈��
	void SetModelPositionZ(float const& posZ);

};
