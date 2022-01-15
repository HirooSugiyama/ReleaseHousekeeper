/*
���_�N���X
�쐬���F2021/05/21
*/
#pragma once

//����
#include"../PlaySceneCommon/ObjectModel/BoxModel.h"

class Protecter
{
private:
	//�萔
		//���f���̍��W
	static const float PROTECTER_MODEL_POSITION_X;
	static const float PROTECTER_MODEL_POSITION_Y;
	static const float PROTECTER_MODEL_POSITION_Z;

		//���f���̊g�嗦
		//�����ڗp
	static const float PROTECTER_MODEL_SCALE_X;
	static const float PROTECTER_MODEL_SCALE_Y;
	static const float PROTECTER_MODEL_SCALE_Z;
	//���f�������~�X�̊p�x����
	static const float PROTECTER_DEBUG_SHIFT_ANGLE;

	//�ϐ�
	//���f���`��N���X
	std::unique_ptr<BoxModel> mpProtecterModel;

	//HP�����t���O
	bool mDamageFlag;


	//�֐�
public:
	//�R���X�g���N�^
	Protecter();
	//�f�X�g���N�^
	~Protecter();

	//������
	void Initialize();
	//�`��
	void Draw();

	//�����蔻���Ԃ�
	BoxModel* GetProtecterModel()const {return mpProtecterModel.get();}

	//HP�����t���O�̃A�N�Z�T
	bool GetDamageFlag() const { return mDamageFlag; }
	void SetDamageFlag(bool const& flag) { mDamageFlag = flag; }

	//�ڂ�Ƃɐ؂�ւ�
	void ChangeOldHouse();

};
