/*
��Q���Ǘ��N���X
*/
#include<pch.h>
#include "WallManager.h"


//�O���錾
//�����蔻��p
#include"../Player/Player.h"
#include"../../PlaySceneDefence/PreparingBlock.h"
#include"../Enemy/EnemyManager.h"

//�����蔻��œ����{���̂��ߎg�p
#include"../ObjectModel/BoxModel.h"
//�ړ����x�̎擾�Ŏg�p
#include"../ObjectMove.h"

#include"WallConstant.h"

/*===================================
�R���X�g���N�^
===================================*/
WallManager::WallManager()
	:
	mpWall{}
{
	for (int i = 0; i < WALL_MAX_NUM; i++)
	{
		mpWall[i] = std::make_unique<Wall>();
	}
}

/*===================================
�f�X�g���N�^
===================================*/
WallManager::~WallManager()
{
}

/*===================================
����������
===================================*/
void WallManager::Initialize()
{
	//�ϐ��̐錾
	DirectX::SimpleMath::Vector3 pos,scale;

	//����
	pos.x = WallConstant::WALL_LEFT_POSITION_X;
	pos.y = WallConstant::WALL_LEFT_POSITION_Y;
	pos.z = WallConstant::WALL_LEFT_POSITION_Z;

	scale.x = WallConstant::WALL_LEFT_SCALE_X;
	scale.y = WallConstant::WALL_LEFT_SCALE_Y;
	scale.z = WallConstant::WALL_LEFT_SCALE_Z;

	mpWall[static_cast<int>(eWallPosition::LEFT_WALL)]->Initialize(pos, scale);

	//�E��
	pos.x = WallConstant::WALL_RIGHT_POSITION_X;
	pos.y = WallConstant::WALL_RIGHT_POSITION_Y;
	pos.z = WallConstant::WALL_RIGHT_POSITION_Z;

	scale.x = WallConstant::WALL_RIGHT_SCALE_X;
	scale.y = WallConstant::WALL_RIGHT_SCALE_Y;
	scale.z = WallConstant::WALL_RIGHT_SCALE_Z;
	mpWall[static_cast<int>(eWallPosition::RIGHT_WALL)]->Initialize(pos, scale);

}
/*===================================
�`�揈��
===================================*/
void WallManager::Draw()
{
	for (int i = 0; i < WALL_MAX_NUM; i++) 
	{
		mpWall[i]->Draw();
	}
}

/*===================================
�G�Ƃ̓����蔻����񂷏���
�����F�G�Ǘ��N���X�̃|�C���^
===================================*/
void WallManager::RoolEnemyManagerChackHit(EnemyManager* pEnemyManager)
{
	for (int i = 0; i < WALL_MAX_NUM; i++)
	{
		//�����蔻�����
		pEnemyManager->ChackHitWallEnemy(mpWall[i]->GetWallModel()->GetAABBCollider());
	}
}
