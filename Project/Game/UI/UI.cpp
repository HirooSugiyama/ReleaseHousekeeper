/*
���[�U�[�C���^�[�t�F�[�X
(�w�肳�ꂽ�Ƃ���Ɏw�肳�ꂽ���̂�`�悷��N���X)
�쐬���F2021/06/23
*/

#include"pch.h"
#include"UI.h"

//�|�C���^�̕ۑ��p
#include"../PlayScene/PlaySceneCommon/Administrator/Timer.h"
#include"../PlayScene/PlaySceneCommon/Protecter.h"


//�G���`��ʒu
const DirectX::SimpleMath::Vector2 UI::STRING_ENEMY_NUM_POSITION(20.f, 80.f);

//�����������G�t�F�N�g�̈ʒu
const DirectX::SimpleMath::Vector2 UI::MONEY_EFFECT_POSITION(1000.f,100.f);

/*==============
�R���X�g���N�^
==============*/
UI::UI()
	:
	mpTimeOfDay(),
	mpMoneyTexture(),
	mpPhaseCursorManager(),
	mpRedAssert(),
	mpPlayerActionInfo(),
	mpDecreaseMoney(),
	mpScoreRender(),
	mpDefeatEnemyRender(),
	mpTimer(),
	mpProtecter(),
	mpPlayer(),
	mpPhaseCountNum(),
	mpPhase(),
	mInitHP(),
	mMaxPhaseNum(),
	mScoreNum(),
	mAllEnemyNum(),
	mRemainingEnemyNum()
{
	//���I�m��
	mpTimeOfDay = std::make_unique<TimeOfDay>();
	mpMoneyTexture = std::make_unique<MoneyTexture>();
	mpPhaseCursorManager = std::make_unique<PhaseCursorManager>();
	mpRedAssert = std::make_unique<RedAssert>();
	mpPlayerActionInfo = std::make_unique<PlayerActionInfo>();
	mpDecreaseMoney = std::make_unique<FloatNumber2D>();
	mpScoreRender = std::make_unique<ScoreRender>();
	mpDefeatEnemyRender = std::make_unique<DefeatEnemyRender>();

}
/*==============
�f�X�g���N�^
==============*/	
UI::~UI()
{
}


/*========================
������
�����F�J�����̃|�C���^
==========================*/
void UI::Initialize()
{
	//�t�F�[�Y�֌W�̉摜�̏����ݒ�
	mpTimeOfDay->Initialize(mpTimer, mMaxPhaseNum);

	//�������̉��n�摜�̏���������
	mpMoneyTexture->Initialize();

	//�t�F�[�Y�̃J�[�\���̏���������
	mpPhaseCursorManager->Initialize(mMaxPhaseNum);

	//�J�[�\���̍��W��ݒ肷��
	mpPhaseCursorManager->SetDrawPosition
	(
		mpTimeOfDay->GetIconStartPosition(),
		mpTimeOfDay->GetIconDistancePosition()
	);

	//�댯�M���̏���������
	mpRedAssert->Initialize();

	//�v���C���[�̌��݂̏�Ԃ̏���������
	mpPlayerActionInfo->Initialize();

	//�����������G�t�F�N�g�̃t�H���g���w��
	mpDecreaseMoney->SetTextureKey("DamageNumberFont");
	mpDecreaseMoney->Initialize();

	//�X�R�A����̕`��N���X�̏���������
	mpScoreRender->Initialize();

	//�c��G���̏���������
	mpDefeatEnemyRender->Initialize();
}

/*==============
�X�V����
==============*/
void UI::Update()
{
	//���݂�Phase���h�q�t�F�[�Y�̏ꍇ
	if (*mpPhase == ePlayScenePhase::DEFENCE)
	{
		//�t�F�[�Y�֌W�̉摜�̍X�V����
		mpTimeOfDay->Update();

		//�댯�M���̍X�V����
		mpRedAssert->Update();

		//�����������G�t�F�N�g�̍X�V����
		mpDecreaseMoney->Update();
	}
	//���݂�Phase���V���b�v�t�F�[�Y�̏ꍇ
	if (*mpPhase == ePlayScenePhase::WEAPON_SHOP)
	{
		//�����������G�t�F�N�g�̍X�V����
		mpDecreaseMoney->Update();
	}

}

