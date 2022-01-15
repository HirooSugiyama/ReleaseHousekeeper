/*
�J��������t�F�[�Y
�쐬���F2021/10/11
*/

#include"pch.h"

#include"PScenePhaseEndAnimation.h"


//������
#include"../PlayScene.h"

//�֐��̎g�p
#include"../PlaySceneCommon/Player/Player.h"
#include"../PlaySceneCommon/ObjectModel/BoxModel.h"



/*=====================
�R���X�g���N�^
=====================*/
PScenePhaseEndAnimation::PScenePhaseEndAnimation()
	:
	PlayScenePhaseBase(),
	mpPlayScene(nullptr),
	mUseAnim(eUseEndAnim::NONE),
	mpWinAnim(nullptr),
	mpLoseAnim(nullptr)
{
	//�g�p���Ȃ��\�������邽�߂��ł��폜�ł���悤��
	mpLoseAnim = std::make_unique< EndAnimationLose>();
	mpWinAnim = std::make_unique<EndAnimationWin>();
}

/*=====================
�f�X�g���N�^
=====================*/
PScenePhaseEndAnimation::~PScenePhaseEndAnimation()
{
}

/*===================
����������
=====================*/
void PScenePhaseEndAnimation::Initialize(PlayScene* pPlayScene)
{
	//�|�C���^�̕ۑ�
	mpPlayScene = pPlayScene;

	
	mpWinAnim->SetPointer
	(
		PlayScenePhaseBase::GetEnemyManager(),
		PlayScenePhaseBase::GetAdministrator()
	);
}

/*=====================
�X�V����
=====================*/
void PScenePhaseEndAnimation::Update()
{
	bool endJuge = false;

	
	
	//�A�j���[�V������ݒ肷��
	switch (mUseAnim)
	{
		case eUseEndAnim::NONE:
		{

			break;
		}
		case eUseEndAnim::LOSE:
		{
			endJuge = mpLoseAnim->Update();

			if (endJuge)
			{
				//�X�e�[�W�I���V�[����
				mpPlayScene->SetClearFlag(true);
			}


			if (mpLoseAnim->GetState()==eLoseAnimStep::END)
			{
				mpPlayScene->StopBGM();
			}

			
			break;
		}
		case eUseEndAnim::WIN_TIME:	//NoBreak
		case eUseEndAnim::WIN_EXTERM:
		{
			//���U���g�t�F�[�Y��
			endJuge = mpWinAnim->Update();

			if (endJuge)
			{
				mpPlayScene->ChangePhaseToResult();
			}

			break;
		}
	}
}

/*====================
�`�揈��
=====================*/
void PScenePhaseEndAnimation::Draw()
{
	switch (mUseAnim)
	{
		case eUseEndAnim::NONE:
		{

			break;
		}
		case eUseEndAnim::LOSE:
		{
			mpLoseAnim->Draw();

			break;
		}
		case eUseEndAnim::WIN_TIME:	//NoBreak
		case eUseEndAnim::WIN_EXTERM:
		{
			mpWinAnim->Draw();
			break;
		}
	}
}

/*====================
���Z�b�g����
=====================*/
void PScenePhaseEndAnimation::Reset()
{

	switch (mUseAnim)
	{
		case eUseEndAnim::NONE:
		{

			break;
		}
		case eUseEndAnim::LOSE:
		{
			mpLoseAnim->Initialize();
			mpLoseAnim->SetProtecterPointer(PlayScenePhaseBase::GetProtecter());

			break;
		}
		case eUseEndAnim::WIN_TIME:	//NoBreak
		case eUseEndAnim::WIN_EXTERM:
		{
			mpWinAnim->Initialize();

			break;
		}
	}

}