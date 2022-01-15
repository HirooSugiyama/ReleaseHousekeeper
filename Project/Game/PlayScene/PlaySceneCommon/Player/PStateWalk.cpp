/*
�v���C���[�̏�ԕ����X�e�[�g�p�^�[���F�ړ����
�쐬���F2021/06/15
*/
#include"pch.h"

#include "PStateWalk.h"

//�Ԃ�l����̊֐��̎擾�Ŏg�p�B
#include"../ObjectModel/BoxModel.h"
#include"../../PlaySceneDefence/PreparingBlock.h"

//�ړ����x�̎擾�Ɏg�p
#include"../ObjectMove.h"

//�����Œ�`����B
const float MoveSpeed::MOVE_VELOCITY_X = 0.18f;
const float MoveSpeed::MOVE_VELOCITY_Y = 0.18f;
const float MoveSpeed::MOVE_VELOCITY_Z = 0.18f;


//�u���b�N�͈̔�
const float PStateWalk::MAX_POSITION_X = 19.f;
const float PStateWalk::MAX_POSITION_Z = 11.f;
const float PStateWalk::MIN_POSITION_Z = -40.f;

//�X�v���C�g�̐�
const int PStateWalk::WALKPLAYER_SPRITE_NUM = 5;

//�X�v���C�g�̃T�C�N��(���̎��Ԏ����ŃX�v���C�g�����)
const int PStateWalk::WALKPLAYER_SPRITE_CYCLE = 4;


//�v���C���[�̈ړ���(X)
const float PStateWalk::PLAYER_MOVE_VELOCITY_X = MoveSpeed::MOVE_VELOCITY_X;
//�v���C���[�̈ړ���(Y)					
const float PStateWalk::PLAYER_MOVE_VELOCITY_Y = MoveSpeed::MOVE_VELOCITY_Y;
//�v���C���[�̈ړ���(Z)					 
const float PStateWalk::PLAYER_MOVE_VELOCITY_Z = MoveSpeed::MOVE_VELOCITY_Z;


//�ړ��ʂ̑�����
const float PStateWalk::PLAYER_MOVE_INCREASE_VELOCITY=0.005f;

//��
const int PStateWalk::PLAYER_CHARACTER_ANGLE_L = 90;
//�E	
const int PStateWalk::PLAYER_CHARACTER_ANGLE_R = -90;
//��	
const int PStateWalk::PLAYER_CHARACTER_ANGLE_U = 0;
//��	
const int PStateWalk::PLAYER_CHARACTER_ANGLE_D = 180;
//����
const int PStateWalk::PLAYER_CHARACTER_ANGLE_LU = 45;
//�E��
const int PStateWalk::PLAYER_CHARACTER_ANGLE_RU = -PLAYER_CHARACTER_ANGLE_LU;
//����
const int PStateWalk::PLAYER_CHARACTER_ANGLE_LD = 135;
//�E��
const int PStateWalk::PLAYER_CHARACTER_ANGLE_RD = -PLAYER_CHARACTER_ANGLE_LD;




/*========================
�R���X�g���N�^
=========================*/
PStateWalk::PStateWalk()
	:
	PlayerStateBase(),
	mpPlayer(nullptr),
	mpWalkSpriteModel(),
	mActualPlayerVelocityX(0.0f),
	mActualPlayerVelocityY(0.0f),
	mActualPlayerVelocityZ(0.0f),
	mpDestinationPlayerCollider(),
	mGroundObjectHitFlag(false),
	mBlockHitFlag(false)
{
	mpWalkSpriteModel = std::make_unique<ObjectSpriteModel>(WALKPLAYER_SPRITE_NUM);

	mpDestinationPlayerCollider = std::make_unique<AABB>();

	//���f���ݒ菈��
	this->SetSpriteModel();
}

