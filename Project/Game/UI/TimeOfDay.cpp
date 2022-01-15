/*
�����t�F�[�Y(��)�Ɩh�q�t�F�[�Y(��)��UI���Ǘ�����N���X
*/
#include"pch.h"
#include "TimeOfDay.h"

//�O���錾
//�|�C���^�̕ۑ�
#include"../PlayScene/PlaySceneCommon/Administrator/Timer.h"

//�萔
//�i�ދ���
const float TimeOfDay::UI_TOD_ICON_DISTANCE = 1050.f;

//�Q�[�W�̊g�嗦
const DirectX::SimpleMath::Vector2 TimeOfDay::UI_TOD_GAUGE_SCALE(2.f, 2.2f);

//�A�C�R���̊g�嗦
const DirectX::SimpleMath::Vector2 TimeOfDay::UI_TOD_ICON_SCALE(0.8f, 0.8f);

//�Q�[�W�̍��W
const DirectX::SimpleMath::Vector2 TimeOfDay::UI_TOD_GAUGE_POSITION(120.f, 710.f);

//�A�C�R���̏������W
const DirectX::SimpleMath::Vector2 TimeOfDay::UI_TOD_ICON_POSITION(100.f, 700.f);

//�t���[�����Z
const float TimeOfDay::CAST_TO_FRAME_TO_SECOND = 60.f;

/*======================
�R���X�g���N�^
========================*/
TimeOfDay::TimeOfDay()
	:
	mpTODGauge(),
	mpTODIcon(),
	mpTimer(),
	mIconMoveVelocity()
{
	mpTODGauge = std::make_unique<ObjectTexture>();
	mpTODIcon = std::make_unique<ObjectTexture>();
}

/*======================
�f�X�g���N�^
========================*/
TimeOfDay::~TimeOfDay()
{
}

/*================================================
����������
�����F�^�C�}�[�̃|�C���^�A���݂̃t�F�[�Y�̃|�C���^
================================================*/
void TimeOfDay::Initialize(Timer* pTimer, int const& maxPhaseNum)
{

	mpTimer = pTimer;

	//�摜�̐ݒ�
	this->SetTexture();
	//���W�̐ݒ�
	this->SetPosition();
	//�g�嗦�̐ݒ�
	this->SetScale();

	mpTODGauge->Initialize();
	mpTODIcon->Initialize();


	mMaxGameTime = mpTimer->GetMaxTime() * maxPhaseNum;


	//���t���[���̑��x���Z�o
	mIconMoveVelocity = this->CalculationIconVelocity();
}

/*========================
�X�V����
========================*/
void TimeOfDay::Update()
{
	//���݂̍��W�ۑ��p�ϐ�
	DirectX::SimpleMath::Vector2 pos= DirectX::SimpleMath::Vector2::Zero;

	pos = mpTODIcon->GetPosition() + DirectX::SimpleMath::Vector2(mIconMoveVelocity, 0.f);

	mpTODIcon->SetPosition(pos);
}

/*========================
�`�揈��
========================*/
void TimeOfDay::Draw()
{
	//���n�̉摜��`��
	mpTODGauge->Draw();
	mpTODIcon->Draw();
}

/*========================
�摜�̐ݒ�:private
========================*/
void TimeOfDay::SetTexture()
{
	auto pRM = ResourceManager::GetInstance();

	auto texture = pRM->GetTexture("FazeGauge");
	mpTODGauge->SetTexture(texture);

	texture = pRM->GetTexture("MoonIcon");
	mpTODIcon->SetTexture(texture);
}

/*=======================
���W�̐ݒ�:private
========================*/
void TimeOfDay::SetPosition()
{
	//�Q�[�W�̍��W�ݒ�
	mpTODGauge->SetPosition(UI_TOD_GAUGE_POSITION);
	mpTODIcon->SetPosition(UI_TOD_ICON_POSITION);
}

/*========================
�g�嗦�̐ݒ�:private
========================*/
void TimeOfDay::SetScale()
{
	mpTODGauge->SetScale(UI_TOD_GAUGE_SCALE);
	mpTODIcon->SetScale(UI_TOD_ICON_SCALE);
}

/*==================================
�A�C�R�����i�ރX�s�[�h���Z�o:private
�����F�t�F�[�Y�̎���
�Ԃ�l�F���ۂɖ��t���[����������
==================================*/
float TimeOfDay::CalculationIconVelocity()
{
	//�Ԃ�l�ϐ��錾
	float velnum=0;

	//�i�ދ���/Phase�̎���=�i�ރX�s�[�h(1�b������)
	velnum = UI_TOD_ICON_DISTANCE / mMaxGameTime;
	
	//1�b������̐i�ރX�s�[�h�Ȃ̂ŁA�t���[�����Z����B
	velnum /= CAST_TO_FRAME_TO_SECOND;


	return velnum;
}
