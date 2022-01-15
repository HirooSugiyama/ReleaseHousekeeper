/*
�n�ʏ�ɂ���I�u�W�F�N�g�𓝊�����N���X
�쐬���F2021/08/19
*/


#include"pch.h"
#include "GroundObjectManager.h"

//�O���錾
#include"../Enemy/EnemyManager.h"

//�֐��������g�p
#include"IGroundObject.h"
#include"../Player/Player.h"
#include"../ObjectModel/BoxModel.h"

#include"../Player/PStateWalk.h"

//CSV�t�@�C�����_�̍��W
const DirectX::SimpleMath::Vector2 GroundObjectManager::GOMANAGER_INIT_CSV_POSITION(-19.f, -40.f);
/*======================
�R���X�g���N�^
======================*/
GroundObjectManager::GroundObjectManager(std::string const& filepath)
	:
	mpConifer{},
	mConiferPosition(),
	mpConiferGroup{},
	mConiferGroupPosition(),
	mpMoveCar{},
	mMoveCarPosition(),
	mpShop{},
	mShopPosition(),
	mGroundObject(),
	mGroundObjectMapChip{},
	mSaveInfo{},
	mGroundObjectCollider{},
	mCorresColliderObject{},
	mPlayerShopTouchFlag(false)
{
	//�t�@�C���ǂݍ��ݏ���
	this->LoadMapChip(filepath);

	//�j�t���̔z�񐔂𒲐߂���
	this->AdjustmentConiferVector();
	//�����Ԃ̔z�񐔂𒲐߂���
	this->AdjustmentMoveCarVector();
	//�j�t���̔z�񐔂𒲐߂���
	this->AdjustmentConiferGroupVector();
	//�V���b�v�̔z�񐔂𒲐߂���
	this->AdjustmentShopVector();

	//CSV�t�@�C�����炠����x�̂܂Ƃ܂�̃I�u�W�F�N�g��T���o��
	this->SeekLoadMapChipCohesive();

	//�������Ƃɓ����蔻����쐬����
	this->CreateCollider();
}

/*======================
�f�X�g���N�^
======================*/
GroundObjectManager::~GroundObjectManager()
{
}

/*======================
������
======================*/
void GroundObjectManager::Initialize()
{
	//�j�t���̏���������
	for (int i = 0; i < static_cast<int>(mpConifer.size()); i++)
	{
		mpConifer[i]->Initialize();

		//���W��ݒ肷��
		this->ConfigConiferVectorPosition();
	}	
	//�����Ԃ̏���������
	for (int i = 0; i < static_cast<int>(mpMoveCar.size()); i++)
	{
		mpMoveCar[i]->Initialize();

		//���W��ݒ肷��
		this->ConfigMoveCarVectorPosition();
	}
	//�j�t���O���[�v�̏���������
	for (int i = 0; i < static_cast<int>(mpConiferGroup.size()); i++)
	{
		mpConiferGroup[i]->Initialize();

		//���W��ݒ肷��
		this->ConfigConiferGroupVectorPosition();
	}	
	//�V���b�v�̏���������
	for (int i = 0; i < static_cast<int>(mpShop.size()); i++)
	{
		mpShop[i]->Initialize();

		//���W��ݒ肷��
		this->ConfigShopVectorPosition();
	}	
}

/*======================
�X�V����
======================*/
void GroundObjectManager::Update()
{
	//�����Ԃ̍X�V����
	for (int i = 0; i < static_cast<int>(mpMoveCar.size()); i++)
	{
		mpMoveCar[i]->Update();
	}
}

/*====================
�`�揈��
======================*/
void GroundObjectManager::Draw()
{
	//�j�t���̕`�揈��
	for (int i = 0; i < static_cast<int>(mpConifer.size()); i++)
	{
		mpConifer[i]->Draw();
	}
	//�����Ԃ̕`�揈��
	for (int i = 0; i < static_cast<int>(mpMoveCar.size()); i++)
	{
		mpMoveCar[i]->Draw();
	}
	//�j�t���O���[�v�̕`�揈��
	for (int i = 0; i < static_cast<int>(mpConiferGroup.size()); i++)
	{
		mpConiferGroup[i]->Draw();
	}
	//�V���b�v�̕`�揈��
	for (int i = 0; i < static_cast<int>(mpShop.size()); i++)
	{
		mpShop[i]->Draw();
	}
}

