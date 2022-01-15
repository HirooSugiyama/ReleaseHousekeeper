/*
�������Ǘ��t�@�C��
*/
#include"pch.h"
#include"Money.h"


//�N���X�O���ŏ�����
Money* Money::sMoney = nullptr;

/*===================================
�R���X�g���N�^
===================================*/
Money::Money()
	:
	mFilepath("none"),
	mPossessionMoney()
{
}

/*=================================
���g�̃C���X�^���X
===================================*/
Money& Money::GetMoneyInstance()
{
	if (sMoney == nullptr)
	{
		sMoney = new Money();
	}
	return *sMoney;
}

/*=================================
�t�@�C�����̐ݒ�
�����F�t�@�C���p�X
===================================*/
void Money::LoadFileSet(std::string filepath)
{
	//�����̕ۑ�
	mFilepath = filepath;

	//���z�̏����ݒ�
	this->MoneyInit();
}

/*=================================
�폜����
===================================*/
void Money::Destroy()
{
	if (sMoney != nullptr)
	{
		delete sMoney;
		sMoney=nullptr;
	}
}

/*===================================
�������̏����ݒ�:private
===================================*/
void Money::MoneyInit()
{
	//�t�@�C���ϊ�
	std::ifstream ifs(mFilepath);
	//1�s�̏���ۑ�����ϐ�
	std::string lineBuf;

	//�����o��
	std::getline(ifs, lineBuf);

	mPossessionMoney = static_cast<int>(atof(lineBuf.c_str()));
}

