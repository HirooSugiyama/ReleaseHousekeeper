/*
�e�X�e�[�W�̏����Ǘ�����N���X
*/
#include"pch.h"

#include"StageInfomation.h"

//�X�e�[�W�摜�̍��W
const DirectX::SimpleMath::Vector2 StageInfomation::STAGE_INFO_TEXTURE_POSITION(655.f,144.f);

//�X�e�[�W�摜�̊g�嗦
const DirectX::SimpleMath::Vector2 StageInfomation::STAGE_INFO_TEXTURE_SCALE(0.43f,0.36f);

//�X�e�[�W��Phase���̕`��ʒu
const DirectX::SimpleMath::Vector2 StageInfomation::STAGE_INFO_PHASENUM_POSITION(855.f, 480.f);

//�X�e�[�W�����Ǘ�����CSV�t�@�C���̃p�X
const std::string StageInfomation::STAGE_INFO_CSV_FILEPATH =
	"Resources/CSV/StageInfomation.csv";


/*===================================
�R���X�g���N�^
===================================*/
StageInfomation::StageInfomation()
	:
	mpStageMapTexture(),
	mpStageLevel(),
	mStageTextureTag{},
	mStagePhaseNum{},
	mStageLevelNum{}
{
	mpStageMapTexture = std::make_unique<ObjectTexture>();
	mpStageLevel = std::make_unique<StageLevel>();
	//�t�@�C���ǂݍ���
	this->LoadStageInfoCSV();
}

/*===================================
�f�X�g���N�^
===================================*/
StageInfomation::~StageInfomation()
{
}

/*===================================
����������
===================================*/
void StageInfomation::Initialize()
{
	//���\�[�X�̊m��
	auto pRM = ResourceManager::GetInstance();
	auto textute = pRM->GetTexture("StageCursor");
	//�摜����������
	mpStageMapTexture->Initialize();

	//�摜��ݒ肷��
	mpStageMapTexture->SetTexture(textute);

	//�g�嗦�̐ݒ�
	mpStageMapTexture->SetPosition(STAGE_INFO_TEXTURE_POSITION);

	//�g�嗦�̐ݒ�
	mpStageMapTexture->SetScale(STAGE_INFO_TEXTURE_SCALE);

	//�X�e�[�W���x���Ǘ��N���X�̏���������
	mpStageLevel->Initialize();
}


/*===================================
�`�揈��
===================================*/
void StageInfomation::Draw(int const& selectStageNum)
{

	//�X�e�[�W���̕`��
	Utility::DrawString
	(
		mStagePhaseNum[selectStageNum],
		STAGE_INFO_PHASENUM_POSITION,
		DirectX::Colors::Black,
		Utility::STRING_SIZE_MEDIUM
	);



	//���\�[�X�̊m��
	auto pRM = ResourceManager::GetInstance();
	auto textute = pRM->GetTexture(mStageTextureTag[selectStageNum]);
	//�摜��ݒ肷��
	mpStageMapTexture->SetTexture(textute);
	mpStageMapTexture->Draw();

	//�X�e�[�W���x���Ǘ��N���X�̕`�揈��
	int starnum = mStageLevelNum[selectStageNum];
	mpStageLevel->Draw(starnum);
}

/*===================================
�X�e�[�W�����t�@�C������擾����
===================================*/
void StageInfomation::LoadStageInfoCSV()
{
	//�t�@�C���ϊ�
	std::ifstream ifs(STAGE_INFO_CSV_FILEPATH);
	//1�s�̏���ۑ�����ϐ�
	std::string lineBuf;

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
			//�X�e�[�W�摜�̃^�O��ۑ�
			if (j == static_cast<int>(FILE_INFO::TEXTURE_TAG))
			{
				mStageTextureTag[i] = tileBuf;
			}
			//�t�F�[�Y�ԍ���ۑ�
			if (j == static_cast<int>(FILE_INFO::PHASE_NUM))
			{
				mStagePhaseNum[i] = atoi(tileBuf.c_str());
			}
			//�t�F�[�Y�̃��x����ۑ�
			if (j == static_cast<int>(FILE_INFO::LEVELOCITY))
			{
				mStageLevelNum[i] = atoi(tileBuf.c_str());
			}
		}
	}
}




