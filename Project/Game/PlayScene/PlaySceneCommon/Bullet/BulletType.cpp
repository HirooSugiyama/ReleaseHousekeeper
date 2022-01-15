/*
�e���Ǘ��t�@�C��
�쐬���F2021/10/10
*/
#include"pch.h"

#include"BulletType.h"


/*===================================
�R���X�g���N�^
===================================*/
BulletType::BulletType()
	:
	mpBulletInfomation()
{
	//�̈�m��
	for (int i = 0; i < static_cast<int>(eWeaponType::NUM); i++)
	{
		mpBulletInfomation[static_cast<eWeaponType>(i)] = std::make_unique<BulletInfomation>();
	}

}

/*===================================
�f�X�g���N�^
===================================*/
BulletType::~BulletType()
{
}

/*=================================
����ǂݍ���
�����F�t�@�C���p�X
===================================*/
void BulletType::SetCSV(std::string const& filepath)
{
	//���\�[�X�̎擾
	auto pRM = ResourceManager::GetInstance();

	//�t�@�C���ϊ�
	std::ifstream ifs(filepath);
	//1�s�̏���ۑ�����ϐ�
	std::string lineBuf;
	//�ꎞ�I�ɕۑ��p

	//1�s�̓ǂݍ��ݏ���_
	for (int i = 0; std::getline(ifs, lineBuf); i++)
	{
		//1�s�̏���stream�ɂ���
		std::stringstream lineStream(lineBuf);
		//1�}�X�̏��ۑ��p
		std::string tileBuf;

		//1�}�X�̏��ǂݍ��ݏ���
		for (int j = 0; std::getline(lineStream, tileBuf, ','); j++)
		{
			switch (j)
			{
				case eReadInfo::MODEL_TAG:
				{
					auto model = pRM->GetCmoModel(tileBuf);
					//�Ή��������̃}�b�v�ɑΉ��������f����ۑ�
					mpBulletInfomation[static_cast<eWeaponType>(i)]->mBulletModel = model;
					break;
				}
				case eReadInfo::SPEED:
				{
					//�Ή��������̃}�b�v�ɑΉ������e�̑��x��ۑ�
					mpBulletInfomation[static_cast<eWeaponType>(i)]->mBulletVelocityZ
						= std::stof(tileBuf);

					break;
				}
				case eReadInfo::SCALE_X:
				{
					//�Ή��������̃}�b�v�ɑΉ������e�̊g�嗦��ۑ�
					mpBulletInfomation[static_cast<eWeaponType>(i)]->mBulletScale.x
						= std::stof(tileBuf);

					break;
				}
				case eReadInfo::SCALE_Y:
				{
					//�Ή��������̃}�b�v�ɑΉ������e�̊g�嗦��ۑ�
					mpBulletInfomation[static_cast<eWeaponType>(i)]->mBulletScale.y
						= std::stof(tileBuf);

					break;
				}
				case eReadInfo::SCALE_Z:
				{
					//�Ή��������̃}�b�v�ɑΉ������e�̊g�嗦��ۑ�
					mpBulletInfomation[static_cast<eWeaponType>(i)]->mBulletScale.z
						= std::stof(tileBuf);

					break;
				}
				case eReadInfo::ATTACK_NUM:
				{
					//�Ή��������̃}�b�v�ɑΉ������e�̍U���͂�ۑ�
					mpBulletInfomation[static_cast<eWeaponType>(i)]->mBulletAttackNum
						= std::stoi(tileBuf);

					break;
				}
				case eReadInfo::INTERVAL:
				{
					//�Ή��������̃}�b�v�ɑΉ������e�C���^�[�o����ۑ�
					mpBulletInfomation[static_cast<eWeaponType>(i)]->mBulletIntervalNum
						= atoi(tileBuf.c_str());

					break;
				}
			}
		}
	}
}