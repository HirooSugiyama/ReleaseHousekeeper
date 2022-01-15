/*
�ЂƂ̃t�F�[�Y�̎n�܂�̃e�N�X�`�����Ǘ�����N���X
�쐬���F2021/09/18
*/
#include"pch.h"

#include"PhaseCursor.h"

//�O���錾
#include"../Common/ObjectTexture.h"


//�摜�̊g�嗦
const DirectX::SimpleMath::Vector2 PhaseCursor::PHASECURSOR_TEXTURE_SCALE(1.f,1.f);

/*===================================
�R���X�g���N�^
===================================*/
PhaseCursor::PhaseCursor()
	:
	mpPhaseCursorTexture()
{
	mpPhaseCursorTexture = std::make_unique<ObjectTexture>();
}

/*===================================
�f�X�g���N�^
===================================*/
PhaseCursor::~PhaseCursor()
{
}

/*=================================
����������
===================================*/
void PhaseCursor::Initialize()
{
	//���\�[�X�̎擾
	auto pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture("PhaseCursor");

	//�摜��ݒ肷��
	mpPhaseCursorTexture->SetTexture(texture);

	//����������
	mpPhaseCursorTexture->Initialize();
	mpPhaseCursorTexture->SetScale(PHASECURSOR_TEXTURE_SCALE);
}

/*===================================
�X�V����
===================================*/
void PhaseCursor::Update()
{

}

/*===================================
�`�揈��
===================================*/
void PhaseCursor::Draw()
{
	mpPhaseCursorTexture->Draw();
}

/*===================================
���W�̎擾
===================================*/
void PhaseCursor::SetPosition(DirectX::SimpleMath::Vector2 const& pos)
{
	mpPhaseCursorTexture->SetPosition(pos);
}