/*=========================
����������
�����F�v���C���[�̃|�C���^
=========================*/
void PStateWalk::Initialize(Player* pPlayer)
{
	mpPlayer = pPlayer;

	//�X�v���C�g���f���̎����̎w��
	mpWalkSpriteModel->SetConstTimer(WALKPLAYER_SPRITE_CYCLE);
}
/*=========================
�X�V����
=========================*/
void PStateWalk::Update()
{
	if (mpPlayer->GetPlayerState() != ePlayerState::WALK)
	{
		mpPlayer->SetState(ePlayerState::WALK);
	}

	//�X�v���C�g�̃^�C�~���O�Ń��f���������ւ��鏈��
	this->ReplacementSpriteModel();
	//�ړ��ʑ�������
	this->ConstantAcceleration();

	//�ړ��ł��邩���f����
	this->AllObjectHit();

}

/*=========================
�`�揈��
=========================*/
void PStateWalk::Draw()
{
	//�X�v���C�g���f���̏��ݒ�
	this->SetSpriteModelPosition();


	mpWalkSpriteModel->Draw();
}

/*=====================================
�ړ��x�N�g�����Z�o��ݒ肷��
�Ԃ�l�F�ړ��x�N�g��
======================================*/
DirectX::SimpleMath::Vector3 PStateWalk::CalculationMoveVelocity()
{
	//�Ԃ�l�p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 returnpos = DirectX::SimpleMath::Vector3::Zero;

	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	bool side = false;
	bool whith = false;

	if (pKey->WalkForward()|| pGamePad->MoveUp())	//�L�[���͂��s��ꂽ��
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().z >= MIN_POSITION_Z)
		{
			returnpos.z = -mActualPlayerVelocityZ;
			whith = true;
		}
	}
	if (pKey->WalkLeft() || pGamePad->MoveLeft()) //�L�[���͂��s��ꂽ��
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().x >= -MAX_POSITION_X)
		{
			returnpos.x = -mActualPlayerVelocityX;
			side = true;
		}
	}
	if (pKey->WalkBack() || pGamePad->MoveDown())//�L�[���͂��s��ꂽ��
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().z < MAX_POSITION_Z)
		{
			returnpos.z = mActualPlayerVelocityZ;
			whith = true;
		}
	}
	if (pKey->WalkRight() || pGamePad->MoveRight())//�L�[���͂��s��ꂽ��
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().x <= MAX_POSITION_X)
		{
			returnpos.x = mActualPlayerVelocityX;
			side = true;
		}
	}

	//���������̏���(�R���g���[���[�͌����I�ɕs�\�Ȃ̂ŏ����͖���)
	//�o�����ւ̓��͈͂ړ���0�Ƃ���B
	if (pKey->WalkRight() && pKey->WalkLeft())
	{
		returnpos.x = 0;
	}


	if(pKey->WalkForward() && pKey->WalkBack())
	{
		returnpos.z = 0;
	}

	//�΂ߕ����̈ړ�����
	if (whith && side && returnpos.x != 0 || returnpos.z != 0)
	{

		//�΂߂Ɉړ�����ۂ͏c���Ƃ͒������قȂ�i���������j�̂ŁA����̒ǉ��̌v�Z�B
		//�x�N�g���̒������擾
		float vl = sqrtf((returnpos.x * returnpos.x) + (returnpos.z * returnpos.z));

		//�P�ʃx�N�g���i�������P�̃x�N�g���j���v�Z
		returnpos.x /= vl;
		returnpos.z /= vl;

		//�ړ��x�N�g����ړI�̑傫���i�ړ��ʁj�ɃX�P�[�����O
		returnpos.x *= mActualPlayerVelocityX;
		returnpos.z *= mActualPlayerVelocityZ;
	}

	return returnpos;
}


/*==================================================================
�ړ���̃v���C���[�̓����蔻���Ԃ�(�ړ��͂��Ȃ�)
===================================================================*/
AABB* PStateWalk::GetDestinationPlayerCollider()
{
	////�Z�o�p�����蔻��̐錾
	DirectX::SimpleMath::Vector3 modelpos, modelscale;
	
	//�v���C���[�̍��W��ۑ�
	modelpos = mpPlayer->GetPlayerModel()->GetPosition();
	
	//�v���C���[�̊g�嗦��ۑ�
	modelscale = mpPlayer->GetPlayerModel()->GetScale();
	
	//���݂̃L�[���͂ł̈ړ��ʂ��Z�o�p�ϐ��ɒǉ�
	modelpos += mpPlayer->GetStateWalk()->CalculationMoveVelocity();
	
	//�g�嗦�̔����̒l�𐶐�
	DirectX::SimpleMath::Vector3 halfsize = mpPlayer->GetPlayerModel()->ReturnHalfSize(modelscale);
	halfsize.y *= mpPlayer->GetPlayerColliderExtendY();
	
	//���͂����ƂɎ��̓����蔻����Z�o
	mpDestinationPlayerCollider->SetCollider(modelpos - halfsize, modelpos + halfsize);

	//�����蔻���Ԃ�
	return mpDestinationPlayerCollider.get();
}






