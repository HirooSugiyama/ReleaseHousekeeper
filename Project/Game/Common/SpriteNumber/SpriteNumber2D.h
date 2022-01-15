/*
�X�v���C�g�V�[�g�̐������QD�`�悷��N���X

�쐬���F2021/12/11
*/
#pragma once


//�O���錾
#include"../ObjectSpriteTexture.h"
#include"NumberBase.h"

enum class eAlign
{
	LEFT,
	RIGHT
};

class SpriteNumber2D :public NumberBase
{
private:

	//�`��ł���ő包��
	static const int MAX_DIGIT_NUM = 5;

	//����1��������̉摜�T�C�Y
	static const RECT SPRITE_SIZE;

	//�摜�̊g�嗦
	static const DirectX::SimpleMath::Vector2 TEX_SCALE;

	//������
	static const int STRING_SPACE;


	//�g�p���鐔���̃X�v���C�g�摜
	std::unique_ptr<ObjectSpriteTexture> mpNumberTexture[MAX_DIGIT_NUM];

	//�Ή�����g�p�t���O
	bool mUseFlag[MAX_DIGIT_NUM];

	//�n�_���W
	DirectX::SimpleMath::Vector2 mInitPosition;

	//�摜���S�ʒu
	eAlign mAlign;

	//�摜�̂��炷��
	float mNumShift;

	//�摜�g�嗦
	DirectX::SimpleMath::Vector2 mTextureScale;

public:

	//�R���X�g���N�^
	SpriteNumber2D();
	//�f�X�g���N�^
	~SpriteNumber2D()override;
	//����������
	void Initialize();
	//�쐬����
	void Create(int const& num, DirectX::SimpleMath::Vector2 const& pos);

	//�`�揈��
	void Draw()override;

	//�e�ϐ��A�萔�̃A�N�Z�T
	int GetMaxDigitNum() { return MAX_DIGIT_NUM; }

	RECT GetSpriteSize() { return SPRITE_SIZE; }

	ObjectSpriteTexture* GetNumberTexture(int index) { return mpNumberTexture[index].get(); }

	void SetUseFlag(int index, bool flag) { mUseFlag[index] = flag; }
	int GetUseFlag(int index) { return mUseFlag[index]; }

	DirectX::SimpleMath::Vector2 GetInitPosition() { return mInitPosition; }

	//�g�嗦��ݒ肷��
	void SetScale(float scale);

	//�摜���S�ʒu���w�肷��
	void SetAlign(eAlign align) { mAlign = align; }


private:
	//�e�ϐ��ɂق����ԍ�������
	void CreateNumber(std::vector<int> const& num);

	//�����Ԑ�������
	void CreateStringShift();
};