/*==============
�`��
==============*/
void UI::Draw()
{

	//�v���C���[�̌��݂̏�Ԃ̕`�揈��
	mpPlayerActionInfo->Draw();
	
	//�댯�M���̕`�揈��
	mpRedAssert->Draw();
	
	//�t�F�[�Y�֌W�̉摜�̕`��
	mpTimeOfDay->Draw();
	
	//�t�F�[�Y�̃J�[�\���̕`�揈��
	mpPhaseCursorManager->Draw();
	
	//�������֌W�̕`��
	this->DrawMoneyTexture();
	
	//�X�R�A�̕`��
	mpScoreRender->Draw(mScoreNum);
	
	//�c��̓G�̐��̕`��
	mpDefeatEnemyRender->Draw(mRemainingEnemyNum, mAllEnemyNum);
}

/*============
�|�C���^�̕ۑ�
==============*/
//�����F�^�C�}�[�̃|�C���^
void UI::SetTimerPointer(Timer* pTimer)
{
	mpTimer = pTimer;
}

//�����F�v���C���[�̃|�C���^
void UI::SetPlayerPointer(Player* pPlayer)
{
	mpPlayer = pPlayer;
}

//�����F���_�̃|�C���^
void UI::SetProtecterPointer(Protecter* pProtecter)
{
	mpProtecter = pProtecter;
}

//�����F�t�F�[�Y�J�E���g���̃|�C���^
void UI::SetPhaseCountPointer(int* pPhaseCount)
{
	mpPhaseCountNum = pPhaseCount;
}

//�����F���݂̃t�F�[�Y�̃|�C���^
void UI::SetPhase(ePlayScenePhase* phase)
{
	mpPhase = phase;
}

//�����F����HP
void UI::SetInitHP(int const& pHP)
{
	mInitHP = pHP;
}

//�����F�ő�Phase��
void UI::SetMaxPhaseNum(int const& phasenum)
{
	mMaxPhaseNum = phasenum;
}

//�����F�X�R�A�l
void UI::SetScoreNum(int const& phasenum)
{
	mScoreNum = phasenum;
}
//�����F�S�Ă̓G�̐�
void UI::SetAllEnemyNum(int const& phasenum)
{
	mAllEnemyNum = phasenum;
}
//�����F�|�����G�̐�
void UI::SetRemainingEnemyNum(int const& phasenum)
{
	mRemainingEnemyNum = phasenum;
}


/*==========================
�댯�M���𑀍삷��֐�
==========================*/
void UI::RedAssertControl(bool const& flag)
{
	mpRedAssert->SetPassFlag(flag);
}

/*========================
�`�悷��摜��ς���֐�
==========================*/
void UI::ChangeActionInfoTexture(ePlayerActionState const& state)
{
	mpPlayerActionInfo->SetPlayerActionState(state);
}

void UI::ChangeActionInfoTexture(eWeaponType const& type)
{
	mpPlayerActionInfo->SetPlayerWeaponType(type);
}

/*==============================
���݂̕���̒e�����擾����֐�
================================*/
void UI::SetActionInfoStrongBulletNum(int const& num)
{
	mpPlayerActionInfo->StrongWeaponBulletNum(num);
}

/*==============================
��������`�悷��֐�
================================*/
void UI::DrawMoneyTexture()
{
	//�������̕`��
	mpMoneyTexture->Draw();

	//�����������G�t�F�N�g�̕`��
	mpDecreaseMoney->Draw();
}

/*============================================
�����������G�t�F�N�g���쐬����
==============================================*/
void UI::CreateMoneyEffect(int const& moneynum)
{
	mpDecreaseMoney->Reset();

	mpDecreaseMoney->Create(moneynum, MONEY_EFFECT_POSITION);
}
