/*
�v���C���[�̒ʏ�U���A�j���[�V�������f�����Ǘ�����N���X
�쐬���F2021/09/05
*/
#include"pch.h"

#include"NormalAttackAnim.h"


//�萔
//Sin�l�g�嗦
const float NormalAttackAnim::SIN_SCLAE = 3.f;

//�A�j���[�V�����̑��x
const float NormalAttackAnim::ANIM_VELOCITY = 3.5f;
//�A�j���[�V�����̉����x
const float NormalAttackAnim::ANIM_ACCEL = 1.05f;

//�A�j���[�V�����ő�l
const float NormalAttackAnim::ANIM_MAX_NUM = 180.f;

/*================================
�R���X�g���N�^
================================*/
NormalAttackAnim::NormalAttackAnim()
	:
	mpAnimModel(nullptr),
	mSinNum(0.f),
	mVelocity(0.f),
	mWorld()
{
	mpAnimModel = std::make_unique<ObjectModel>();
}

/*================================
�f�X�g���N�^
================================*/
NormalAttackAnim::~NormalAttackAnim()
{
}

/*================================
����������
================================*/
void NormalAttackAnim::Initialize()
{

	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("Lance");

	mpAnimModel->SetModel(model);

	this->Reset();

	mpAnimModel->SetScale(DirectX::SimpleMath::Vector3::One);

	mVelocity = ANIM_VELOCITY;
}

/*================================
���Z�b�g����
================================*/
void NormalAttackAnim::Reset()
{
	mVelocity = ANIM_VELOCITY;
	mSinNum = 0.f;
}

/*=============================================================================
�X�V����
�����F�v���C���[�̍U���p���[���h���W
�Ԃ�l�F�A�j���[�V�����ғ��t���O(true:�I��)
=============================================================================*/
bool NormalAttackAnim::Update(DirectX::SimpleMath::Matrix const& playerAttackmat)
{

	//�l���擾
	float sinf = std::sinf(DirectX::XMConvertToRadians(mSinNum)) * SIN_SCLAE;

	//�l���X�V����
	mVelocity *= ANIM_ACCEL;
	mSinNum += mVelocity;

	//���[���h���W���v�Z����
	mWorld = (DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.f, 0.f, -sinf))) * playerAttackmat;
	

	//�ő�l�ƂȂ�����
	if (mSinNum >= ANIM_MAX_NUM)
	{
		return true;
	}

	return false;
}

/*==============================
�`�揈��
================================*/
void NormalAttackAnim::Draw()
{
	//�`��
	mpAnimModel->Draw(&mWorld);
}
