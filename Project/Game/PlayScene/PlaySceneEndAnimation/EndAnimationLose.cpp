/*
�I�����A�j���[�V��������
�����N���X

�쐬���F2021/11/10
*/
#include"pch.h"
#include "EndAnimationLose.h"

//�G�t�F�N�g�̎g�p
#include"../Effect/EffectManager.h"
#include"../Effect/EffectType.h"
#include"../Effect/Effect.h"

//�֐��̎g�p
#include"../PlaySceneCommon/Protecter.h"

//�T�E���h�֌W
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"


//���j�������W
const DirectX::SimpleMath::Vector3 EndAnimationLose::EXPLOSION_POSITION_FIRST(-10.f,8.f,20.f);

const DirectX::SimpleMath::Vector3 EndAnimationLose::EXPLOSION_POSITION_SECOND(10.f, 8.f, 20.f);
const DirectX::SimpleMath::Vector3 EndAnimationLose::EXPLOSION_POSITION_THIRD(0.f, 8.f, 20.f);
const DirectX::SimpleMath::Vector3 EndAnimationLose::EXPLOSION_POSITION_FORTH(0.f, 8.f, 20.f);

//�����T�C�Y
const DirectX::SimpleMath::Vector2 EndAnimationLose::EXPLOSION_SCALE_SMALL(3.f,3.f);
const DirectX::SimpleMath::Vector2 EndAnimationLose::EXPLOSION_SCALE_BIG(25.f,25.f);

//�J�����֌W
const DirectX::SimpleMath::Vector3 EndAnimationLose::ENDANIM_LOSE_CAMERA_TARGET(0.f, 0.f, 10.f);
const DirectX::SimpleMath::Vector3 EndAnimationLose::ENDANIM_LOSE_CAMERA_EYE(0.f, 65.5f, 10.5f);

//�J����Y�l�ő�l
const float EndAnimationLose::CAMERA_MAX_POSITION_Y = 65.f;

//�唚���̓r��
const int EndAnimationLose::EXPLOSION_FORTH_MIDDLE = 3;

//�ҋ@����
const int EndAnimationLose::WAIT_TIME = 3;

/*===================================
�R���X�g���N�^
===================================*/
EndAnimationLose::EndAnimationLose()
	:
	EndAnimationBase(),
	mState(eLoseAnimStep::NONE),
	mEffectAddress(nullptr),
	mpTimer(nullptr),
	mMiniTimer(0),
	mpProtecter(nullptr),
	mpLoseTexture(nullptr),
	mBGMID(Utility::EXCEPTION_NUM)
{
	mpTimer = std::make_unique<Timer>();
	mpLoseTexture = std::make_unique<ObjectTexture>();
}

/*===================================
�f�X�g���N�^
===================================*/
EndAnimationLose::~EndAnimationLose()
{
}

/*===================================
����������
===================================*/
void EndAnimationLose::Initialize()
{
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture=pRM->GetTexture("LoseTexture");

	mpTimer->SetMaxTime(WAIT_TIME);

	mpLoseTexture->SetTexture(texture);
	mpLoseTexture->Initialize();
}