/*======================================
�G�̓����蔻�����
�����F�t�@�C���̃p�X
======================================*/
void GroundObjectManager::RoolEnemyManagerChackHit(EnemyManager* pEnemyManager)
{
	//�����蔻��̐������J��Ԃ�
	for (int i = 0; i < static_cast<int>(mGroundObjectCollider.size()); i++)
	{
		pEnemyManager->ChackHitGroundObjectEnemy(&mGroundObjectCollider[i]);
	}
}

/*=====================================
�v���C���[�Ƃ̓����蔻�菈��
�����F�v���C���[�̃|�C���^
======================================*/
void GroundObjectManager::ChackHitPlayerGroundObject(Player* pPlayer)
{
	//����p�ϐ��̐錾
	bool hitflag = false;

	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//�����蔻��̐������s��
	for (int i = 0; i < static_cast<int>(mGroundObjectCollider.size()); i++)
	{	
		//�����������Ă����珈�����s��
		if (pC.Intersect(pPlayer->GetStateWalk()->GetDestinationPlayerCollider(),
			&mGroundObjectCollider[i]))
		{

			hitflag = true;

			//�����V���b�v�ɂԂ�������
			if (mCorresColliderObject[i] == eGroundObject::SHOP)
			{
				//�t���O�����Ă�
				mPlayerShopTouchFlag = true;
				//���C�v����
				ScreenTransitionInterface& pSTI = ScreenTransitionInterface::GetScreenTransitionInstance();
				pSTI.SetWipeUseFlag(true);
				pSTI.GetWipe()->SetClose();
			}
			else
			{
				//�n��I�u�W�F�N�g�Ƃ͓������Ă��邱�Ƃɂ���
				pPlayer->GetStateWalk()->SetGroundObjectHitFlag(true);
			}
		}
	}
	//�������݂̓��͂ňړ����Ă��Փ˂��Ȃ��Ȃ��
	if(hitflag==false)
	{
		//�n��I�u�W�F�N�g�Ƃ͓������Ă��Ȃ����Ƃɂ���
		pPlayer->GetStateWalk()->SetGroundObjectHitFlag(false);

		//�V���b�v�Ƃ��������ĂȂ����ƂƂ���
		mPlayerShopTouchFlag = false;
	}
}

/*======================================
�I�u�W�F�N�g�z�u�p��MapChip�ǂݍ���
�����F�t�@�C���̃p�X
======================================*/
void GroundObjectManager::LoadMapChip(std::string const& filepath)
{
	//�t�@�C���ϊ�
	std::ifstream ifs(filepath);
	//1�s�̏���ۑ�����ϐ�
	std::string lineBuf;

	//1�s�̓ǂݍ��ݏ���
	for (int i = 0; std::getline(ifs, lineBuf); i++)
	{
		//1�s�̏���stream�ɂ���
		std::stringstream lineStream(lineBuf);
		//1�}�X�̏��ۑ��p
		std::string tileBuf;
		//�ϊ��p�ϐ�
		DirectX::SimpleMath::Vector2 pos;

		//1�}�X�̏��ǂݍ��ݏ���
		for (int j = 0; std::getline(lineStream, tileBuf, ','); j++)
		{
			//�v�f���Ȃ�������
			if (atoi(tileBuf.c_str()) == static_cast<int>(eGroundObject::NONE))
			{
				continue;
			}

			//�ȉ��͗v�f������ꍇ�̂ݒʂ鏈��
			int tile = atoi(tileBuf.c_str());
			

			//�v�f��ۑ�
			mGroundObjectMapChip[j][i] = tile;

			//���W��ۑ�
			pos.x = static_cast<float>(j);
			pos.y = static_cast<float>(i);

			//���W�����[���h���W�ɕϊ�
			pos += GOMANAGER_INIT_CSV_POSITION;

			//�v�f�ɂ���ď�����ς���
			switch (tile)
			{
				case static_cast<int>(eGroundObject::CONIFER):
				{
					mConiferPosition.push_back(pos);

					//�m�ې��𑝂₷
					mGroundObject.mConiferNum++;

					break;
				}
				case static_cast<int>(eGroundObject::MOVE_CAR):
				{
					mMoveCarPosition.push_back(pos);

					//�m�ې��𑝂₷
					mGroundObject.mMoveCarNum++;

					break;
				}
				case static_cast<int>(eGroundObject::CONIFER_GROUP):
				{
					mConiferGroupPosition.push_back(pos);

					//�m�ې��𑝂₷
					mGroundObject.mConiferGroupNum++;

					break;
				}
				case static_cast<int>(eGroundObject::SHOP):
				{
					mShopPosition.push_back(pos);

					//�m�ې��𑝂₷
					mGroundObject.mShopNum++;

					break;
				}
			}
		}

	}
}

