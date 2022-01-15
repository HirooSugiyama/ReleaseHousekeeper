/*
���U���g�Ŏg�p�������ǂݍ��݁A�Ǘ�����N���X
�쐬���F2021/10/23
*/
#pragma once

//�萔�̎g�p
#include"ResultDrawStringConstant.h"

class ResultInfo
{
private:

	//�X�R�A�����L���O�Ǘ��p�ϐ�
	int mScoreRanking[ResultDrawStringConstant::SCORE_RANKING_STORAGE];

	//�ǂݍ��ރt�@�C���̃p�X
	std::string mFilePath;

public:

	//�R���X�g���N�^
	ResultInfo();
	//�f�X�g���N�^
	~ResultInfo();
	//����������
	void Initialize(int const& stagenum);
	//�X�V����
	void Update();

	//�X�R�A�����L���O�ǂݍ���
	void LoadScoreRanking();

	//�X�R�A�������L���O�ɓ����
	void SetScoreRanking(int const& scorenum);


	//�X�R�A����������
	void WriteScore();

	//�X�R�A�̎擾
	int GetScoreRanking(int const& i)const { return mScoreRanking[i]; }
};
