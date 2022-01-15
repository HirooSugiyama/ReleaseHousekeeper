/*
�ԐF�_�Ńe�N�X�`���Ǘ��N���X
�쐬���F2021/10/07
*/
#pragma once

//�O���錾
#include"../Common/ObjectTexture.h"

class RedAssert
{
private:
	//�萔

	//���W
	static const DirectX::SimpleMath::Vector2 DANGEROUSUI_TEXTURE_POSITION;
	//�g�嗦
	static const DirectX::SimpleMath::Vector2 DANGEROUSUI_TEXTURE_SCALE;

	//�����x����
	static const float DANGEROUSUI_SIN_NUM;
	//�����x�̒l����
	static const float DANGEROUSUI_SIN_SHIFT;


	//�ϐ�
	//sin�l
	float mSin;

	//�摜
	std::unique_ptr<ObjectTexture> mpDangerousUI;

	//�`�悷�邩�ǂ����̔���p�t���O
	bool mPassFlag;

public:

	//�R���X�g���N�^
	RedAssert();
	//�f�X�g���N�^
	~RedAssert();
	//����������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

	//������ʂ����ǂ����̃t���O�̃A�N�Z�T
	void SetPassFlag(bool const& flag) { mPassFlag = flag; }

};
