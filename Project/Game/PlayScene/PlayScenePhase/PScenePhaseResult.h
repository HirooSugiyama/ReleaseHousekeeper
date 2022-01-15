/*
�J�E���g�_�E���t�F�[�Y
�쐬���F2021/09/30
*/
#pragma once

//���N���X
#include"PlayScenePhaseBase.h"

//�񋓌^�̎g�p
#include"../PlaySceneResult/ResultDrawString.h"

//�萔�̎g�p
#include"../PlaySceneResult/ResultDrawStringConstant.h"


#include"../PlaySceneResult/MoveSpriteNumber2D.h"

//����
#include"../../Common/ObjectTexture.h"
#include"../PlaySceneResult/MoveSpriteNumber2D.h"
#include"../PlaySceneResult/MoveString.h"
#include"../PlaySceneCommon/Administrator/Timer.h"
#include"../PlaySceneResult/ResultInfo.h"

class PScenePhaseResult :public PlayScenePhaseBase
{
private:

	//����ɍׂ�����ԕ���
	enum class eResultState
	{
		CONFIG,	//�l�ݒ菈��
		UPDATE,	//�X�V����
		END,	//�I������
	};

	enum class eMoveNumState
	{
		NONE,				//�ŏ�
		STRING_MOVE,		//���͂���ʊO���痬��Ă���
		BONUS_UP,			//BONUS�l���㏸
		SCORE_UP,			//�X�R�A�l���㏸
		SCORE_BLINKING,		//�����L���O�ɓ����Ă�����_��
		PUSH_ENTER,			//�G���^�[�L�[�������\����_��
		
	};

	//�኱�̃C���^�[�o��
	static const int SLIGHTLY_INTERVAL;

	//������������
	static const int NUM_MOVE_TIME;


	//�X�R�A�{�[�i�X�W��
	//������
	static const int MONEY_CAST_BONUS;
	//���j��
	static const int DEFFEAT_CAST_BONUS;

	//���U���g�摜�ړ����x
	static const int TEXTURE_MOVE_VELOCITY;


	//PlayScene�I�u�W�F�N�g�֕ۑ��p�̃|�C���^
	PlayScene* mpPlayScene;

	//�\�����ۑ��p�ϐ�
	//�e�핶��
	std::unique_ptr<MoveString> mpDrawString[static_cast<int>(eResultDrawString::NUM)];

	//���ʉ摜
	std::unique_ptr<ObjectTexture> mpCommonTexture;

	//�X�R�A
	int mScoreNum;
	std::unique_ptr<MoveSpriteNumber2D> mpScoreMoveNum;

	//������
	int mMoneyNum;
	std::unique_ptr<MoveSpriteNumber2D> mpMoneyMoveNum;

	//�S���j�{�[�i�X
	int mDeffeatBonusNum;
	std::unique_ptr<MoveSpriteNumber2D> mpDeffeatBonusMoveNum;

	//�N���A�{�[�i�X
	int mClearBonusNum;
	std::unique_ptr<MoveSpriteNumber2D> mpClearBonusMoveNum;

	//�����L���O�̃X�R�A
	int mScoreRankingNum[ResultDrawStringConstant::SCORE_RANKING_STORAGE];
	std::unique_ptr<MoveSpriteNumber2D> mpRanking[ResultDrawStringConstant::SCORE_RANKING_STORAGE];

	//�X�R�A�Ǘ�
	std::unique_ptr<ResultInfo> mpResultInfo;

	//��ԕ����ϐ��̎��ԉ�
	eResultState mState;
	eMoveNumState mNumState;

	//���Ԍv���p�^�C�}�[�ϐ�
	std::unique_ptr<Timer> mpTimer;

public:
	//�R���X�g���N�^
	PScenePhaseResult();

	//�f�X�g���N�^
	~PScenePhaseResult();
	
	//������
	void Initialize(PlayScene* pPlayScene)override;

	//�X�V
	void Update()override;

	//�`��
	void Draw()override;

private:

	//�l�̊e��ݒ�
	void Configuration();

	//�e��l�̕`�揈��
	void NumDraw();


	//�X�R�A���Z�o����
	void CalculationScore();

	//�l�������ړ�������
	void ForcedChange();


	//�摜�ړ�����
	bool MoveTexture();


};