/*=====================================
���f����ݒ肷��:private
======================================*/
void PStateWalk::SetSpriteModel()
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();

	std::string addfilekey= "none";
	std::string filekey= "none";

	for (int i = 0; i < WALKPLAYER_SPRITE_NUM; i++)
	{
		//�v�f����string�ϊ�
		addfilekey =std::to_string(i);
		//�L�[�̍쐬
		filekey = "Player" + addfilekey;
		//�L�[�����Ƀ��f�������擾
		auto model = pRM->GetCmoModel(filekey);
		mpWalkSpriteModel->SetSpriteModel(i, model);
	}
}

/*=====================================
State�J�n���̏���������:private
======================================*/
void PStateWalk::SetSpriteModelPosition()
{
	//�ȗ���
	DirectX::SimpleMath::Vector3 pos= DirectX::SimpleMath::Vector3::Zero, scale= DirectX::SimpleMath::Vector3::Zero;
	pos = mpPlayer->GetPlayerModel()->GetPosition();
	scale = mpPlayer->GetPlayerModel()->GetScale();


	mpWalkSpriteModel->SetPosition(pos);
	mpWalkSpriteModel->SetScale(scale);
	
	//�������蔻��͒ʏ탂�f���̕��ŏ���
}

/*==================================================================
�X�v���C�g�̃^�C�~���O�Ń��f���������ւ��鏈��:private
===================================================================*/
void PStateWalk::ReplacementSpriteModel()
{
	mpWalkSpriteModel->SpriteUpdate();
}

/*=====================================
�ړ��ʂ������x�I�ɑ���������:private
=======================================*/
void PStateWalk::ConstantAcceleration()
{
	//���������x���ő�l�ł͂Ȃ�������A�����x���������₷�B
	/*X*/
	if (mActualPlayerVelocityX < PLAYER_MOVE_VELOCITY_X)
	{
		mActualPlayerVelocityX += PLAYER_MOVE_INCREASE_VELOCITY;
	}
	/*Y*/
	if (mActualPlayerVelocityY < PLAYER_MOVE_VELOCITY_Y)
	{
		mActualPlayerVelocityY += PLAYER_MOVE_INCREASE_VELOCITY;
	}
	/*Z*/
	if (mActualPlayerVelocityZ < PLAYER_MOVE_VELOCITY_Z)
	{
		mActualPlayerVelocityZ += PLAYER_MOVE_INCREASE_VELOCITY;
	}


}

/*===========================================================================
�S�ẴI�u�W�F�N�g�ɓ������Ă��Ȃ��ꍇ�̂ݏ�����ʂ��֐�:private
============================================================================*/
void PStateWalk::AllObjectHit()
{
	//�ǂ̃I�u�W�F�N�g�Ƃ��������Ă��Ȃ�������
	if (mBlockHitFlag == false&&
		mGroundObjectHitFlag == false)
	{
		//�ړ�����
		this->Move();

		//�����蔻����X�V����
		mpPlayer->UpdateCollider();
	}
}