/*======================================
�j�t���̔z�񐔂𒲐߂���
======================================*/
void GroundObjectManager::AdjustmentConiferVector()
{
	//�\���̏������ƂɕK�v�ȕ������I�u�W�F�N�g����������
	mpConifer.resize(mGroundObject.mConiferNum);

	//�G�̃������m��
	for (int i = 0; i < static_cast<int>(mpConifer.size()); i++)
	{
		mpConifer[i] = std::make_unique<GroundObjectConifer>();
	}
}

/*======================================
�j�t���̍��W��ݒ肷��
======================================*/
void GroundObjectManager::ConfigConiferVectorPosition()
{
	//�ϊ��p�ϐ�
	DirectX::SimpleMath::Vector3 pos= DirectX::SimpleMath::Vector3::Zero;

	//�G�̃������m��
	for (int i = 0; i < static_cast<int>(mpConifer.size()); i++)
	{
		pos.x = mConiferPosition[i].x;
		pos.y = mpConifer[i]->GetConiferModelPositionY();
		pos.z = mConiferPosition[i].y;
		mpConifer[i]->
			SetConiferModelPosition(pos);
	}
}

/*======================================
�j�t���O���[�v�̔z�񐔂𒲐߂���
======================================*/
void GroundObjectManager::AdjustmentConiferGroupVector()
{
	//�\���̏������ƂɕK�v�ȕ������I�u�W�F�N�g����������
	mpConiferGroup.resize(mGroundObject.mConiferGroupNum);

	//�G�̃������m��
	for (int i = 0; i < static_cast<int>(mpConiferGroup.size()); i++)
	{
		mpConiferGroup[i] = std::make_unique<GroundObjectConiferGroup>();
	}
}

/*======================================
�j�t���̃O���[�v���W��ݒ肷��
======================================*/
void GroundObjectManager::ConfigConiferGroupVectorPosition()
{
	//�ϊ��p�ϐ�
	DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero;

	//�G�̃������m��
	for (int i = 0; i < static_cast<int>(mpConiferGroup.size()); i++)
	{
		pos.x = mConiferGroupPosition[i].x;
		pos.y = mpConiferGroup[i]->GetConiferModelPositionY();
		pos.z = mConiferGroupPosition[i].y;
		mpConiferGroup[i]->
			SetConiferModelPosition(pos);
	}
}

/*======================================
�����Ԃ̔z�񐔂𒲐߂���
======================================*/
void GroundObjectManager::AdjustmentMoveCarVector()
{
	//�\���̏������ƂɕK�v�ȕ������I�u�W�F�N�g����������
	mpMoveCar.resize(mGroundObject.mMoveCarNum);

	//�G�̃������m��
	for (int i = 0; i < static_cast<int>(mpMoveCar.size()); i++)
	{
		mpMoveCar[i] = std::make_unique<GroundObjectMoveCar>();
	}
}

/*====================================
�����Ԃ̍��W��ݒ肷��
======================================*/
void GroundObjectManager::ConfigMoveCarVectorPosition()
{
	//�ϊ��p�ϐ�
	DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero;

	//�G�̃������m��
	for (int i = 0; i < static_cast<int>(mpMoveCar.size()); i++)
	{
		pos.x = mMoveCarPosition[i].x;
		pos.y = mpMoveCar[i]->GetMoveCarModelPositionY();
		pos.z = mMoveCarPosition[i].y;
		mpMoveCar[i]->
			SetMoveCarModelPosition(pos);
	}
}

/*======================================
�V���b�v�̔z�񐔂𒲐߂���
======================================*/
void GroundObjectManager::AdjustmentShopVector()
{
	//�\���̏������ƂɕK�v�ȕ������I�u�W�F�N�g����������
	mpShop.resize(mGroundObject.mShopNum);

	//�G�̃������m��
	for (int i = 0; i < static_cast<int>(mpShop.size()); i++)
	{
		mpShop[i] = std::make_unique<GroundObjectShop>();
	}
}

/*====================================
�V���b�v�̍��W��ݒ肷��
======================================*/
void GroundObjectManager::ConfigShopVectorPosition()
{
	//�ϊ��p�ϐ�
	DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero;

	//�G�̃������m��
	for (int i = 0; i < static_cast<int>(mpShop.size()); i++)
	{
		pos.x = mShopPosition[i].x;
		pos.y = mpShop[i]->GetShopModelPositionY();
		pos.z = mShopPosition[i].y;
		mpShop[i]->SetShopModelPosition(pos);
	}
}

