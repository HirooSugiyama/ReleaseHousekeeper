/*
��ɕ����_���Ǘ�����N���X
*/
#pragma once


class Cloud
{
private:
	//�_�̏������W
	static const DirectX::SimpleMath::Vector2 CLOUD_POSITION1;
	static const DirectX::SimpleMath::Vector2 CLOUD_POSITION2;
	static const DirectX::SimpleMath::Vector2 CLOUD_POSITION3;

	//�_�̈ړ����x
	static const float CLOUD_VELOCITY;
	//�_�̉�ʊO���W
	static const float CLOUD_OVER_POSITION;
	static const float CLOUD_RESET_POSITION;


	//�萔
	//�_�̐�
	static const int CLOUD_NUM = 3;

	//�ϐ�
	//�_�̉摜
	std::unique_ptr<ObjectTexture> mpClouds[CLOUD_NUM];


public:
	//�R���X�g���N�^
	Cloud();
	//�f�X�g���N�^
	~Cloud();

	//������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

private:
	//�ړ�����
	void Move();
	//���[�v����
	void Warp();

};
