/*
�t�F�[�Y���n�܂�^�C�~���O�������J�[�\���̕`����s���N���X
*/
#include"pch.h"

#include"PhaseCursorManager.h"


//�擾���W�̂��炷��
const float PhaseCursorManager::PHASECURSOR_SHIFT_POSITION = 30.f;


/*===================================
�R���X�g���N�^
===================================*/
PhaseCursorManager::PhaseCursorManager()
	:
	mpPhaseCursor()
{
}

/*===================================
�f�X�g���N�^
===================================*/
PhaseCursorManager::~PhaseCursorManager()
{
}

/*===================================
����������
�����F�ő�t�F�[�Y��
===================================*/
void PhaseCursorManager::Initialize(int const& phasemaxnum)
{
	mpPhaseCursor.resize(phasemaxnum);

	//��O�I�ɂ����œ��I�m�ۂ��s��
	for (int i = 0; i < phasemaxnum; i++)
	{
		mpPhaseCursor[i] = std::make_unique<PhaseCursor>();
	}

	for (int i = 0; i < static_cast<int>(mpPhaseCursor.size()); i++)
	{
		mpPhaseCursor[i]->Initialize();
	}
}


/*=================================
�`�揈��
===================================*/
void PhaseCursorManager::Draw()
{
	for (int i = 0; i < static_cast<int>(mpPhaseCursor.size()); i++)
	{
		mpPhaseCursor[i]->Draw();
	}
}

/*===================================
�`�悷����W�����߂�
�����F�`��J�n���W�A���炷��
===================================*/
void PhaseCursorManager::SetDrawPosition(DirectX::SimpleMath::Vector2 const& startpos, 
									float const& movepos)
{
	//���̊Ԋu���Z�o
	float intervel = movepos / static_cast<int>(mpPhaseCursor.size());
	DirectX::SimpleMath::Vector2 pos =
		startpos+ DirectX::SimpleMath::Vector2(PHASECURSOR_SHIFT_POSITION,0.f);

	for (int i = 0; i < static_cast<int>(mpPhaseCursor.size()); i++)
	{
		mpPhaseCursor[i]->SetPosition(pos);
		pos.x += intervel;
	}
}




