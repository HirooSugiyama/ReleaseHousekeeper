/*
�G��ǂݍ��ނ��߂̃N���X
�쐬���F2021/05/25
*/
#pragma once

class EnemyCall
{
private:
	//���W���
	enum class eEnemyCSV :int
	{
		POSITION_X,		//X���W
		POSITION_Y,		//Y���W
		POSITION_Z,		//Z���W
		PHASE_NUM,	//�����o���t�F�[�Y��
		ENEMY_TYPE,	//�G�̎��
	};

	//�G���
	struct EnemyInfo
	{
		//�G�̍��W
		DirectX::SimpleMath::Vector3 mVectorESPosition;	//1,2,3�Ԗڂ̗v�f
		//�t�F�[�Y�ԍ�
		int mPhaseNumber;

		//�R���X�g���N�^
		EnemyInfo()
			:mVectorESPosition()
			, mPhaseNumber()
		{}
	};
	//�萔

	//���̉�
	std::vector<EnemyInfo> mEnemyInfo;

public:
	//�R���X�g���N�^
	EnemyCall();
	//�f�X�g���N�^
	~EnemyCall();
	//�t�@�C������Ԃ�
	EnemyInfo GetEnemyStructer(int const& i)const {return mEnemyInfo[i];}
	//�v�f����Ԃ�
	int GetEnemyStructerSize() const {return mEnemyInfo.size();}
	//�G�����w�肷��֐�
	void LoadInfo(std::string const& filepath);
	//�v�f��������
	void Reset();

private:
	//CSV�t�@�C�������w��
	void SetCSV(std::string const& filepath);
};