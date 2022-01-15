/*
�X�e�[�W�I���^�O
�쐬���F2021/10/21
*/
#pragma once

//����
#include"../Common/ObjectTexture.h"

class StageNumberTag
{
private:
	//�摜�g�嗦
	static const DirectX::SimpleMath::Vector2 TEX_SCALE;

	//�摜�`��ʒu���琔���`��ʒu���Z�o���邽�߂̒萔
	static const DirectX::SimpleMath::Vector2 NUM_SHIFT;


	//�摜�`��ʒu
	DirectX::SimpleMath::Vector2 mDrawPosition;


	//���j�[�N�|�C���^
	std::unique_ptr<ObjectTexture> mpBackGround;

	//�`�敶��
	int mDrawStageString;

public:

	//�R���X�g���N�^
	StageNumberTag();
	//�f�X�g���N�^
	~StageNumberTag();
	//����������
	void Initialize();
	//�`�揈��
	void Draw(bool const& flag=true);

	//�`��ʒu�̎w��
	void SetPosition(DirectX::SimpleMath::Vector2 const& pos);

	//�X�e�[�W�ԍ��̃A�N�Z�T
	void SetStageNum(int const& i) { mDrawStageString = i; }

};
