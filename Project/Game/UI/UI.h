/*
���[�U�[�C���^�[�t�F�[�X
(�w�肳�ꂽ�Ƃ���Ɏw�肳�ꂽ���̂�`�悷��N���X)
�쐬���F2021/06/23
*/
#pragma once



//���݂̃t�F�[�Y�擾�Ɏg�p
#include"../PlayScene/PlayScenePhase/PlayScenePhase.h"

//�񋓌^�̎g�p
#include"../PlayScene/PlaySceneCommon/Player/PlayerActionState.h"
#include"../PlayScene/PlaySceneCommon/Weapon/WeaponeType.h"


//�O���錾
//����
#include"ScoreRender.h"
#include"DefeatEnemyRender.h"
#include"TimeOfDay.h"
#include"MoneyTexture.h"
#include"PhaseCursorManager.h"
#include"RedAssert.h"
#include"PlayerActionInfo.h"
#include"../Common/SpriteNumber/FloatNumber2D.h"

//�|�C���^�̕ۑ�
class Timer;
class Protecter;
class Player;

//����
class CameraBase;
class DirectXtkIF;


class UI
{
private:
	//�G���`��ʒu
	static const DirectX::SimpleMath::Vector2 STRING_ENEMY_NUM_POSITION;
	//�����������G�t�F�N�g�̈ʒu
	static const DirectX::SimpleMath::Vector2 MONEY_EFFECT_POSITION;


	//���݂̃t�F�[�Y�ƃt�F�[�Y�̎c�莞�Ԃ�\��
	std::unique_ptr<TimeOfDay> mpTimeOfDay;
	//�������̉��n�̉摜��`��
	std::unique_ptr<MoneyTexture> mpMoneyTexture;
	//�t�F�[�Y�̃J�[�\����`��
	std::unique_ptr<PhaseCursorManager> mpPhaseCursorManager;
	//�댯�M���\��
	std::unique_ptr<RedAssert> mpRedAssert;
	//�v���C���[�̌��݂̏��
	std::unique_ptr<PlayerActionInfo> mpPlayerActionInfo;
	
	//�����������G�t�F�N�g
	std::unique_ptr<FloatNumber2D> mpDecreaseMoney;

	//�X�R�A����̕`��
	std::unique_ptr<ScoreRender> mpScoreRender;

	//�c��G���̕`��
	std::unique_ptr<DefeatEnemyRender> mpDefeatEnemyRender;


	//�|�C���^�ۑ��p
	Timer* mpTimer;
	Protecter* mpProtecter;
	Player* mpPlayer;

	//�����N���X�֓n�����߂̈ꎞ�I�ȕۑ��p�ϐ�
	int* mpPhaseCountNum;
	ePlayScenePhase* mpPhase;
	int mInitHP;
	//�ő�t�F�[�Y��
	int mMaxPhaseNum;

	//�`�悷��X�R�A�̒l
	int mScoreNum;

	//�S�Ă̓G�̐�
	int mAllEnemyNum;
	//�c���Ă���G�̐�
	int mRemainingEnemyNum;

public:
	//�R���X�g���N�^
	UI();
	//�f�X�g���N�^
	~UI();


	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//UI�`��ɕK�v�ȏ����擾����
	void SetTimerPointer(Timer* pTimer);
	void SetPlayerPointer(Player* pPlayer);
	void SetProtecterPointer(Protecter* pProtecter);
	void SetPhaseCountPointer(int* pPhaseCount);
	void SetPhase(ePlayScenePhase* phase);
	void SetInitHP(int const& pHP);
	void SetMaxPhaseNum(int const& phasenum);

	void SetScoreNum(int const& score);
	void SetAllEnemyNum(int const& enemynum);
	void SetRemainingEnemyNum(int const& enemynum);

	//�댯�M���𑀍삷��֐�
	void RedAssertControl(bool const& flag);

	//�`�悷��摜��ς���֐�
	void ChangeActionInfoTexture(ePlayerActionState const& state);
	void ChangeActionInfoTexture(eWeaponType const& type);
	//���݂̕���̒e�����擾����֐�
	void SetActionInfoStrongBulletNum(int const& num);

	//��������`�悷��֐�
	void DrawMoneyTexture();

	//�����������G�t�F�N�g���쐬����
	void CreateMoneyEffect(int const& moneynum);

};