/*================================================================
CSV�t�@�C�����炠����x�̂܂Ƃ܂�̃I�u�W�F�N�g��T���o��:private
�����F�t�@�C���̃p�X
==================================================================*/
void GroundObjectManager::SeekLoadMapChipCohesive()
{
	mSaveInfo.clear();

	//�ꎞ�ۑ��p�\���̂����̉�
	SaveColliderInfo colliderInfo
		(eGroundObject::NONE, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2::Zero);

	//Y���̏���
	for (int y = 0; y < GOMANAGER_CSV_MAX_Y; y++)
	{
		//�ϊ��p�ϐ�
		int chipX = 0, chipY = 0;

		//X���̏���
		for (int x = 0; x < GOMANAGER_CSV_MAX_X; x++)
		{
			if (mGroundObjectMapChip[x][y] == static_cast<int>(eGroundObject::NONE))continue;
			if (mGroundObjectMapChip[x][y] == static_cast<int>(eGroundObject::CONIFER_GROUP))continue;
			if (this->OverlapCheck(x, y))continue;	//�d���`�F�b�N

			//�I�u�W�F�N�g����������ċA�J�n
			chipX = x;
			chipY = y;
			this->Search(chipX, chipY, mGroundObjectMapChip[x][y]);

			eGroundObject object(static_cast<eGroundObject>(mGroundObjectMapChip[x][y]));
			colliderInfo.mObjectType = object;


			colliderInfo.mMinPosition = 
				DirectX::SimpleMath::Vector2(static_cast<float>(x), static_cast<float>(y));
			colliderInfo.mMaxPosition = 
				DirectX::SimpleMath::Vector2(static_cast<float>(chipX), static_cast<float>(chipY));
			mSaveInfo.push_back(colliderInfo);
		}
	}
}

