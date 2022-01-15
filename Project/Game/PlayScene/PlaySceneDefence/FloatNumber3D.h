/*
�����������\�����s���N���X
�쐬���F2021/10/22
*/
#pragma once

//���N���X
#include"../../Common/SpriteNumber/NumberBase.h"

//����
#include"../Effect/Effect.h"

//�O���錾
class CameraBase;

class FloatNumber3D :public NumberBase
{
private:


	//�`��ł���ő包��
	static const int MAX_DIGIT_NUM = 3;

	//�������m�̕�
	static const float NUM_SHIFT;

	//�����̈ړ����x
	static const float NUM_MOVE_VELOCITY;

	//�����x�̕ω����x
	static const float NUM_ALPHA_VELOCITY;

	//�摜�g�嗦
	static const DirectX::SimpleMath::Vector2 TEX_SCALE;


	//�g�p���鐔���̃X�v���C�g�摜
	std::unique_ptr<EffectSpriteTexture> mpNumberTexture[MAX_DIGIT_NUM];

	//�|�C���^�ۑ��p
	CameraBase* mpCamera;

	//�n�_���W
	DirectX::SimpleMath::Vector3 mInitPosition;

	//�g�p�t���O
	bool mUseFlag;

public:

	//�R���X�g���N�^
	FloatNumber3D();
	//�f�X�g���N�^
	~FloatNumber3D()override;
	//����������
	void Initialize(CameraBase* pCamera);
	//�쐬����
	void Create(int num, DirectX::SimpleMath::Vector3 pos);
	//�X�V����
	void Update()override;

	//�`�揈��
	void Draw()override;

	//���Z�b�g����
	void Reset();

private:
	//�e�ϐ��ɂق����ԍ�������
	void CreateNumber(std::vector<int> num);
};

