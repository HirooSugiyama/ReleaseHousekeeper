/*
�v���C�V�[�����烊�U���g�V�[���֏���n�����߂̃C���^�[�t�F�[�X
*/

#include"pch.h"
#include"PtoRSceneInterface.h"

//�O���ŏ�����
PtoRSceneInterface* PtoRSceneInterface::sPtoRIF = nullptr;

/*================
�R���X�g���N�^
================*/
PtoRSceneInterface::PtoRSceneInterface()
{
}


/*========================
�C���X�^���X�̎擾
�Ԃ�l�F���g�̃C���X�^���X
==========================*/
PtoRSceneInterface& PtoRSceneInterface::GetPtoRIFInstance()
{
	if (sPtoRIF == nullptr)
	{
		sPtoRIF = new PtoRSceneInterface();
	}
	return *sPtoRIF;
}