/*=====================================
�ړ�����:private
======================================*/
void PStateWalk::Move()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	DirectX::SimpleMath::Vector3 vel;
	int rot = -1;//Model�̌X��

	bool side = false;
	bool whith = false;

	if (pKey->WalkForward() || pGamePad->MoveUp())	//�L�[���͂��s��ꂽ��
	{		
		if (mpPlayer->GetPlayerModel()->GetPosition().z >= MIN_POSITION_Z)
		{
			vel.z = -mActualPlayerVelocityZ;
			rot = PLAYER_CHARACTER_ANGLE_U;
			whith = true;
		}
	}
	if (pKey->WalkLeft() || pGamePad->MoveLeft()) //�L�[���͂��s��ꂽ��
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().x >= -MAX_POSITION_X)
		{
			vel.x = -mActualPlayerVelocityX;
			rot = PLAYER_CHARACTER_ANGLE_L;
			side = true;
		}
	}
	if (pKey->WalkBack() || pGamePad->MoveDown())//�L�[���͂��s��ꂽ��
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().z < MAX_POSITION_Z)
		{
			vel.z = mActualPlayerVelocityZ;
			rot = PLAYER_CHARACTER_ANGLE_D;
			whith = true;
		}
	}
	if (pKey->WalkRight() || pGamePad->MoveRight())//�L�[���͂��s��ꂽ��
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().x <= MAX_POSITION_X)
		{
			vel.x = mActualPlayerVelocityX;
			rot = PLAYER_CHARACTER_ANGLE_R;
			side = true;
		}
	}

	//���������̏���(�R���g���[���[�͌����I�ɕs�\�Ȃ̂ŏ����͖���)
	//�o�����ւ̓��͈͂ړ���0�Ƃ���B
	if (pKey->WalkRight() && pKey->WalkLeft())
	{
		vel.x = 0;
	}


	if (pKey->WalkForward() && pKey->WalkBack())
	{
		vel.z = 0;
	}


	//�΂ߕ����̈ړ�����
	if (whith && side && vel.x != 0 || vel.z != 0)
	{

		//�΂߂Ɉړ�����ۂ͏c���Ƃ͒������قȂ�i���������j�̂ŁA����̒ǉ��̌v�Z�B
		//�x�N�g���̒������擾
		float vl = sqrtf((vel.x * vel.x) + (vel.z * vel.z));

		//�P�ʃx�N�g�����v�Z
		vel.x /= vl;
		vel.z /= vl;

		//�ړ��x�N�g����ړI�̑傫���i�ړ��ʁj�ɃX�P�[�����O
		vel.x *= mActualPlayerVelocityX;
		vel.z *= mActualPlayerVelocityZ;

		if (pKey->WalkForward() || pGamePad->MoveUp())	//�L�[���͂��s��ꂽ��
		{
			if (pKey->WalkLeft() || pGamePad->MoveLeft()) //�L�[���͂��s��ꂽ��
			{
				rot = PLAYER_CHARACTER_ANGLE_LU;
			}
			if (pKey->WalkRight() || pGamePad->MoveRight())//�L�[���͂��s��ꂽ��
			{
				rot = PLAYER_CHARACTER_ANGLE_RU;
			}
		}
		if (pKey->WalkBack() || pGamePad->MoveDown())//�L�[���͂��s��ꂽ��
		{
			if (pKey->WalkLeft() || pGamePad->MoveLeft()) //�L�[���͂��s��ꂽ��
			{
				rot = PLAYER_CHARACTER_ANGLE_LD;
			}
			if (pKey->WalkRight() || pGamePad->MoveRight())//�L�[���͂��s��ꂽ��
			{
				rot = PLAYER_CHARACTER_ANGLE_RD;
			}
		}
	}

	//X������������Y�����ɓ��͂���������
	if (vel.x != 0 || vel.z != 0) {
		mpPlayer->GetPlayerModel()->Move(vel);								//���f�����ړ�������B
		mpPlayer->GetPlayerModel()->SetRotationY(static_cast<float>(rot));	//�X����ύX������

		mpWalkSpriteModel->SetRotationY(static_cast<float>(rot));
		//degree�ɂ͊֐����ŕϊ�
	}

	//��؏������Ȃ������痧����Ԃֈڍs
	if (vel == DirectX::SimpleMath::Vector3::Zero) {
		mpPlayer->ChangeStateStand();

		//�����x�����ׂď���������
		this->AllActualPlayerVelocityInit();
	}
}

/*=====================================
�g�p��������x�����ׂď�����:private
======================================*/
void PStateWalk::AllActualPlayerVelocityInit()
{
	mActualPlayerVelocityX=0.f;
	mActualPlayerVelocityY=0.f;
	mActualPlayerVelocityZ=0.f;
}