/*======================================
�������Ƃɓ����蔻����쐬����:private
=========================================*/
void GroundObjectManager::CreateCollider()
{
	int num = static_cast<int>(mSaveInfo.size());

	//���̐������e�ʂ𑝂₷
	mGroundObjectCollider.resize(num);
	mCorresColliderObject.resize(num);

	//�ȗ����ϐ��̐錾
	DirectX::SimpleMath::Vector3 basepos, minpos, maxpos, halfScale;


	//���̐������s��
	for (int i = 0; i < num; i++)
	{
		//�I�u�W�F�N�g�̎�ނɂ���ď�����ς���
		//�g�嗦�����Ƃɓ����蔻��p���W�����߂�
		switch (mSaveInfo[i].mObjectType)
		{
			case eGroundObject::CONIFER:
			{
				/*==================�ŏ��l���v�Z==================*/
				//�Z�o�������W+world���W�ϊ�
				basepos.x = mSaveInfo[i].mMinPosition.x+ GOMANAGER_INIT_CSV_POSITION.x;

				//���ʂ̍��W���g�p(��\����0�Ԗڂ̒萔���g�p)
				basepos.y = mpConifer[0]->GetConiferModelPositionY();

				//�Z�o�������W+world���W�ϊ�
				basepos.z = mSaveInfo[i].mMinPosition.y+ GOMANAGER_INIT_CSV_POSITION.y;

				//�g�嗦�̔������擾
				halfScale = mpConifer[0]->GetConiferScale() / static_cast<float>(Utility::SCALE_HALF);

				//�ŏ��l���Z�o
				minpos = basepos - halfScale;
				/*==================�����܂�=================*/

				/*==================�ő�l���v�Z==================*/
				//�Z�o�������W+world���W�ϊ�
				basepos.x = mSaveInfo[i].mMaxPosition.x + GOMANAGER_INIT_CSV_POSITION.x;

				//�Z�o�������W+world���W�ϊ�
				basepos.z = mSaveInfo[i].mMaxPosition.y + GOMANAGER_INIT_CSV_POSITION.y;

				//�ő�l���Z�o
				maxpos = basepos + halfScale;

				/*==================�����܂�=================*/

				break;
			}
			case eGroundObject::MOVE_CAR:
			{
				/*==================�ŏ��l���v�Z==================*/
				//�Z�o�������W+world���W�ϊ�
				basepos.x = mSaveInfo[i].mMinPosition.x + GOMANAGER_INIT_CSV_POSITION.x;

				//���ʂ̍��W���g�p(��\����0�Ԗڂ̒萔���g�p)
				basepos.y = mpMoveCar[0]->GetMoveCarModelPositionY();

				//�Z�o�������W+world���W�ϊ�
				basepos.z = mSaveInfo[i].mMinPosition.y + GOMANAGER_INIT_CSV_POSITION.y;

				//�g�嗦�̔������擾
				halfScale = mpMoveCar[0]->GetMoveCarScale() / static_cast<float>(Utility::SCALE_HALF);

				//�ŏ��l���Z�o
				minpos = basepos - halfScale;
				/*==================�����܂�=================*/

				/*==================�ő�l���v�Z==================*/
				//�Z�o�������W+world���W�ϊ�
				basepos.x = mSaveInfo[i].mMaxPosition.x + GOMANAGER_INIT_CSV_POSITION.x;

				//�Z�o�������W+world���W�ϊ�
				basepos.z = mSaveInfo[i].mMaxPosition.y + GOMANAGER_INIT_CSV_POSITION.y;

				//�ő�l���Z�o
				maxpos = basepos + halfScale;

				/*==================�����܂�=================*/

				break;
			}
			case eGroundObject::SHOP:
			{
				/*==================�ŏ��l���v�Z==================*/
				//�Z�o�������W+world���W�ϊ�
				basepos.x = mSaveInfo[i].mMinPosition.x + GOMANAGER_INIT_CSV_POSITION.x;

				//���ʂ̍��W���g�p(��\����0�Ԗڂ̒萔���g�p)
				basepos.y = mpShop[0]->GetShopModelPositionY();

				//�Z�o�������W+world���W�ϊ�
				basepos.z = mSaveInfo[i].mMinPosition.y + GOMANAGER_INIT_CSV_POSITION.y;

				//�g�嗦�̔������擾
				halfScale = mpShop[0]->GetConiferScale() / static_cast<float>(Utility::SCALE_HALF);

				//�ŏ��l���Z�o
				minpos = basepos - halfScale;
				/*==================�����܂�=================*/

				/*==================�ő�l���v�Z==================*/
				//�Z�o�������W+world���W�ϊ�
				basepos.x = mSaveInfo[i].mMaxPosition.x + GOMANAGER_INIT_CSV_POSITION.x;

				//�Z�o�������W+world���W�ϊ�
				basepos.z = mSaveInfo[i].mMaxPosition.y + GOMANAGER_INIT_CSV_POSITION.y;

				//�ő�l���Z�o
				maxpos = basepos + halfScale;

				/*==================�����܂�=================*/

				break;
			}
		}
		//����ݒ肷��
		mGroundObjectCollider[i].SetCollider(minpos, maxpos);
		mCorresColliderObject[i] = mSaveInfo[i].mObjectType;
	}
}

/*================================================================
�I�u�W�F�N�g�̃T�C�Y�𑪒肷��ċA�֐�:private
==================================================================*/
void GroundObjectManager::Search(int& chipX, int& chipY, int objectNum)
{
	//���ׂ������I�u�W�F�N�g�Ȃ�
	if (mGroundObjectMapChip[chipX + 1][chipY] == objectNum)
	{
		chipX++;
		this->Search(chipX, chipY, objectNum);

	}
	//�c������
	if(mGroundObjectMapChip[chipX][chipY + 1] == objectNum)
	{
		chipY++;
		this->Search(chipX, chipY, objectNum);
	}
}
/*================================================================
���ɓ����蔻��ɂ��邩���`�F�b�N����֐�:private
�����F���݂̃}�b�v�`�b�v���W
�Ԃ�l�Ftrue[���ɂ���]�@false[�Ȃ�]
==================================================================*/
bool GroundObjectManager::OverlapCheck(int x, int y)
{
	//�^�ϊ�
	DirectX::SimpleMath::Vector2 pos
		(DirectX::SimpleMath::Vector2(static_cast<float>(x), static_cast<float>(y)));

	//�ݒ肵�������蔻��̓��e�𑖍�����
	for (int i = 0; i < static_cast<int>(mSaveInfo.size()); i++)
	{
		if (mSaveInfo[i].mMinPosition.x<= pos.x && mSaveInfo[i].mMaxPosition.x >= pos.x&&
			mSaveInfo[i].mMinPosition.y <= pos.y && mSaveInfo[i].mMaxPosition.y >= pos.y)
		{
			return true;
		}
	}
	return false;
}
