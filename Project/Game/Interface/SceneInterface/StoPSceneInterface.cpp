/*
�X�e�[�W�Z���N�g��ʂ���v���C�V�[���֏���n�����߂̃C���^�[�t�F�[�X
*/

#include"pch.h"
#include"StoPSceneInterface.h"


//�O���ŏ�����
StoPSceneInterface* StoPSceneInterface::sStoPIF = nullptr;


/*================
�R���X�g���N�^
================*/
StoPSceneInterface::StoPSceneInterface()
	:
	mCSVFileName("none"),
	mStageNumber("-1")
{
}


/*================================
�C���X�^���X�̎擾
�Ԃ�l�F���g�̃C���X�^���X
================================*/
StoPSceneInterface& StoPSceneInterface::GetStoPIFInstance()
{
	if (sStoPIF == nullptr)
	{
		sStoPIF = new StoPSceneInterface();
	}
	return *sStoPIF;
}
