/*
�����������\�����s���N���X�̊��N���X
�쐬���F2021/10/22
*/
#include"pch.h"
#include "NumberBase.h"


//�����x�����l
const float NumberBase::INIT_ALPHA = 1.f;	
//�����̐��̍ő吔
const int NumberBase::MAX_NUMTYPE_NUM = 10;


/*==============================================
�R���X�g���N�^
===============================================*/
NumberBase::NumberBase()
	:
	mTextureAlpha(INIT_ALPHA),
	mTextureKey("")
{
}

/*==============================================
�f�X�g���N�^
===============================================*/
NumberBase::~NumberBase()
{
}

/*==============================================
�擾������������K�v�Ȑ�����I�яo��:private
�����F�쐬���鐔���A����
�Ԃ�l�F�K�v�Ȑ���
===============================================*/
std::vector<int> NumberBase::ChooseNum(int num)
{
	//�Ԃ�l�p�ϐ��̐錾
	std::vector<int> returnNum;
	std::vector<int> instantNum;

	//1�K��邲�ƂɌ�������炵�Ă���
	for (int i = num; i >= 1; i /= MAX_NUMTYPE_NUM)
	{
		instantNum.push_back(i);
	}
	//�O����
	if (static_cast<int>(instantNum.size()) == 0)
	{
		instantNum.push_back(0);
	}

	//�T�C�Y�𑝂₷
	returnNum.resize(instantNum.size());

	returnNum[0] = instantNum[instantNum.size() - 1];

	//���ۂɕۑ�����l���Z�o����
	for (int i = static_cast<int>(returnNum.size()) - 1; i > 0; i--)
	{
		returnNum[i] = instantNum[i - 1] - (instantNum[i] * MAX_NUMTYPE_NUM);
	}

	//���Ԃ����ɖ߂�
	instantNum = returnNum;

	for (int i = 1; i < static_cast<int>(returnNum.size()); i++)
	{
		returnNum[i] = instantNum[static_cast<int>(returnNum.size()) - i];
	}

	return returnNum;
}

