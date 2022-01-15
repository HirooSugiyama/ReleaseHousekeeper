/*
�I�����A�j���[�V��������
�����N���X

�쐬���F2021/11/10
*/
#include"pch.h"
#include "EndAnimationWin.h"

//�G�t�F�N�g�̎g�p
#include"../Effect/EffectManager.h"

//�֐��̎g�p
#include"../PlaySceneCommon/Enemy/EnemyManager.h"
#include"../PlaySceneCommon/Administrator/Administrator.h"
#include"../PlaySceneCommon/Administrator/CelestialSphere.h"

//�J�����̃^�[�Q�b�g
const DirectX::SimpleMath::Vector3 EndAnimationWin::ENDANIM_WIN_CAMERA_TARGET(0.f, 0.f, -20.1f);

const DirectX::SimpleMath::Vector3 EndAnimationWin::ENDANIM_WIN_CAMERA_EYE(0.f, 65.5f, -20.f);

//�J����Z�l�ŏ��l
const float EndAnimationWin::CAMERA_MIN_POSITION_Z = -20.f;

/*===================================
�R���X�g���N�^
===================================*/
EndAnimationWin::EndAnimationWin()
	:
	EndAnimationBase(),
	mState(eWinAnimStep::NONE),
	mpTimer(nullptr),
	mpAdministrator(nullptr)
{
	mpTimer = std::make_unique<Timer>();
}

/*===================================
�f�X�g���N�^
===================================*/
EndAnimationWin::~EndAnimationWin()
{
}

/*==================================
����������
===================================*/
void EndAnimationWin::Initialize()
{
	mpTimer->SetMaxTime(1);
}

/*===================================
�X�V����
�Ԃ�l�F�A�j���[�V�����I��
===================================*/
bool EndAnimationWin::Update()
{
	switch (mState)
	{
		case eWinAnimStep::NONE:
		{
			mState = eWinAnimStep::PREPARATION;
			break;
		}
		case eWinAnimStep::PREPARATION:
		{
			//�G�t�F�N�g�}�l�[�W���[�̎擾
			auto pEM = EffectManager::GetInstance();
			pEM->SetCameraPointer(EndAnimationBase::GetCamera());

			//�����_�ƃJ�����ʒu�𒲐�
			EndAnimationBase::GetCamera()->SetRefTargetPosition(ENDANIM_WIN_CAMERA_TARGET);
			EndAnimationBase::GetCamera()->SetRefEyePosition(ENDANIM_WIN_CAMERA_EYE);

			mpAdministrator->DirectAcceserCelestialSphere()->ChangeSphereModelDay();

			mState = eWinAnimStep::SUNRISE;
			
			break;
		}
		case eWinAnimStep::SUNRISE:
		{
			mpTimer->Update();
			if (mpTimer->GetMaxTime() == mpTimer->GetMainTimer())
			{
				mState = eWinAnimStep::ROTATION_ANGLE1;
				
			}
			break;
		}
		case eWinAnimStep::ROTATION_ANGLE1:
		{
			EndAnimationBase::GetCamera()->Update();

			if (EndAnimationBase::GetCamera()->GetTargetPosition().z < CAMERA_MIN_POSITION_Z)
			{
				mState = eWinAnimStep::EXTERM_ENEMY;
			}
			break;
		}
		case eWinAnimStep::EXTERM_ENEMY:
		{
			//�G����Ĕ��j
			mpEnemyManager->ExplosionSimultaneousEnemy();

			//�G�t�F�N�g�̕`�揈��
			EffectManager* pEM = EffectManager::GetInstance();
			
			//�G�t�F�N�g���I��������
			if (!pEM->ChackAllEffect())
			{
				mState = eWinAnimStep::END;
			}
			break;
		}
		case eWinAnimStep::END:
		{

			return true;

			break;
		}
	}


	return false;
}

/*===================================
�`�揈��
===================================*/
void EndAnimationWin::Draw()
{
	//�G�t�F�N�g�̕`�揈��
	EffectManager* pEM = EffectManager::GetInstance();
	pEM->Draw();
}
