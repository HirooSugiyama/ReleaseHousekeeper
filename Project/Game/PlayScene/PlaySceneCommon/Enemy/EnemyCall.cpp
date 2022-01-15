/*
�G��ǂݍ��ނ��߂̃N���X
�쐬���F2021/05/25
*/
#include"pch.h"
#include "EnemyCall.h"

/*========================
�R���X�g���N�^
========================*/
EnemyCall::EnemyCall()
	:
	mEnemyInfo()
{
}

/*===================================
�f�X�g���N�^
===================================*/
EnemyCall::~EnemyCall()
{
}


/*==============================
�G�����w�肷��֐�
�����F�t�@�C���̃p�X
==============================*/
void EnemyCall::LoadInfo(std::string const& filepath)
{
	//�����̓`���[�g���A����p�ǂݍ��݃N���X�Ȃ̂Ńt�@�C������ǂݍ���
	this->SetCSV(filepath);
}

/*=============================
�ۑ��p�ϐ���������
==============================*/
void EnemyCall::Reset()
{
	mEnemyInfo.resize(0);
}


/*==============================
�t�@�C���ǂݍ��ݏ����Fprivate
�����F�t�@�C���̃p�X
==============================*/
void EnemyCall::SetCSV(std::string const& filepath)
{
	//�񋓌^���ȑf��
	const int csv_pos_x = static_cast<int>(eEnemyCSV::POSITION_X);
	const int csv_pos_y = static_cast<int>(eEnemyCSV::POSITION_Y);
	const int csv_pos_z = static_cast<int>(eEnemyCSV::POSITION_Z);
	const int phasenum = static_cast<int>(eEnemyCSV::PHASE_NUM);

	//�t�@�C���ϊ�
	std::ifstream ifs(filepath);
	//1�s�̏���ۑ�����ϐ�
	std::string lineBuf;
	//�ꎞ�I�ɕۑ��p
	EnemyInfo instantpos;

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
			//���W�̕ۑ�
			if (j == csv_pos_x) {
				instantpos.mVectorESPosition.x = static_cast<float>(atof(tileBuf.c_str()));
			}
			else if (j == csv_pos_y) {
				instantpos.mVectorESPosition.y = static_cast<float>(atof(tileBuf.c_str()));
			}
			else if (j == csv_pos_z) {
				instantpos.mVectorESPosition.z = static_cast<float>(atof(tileBuf.c_str()));
			}
			else if (j == phasenum) {
				instantpos.mPhaseNumber = static_cast<int>(atof(tileBuf.c_str()));
			}
		}

		if (instantpos.mPhaseNumber != 0)
		{
			//�T�C�Y�𑝂₷
			mEnemyInfo.push_back(instantpos);

			instantpos.mPhaseNumber = 0;
			instantpos.mVectorESPosition = DirectX::SimpleMath::Vector3::Zero;
		}		
	}
}