/*
�Ǘ��҃N���X�`HP��^�C�}�[�����`
�쐬���F2021/05/25
*/

#include"pch.h"
#include "Administrator.h"

//���ޏ������`��ʒu
const DirectX::SimpleMath::Vector2 Administrator::COUNTER_DROW_POSITION(1000.f, 190.f);

//�\���ꂸ�炵�p�ϐ�
const int Administrator::SHIFT_POSITION_NUM = 100;

/*===================================
�R���X�g���N�^
===================================*/
Administrator::Administrator()
	:
	mpAdTimer(nullptr),
	mpCelestialSphere(nullptr),
	mpScore(nullptr),
	mPhaseNum(0),
	mUsePriceNum(0),
	mClearBonusScoreNum(0)
{
	mpAdTimer = std::make_unique<Timer>();

	mpCelestialSphere = std::make_unique <CelestialSphere>();
	mpScore = std::make_unique <Score>();

}

/*===================================
�f�X�g���N�^
===================================*/
Administrator::~Administrator()
{
}

/*===================================
������
===================================*/
void Administrator::Initialize()
{
	mpCelestialSphere->Initialize();
}

/*===================================
�X�V
===================================*/
void Administrator::Update()
{
	mpAdTimer->Update();
}

/*==================================
�t�@�C����������擾
�����F�t�@�C����
===================================*/
void Administrator::LoadCSV(std::string const& filename)
{
	//�t�@�C���ϊ�
	std::ifstream ifs(filename);
	//1�s�̏���ۑ�����ϐ�
	std::string lineBuf;

	//1�s�̓ǂݍ��ݏ���_
	for (int i = 0; std::getline(ifs, lineBuf); i++)
	{
		//1�s�̏���stream�ɂ���
		std::stringstream lineStream(lineBuf);
		//1�}�X�̏��ۑ��p
		std::string tileBuf;

		//1�}�X�̏��ǂݍ��ݏ���
		for (int j = 0; std::getline(lineStream, tileBuf, ','); j++)
		{
			switch (j)
			{
				//�h�q���Ԃ��擾
				case DEFENCE_TIME:
				{
					int consttimer = atoi(tileBuf.c_str());
					mpAdTimer->SetMaxTime(consttimer);
					break;
				}
				//�t�F�[�Y�����擾
				case PHASE_NUM:	
				{
					mPhaseNum = atoi(tileBuf.c_str());
					break;
				}
				//�g�p�\���z���擾
				case PRICE:
				{
					mUsePriceNum = atoi(tileBuf.c_str());
					break;
				}	
				//�N���A���̃{�[�i�X�X�R�A���擾
				case CLEAR_BONUS:
				{
					mClearBonusScoreNum = atoi(tileBuf.c_str());
					break;
				}
			}
		}
	}
}
