/*
�c��t�F�[�Y���v������摜���Ǘ�����N���X
*/
#include"pch.h"
#include"PhaseCount.h"

//�O���錾
//����
#include"../Common/ObjectTexture.h"
#include "Game/Manager/ResourceManager.h"


//debug
#include"Game/Interface/DirectXTKInterface/DirectXTKInterface.h"
#include<SpriteFont.h>

using namespace DirectX::SimpleMath;


//���W
const DirectX::SimpleMath::Vector2
	PhaseCount::UI_PHAZECOUNT_POS = Vector2(0.f, 150.f);
//�g�嗦
const DirectX::SimpleMath::Vector2
	PhaseCount::UI_PHAZECOUNT_SCALE = Vector2(1.f, 1.f);


/*==============
�R���X�g���N�^
==============*/
PhaseCount::PhaseCount()
	:mpPhaseCountGroundwork()
	, mpPhaseNum(0)
{
	mpPhaseCountGroundwork = std::make_unique<ObjectTexture>();
}

/*==============
�f�X�g���N�^
==============*/
PhaseCount::~PhaseCount()
{
}

/*============================
����������
�����F�t�F�[�Y���̃|�C���^
============================*/
void PhaseCount::Initialize(int* pPhaseCountNum)
{
	//�|�C���^�̕ۑ�
	mpPhaseNum = pPhaseCountNum;

	//1��ނ����Ȃ����߂��ׂĂ����ōs��
	//���\�[�X�}�l�[�W���[�̎擾
	auto pRM = ResourceManager::GetInstance();

	//�摜�̐ݒ�
	auto texture = pRM->GetTexture("WoodMat");
	mpPhaseCountGroundwork->SetTexture(texture);
	//���W�̐ݒ�
	mpPhaseCountGroundwork->SetPos(UI_PHAZECOUNT_POS);
	//�g�嗦�̐ݒ�
	mpPhaseCountGroundwork->SetScale(UI_PHAZECOUNT_SCALE);

	mpPhaseCountGroundwork->Initialize();
}

/*==============
�`�揈��
==============*/
void PhaseCount::Draw()
{
	//mpPhaseCountGroundwork->Draw();

	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();

	wchar_t buf[32];
	swprintf_s(buf, 32, L"Phase = %d", *mpPhaseNum);
	//�`��J�n
	pDxIF.GetSpriteFont()->DrawString
	(pDxIF.GetSpriteBatch(), buf, DirectX::XMFLOAT2(UI_PHAZECOUNT_POS)); 


}