/*===================================
�X�V����
�Ԃ�l�F�A�j���[�V�����I��
===================================*/
bool EndAnimationLose::Update()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	switch (mState)
	{
		case eLoseAnimStep::NONE:
		{
			mState = eLoseAnimStep::PREPARATION;
			break;
		}		
		case eLoseAnimStep::PREPARATION:
		{
			//�G�t�F�N�g�}�l�[�W���[�̎擾
			auto pEM = EffectManager::GetInstance();
			pEM->SetCameraPointer(EndAnimationBase::GetCamera());


			//�����_�ƃJ�����ʒu�𒲐�
			EndAnimationBase::GetCamera()->SetRefEyePosition(ENDANIM_LOSE_CAMERA_EYE);
			EndAnimationBase::GetCamera()->SetRefTargetPosition(ENDANIM_LOSE_CAMERA_TARGET);
			mState = eLoseAnimStep::ROTATION_ANGLE;
			break;
		}
		case eLoseAnimStep::ROTATION_ANGLE:
		{
			EndAnimationBase::GetCamera()->Update();

			if (EndAnimationBase::GetCamera()->GetEyePosition().y > CAMERA_MAX_POSITION_Y)
			{
				//�G�t�F�N�g��ݒ肷��
				this->SetEffect(EXPLOSION_POSITION_FIRST, EXPLOSION_SCALE_SMALL);

				mState = eLoseAnimStep::FIRST_EXPLOSION;
			}
			break;
		}
		case eLoseAnimStep::FIRST_EXPLOSION:
		{

			//�G�t�F�N�g���I��������
			if (!*mEffectAddress)
			{
				//�G�t�F�N�g��ݒ肷��
				this->SetEffect(EXPLOSION_POSITION_SECOND, EXPLOSION_SCALE_SMALL);

				mState = eLoseAnimStep::SECOND_EXPLOSION;
			}
			break;
		}
		case eLoseAnimStep::SECOND_EXPLOSION:
		{
			if (!*mEffectAddress)
			{
				//�G�t�F�N�g��ݒ肷��
				this->SetEffect(EXPLOSION_POSITION_THIRD, EXPLOSION_SCALE_SMALL);

				mState = eLoseAnimStep::THIRD_EXPLOSION;
			}
			break;
		}
		case eLoseAnimStep::THIRD_EXPLOSION:
		{
			if (!*mEffectAddress)
			{
				//�G�t�F�N�g��ݒ肷��
				this->SetEffect(EXPLOSION_POSITION_FORTH, EXPLOSION_SCALE_BIG);

				mState = eLoseAnimStep::FORTH_EXPLOSION;
			}
			break;
		}
		case eLoseAnimStep::FORTH_EXPLOSION:
		{
			mMiniTimer++;

			if (mMiniTimer == EXPLOSION_FORTH_MIDDLE)
			{
				mpProtecter->ChangeOldHouse();
			}

			if (!*mEffectAddress)
			{
				
				mState = eLoseAnimStep::END;
			}
			break;
		}
		case eLoseAnimStep::END:
		{
			mpTimer->Update();
			if (mpTimer->GetMaxTime() == mpTimer->GetMainTimer())
			{
				//���y�𗬂�
				mBGMID=ADX2::GetInstance().Play(CRI_CUESHEET_0_BGM_LOSE);

				mState = eLoseAnimStep::LOSE_TEXTURE;
			}

			break;
		}
		case eLoseAnimStep::LOSE_TEXTURE:
		{
			//����{�^���������ꂽ��ړ�����
			if (pKey->Decision()|| pGamePad->Decision())
			{
				ADX2::GetInstance().Stop(mBGMID);
				return true;
			}

			break;
		}
		default:
		{
			break;
		}
	}


	return false;
}

/*===================================
�`�揈��
===================================*/
void EndAnimationLose::Draw()
{
	//�G�t�F�N�g�̕`�揈��
	EffectManager* pEM = EffectManager::GetInstance();
	pEM->Draw();

	//�����摜�`��̒i�K�̏ꍇ�̂ݕ`�悷��
	if (mState == eLoseAnimStep::LOSE_TEXTURE)
	{
		mpLoseTexture->Draw();
	}
}

/*==============================================================
�G�t�F�N�g��ݒ肷��:private
�����F�G�t�F�N�g�𔭐���������W�A�G�t�F�N�g�摜�̊g�嗦
================================================================*/
void EndAnimationLose::SetEffect(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector2 scale)
{
	//�G�t�F�N�g�}�l�[�W���[�̎擾
	auto pEM = EffectManager::GetInstance();

	auto effect = pEM->GetEffect(eEffectType::BOMB);
	effect->SetPosition(pos);
	effect->SetScale(scale);
	effect->SetSpriteFlag(true);
	effect->SetLoopFlag(false);
	mEffectAddress = effect->GetSpriteFlagAddress();
}
