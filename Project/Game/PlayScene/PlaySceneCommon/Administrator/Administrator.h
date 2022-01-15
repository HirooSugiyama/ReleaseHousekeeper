/*
�Ǘ��҃N���X�`HP��^�C�}�[�����`
�쐬���F2021/05/25
*/
#pragma once


//����
#include"CelestialSphere.h"
#include"Score.h"
#include"Timer.h"

enum AdCSV
{
	DEFENCE_TIME,		//��������
	PHASE_NUM,			//�t�F�[�Y��
	PRICE,				//�g�p�\���z
	CLEAR_BONUS,		//�N���A���̃{�[�i�X�X�R�A
};


class Administrator
{
private:

	//�萔

	//���ޏ������`��ʒu
	static const DirectX::SimpleMath::Vector2 COUNTER_DROW_POSITION;
	//�\���ꂸ�炵�p�ϐ�
	static const int SHIFT_POSITION_NUM;

	//�^�C�}�[
	std::unique_ptr<Timer> mpAdTimer;

	//�V��
	std::unique_ptr<CelestialSphere> mpCelestialSphere;

	//�X�R�A
	std::unique_ptr<Score> mpScore;

	//�t�F�[�Y��
	int mPhaseNum;

	//�g�p�\���z
	int mUsePriceNum;

	//�N���A���̃{�[�i�X�X�R�A
	int mClearBonusScoreNum;

public:
	//�R���X�g���N�^
	Administrator();
	//�f�X�g���N�^
	~Administrator();
	//������
	void Initialize();
	//�X�V
	void Update();

	//�^�C�}�[�ɒ��ڃA�N�Z�X����
	Timer* DirectAcceserTimer() const { return mpAdTimer.get(); }


	//�V���֒��ڃA�N�Z�X����
	CelestialSphere* DirectAcceserCelestialSphere() const { return mpCelestialSphere.get(); }


	//�X�R�A�֒��ڃA�N�Z�X����
	Score* DirectAcceserScore() const { return mpScore.get(); }


	//�t�@�C���ǂݍ���
	void LoadCSV(std::string const& filename);

	//Phase���̎擾
	int GetPhaseNum()const { return mPhaseNum; }

	//�g�p�\���z�̎擾
	int GetUsePriceNum()const { return mUsePriceNum; }


	//�N���A���̃{�[�i�X�X�R�A�̎擾
	int GetClearBonusScoreNum() const { return mClearBonusScoreNum; }
};
