/*
�w�肳�ꂽ���̂̉e��\������N���X
�쐬���F2021/09/23
*/
#pragma once


//�h�����N���X
#include"FlatPolygon.h"

namespace DirectX
{
	class BasicEffect;
	struct VertexPositionTexture;
}

class Shadow:public FlatPolygon
{
private:
	//�ϐ�============================

	//�֐�============================

public:
	//�R���X�g���N�^	
	Shadow();								

	//�f�X�g���N�^
	~Shadow()override;

	//���b�v��������������
	void WrapInitialize();

};
