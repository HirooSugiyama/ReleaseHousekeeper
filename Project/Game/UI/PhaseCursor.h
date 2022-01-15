/*
�ЂƂ̃t�F�[�Y�̎n�܂�̃e�N�X�`�����Ǘ�����N���X
�쐬���F2021/09/18
*/
#pragma once


//����
#include"../Common/ObjectTexture.h"

class PhaseCursor
{
private:
	//�摜�̊g�嗦
	static const DirectX::SimpleMath::Vector2 PHASECURSOR_TEXTURE_SCALE;


	//���j�[�N�|�C���^
	std::unique_ptr<ObjectTexture> mpPhaseCursorTexture;

public:

	//�R���X�g���N�^
	PhaseCursor();
	//�f�X�g���N�^
	~PhaseCursor();
	//����������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	//���W�̐ݒ�
	void SetPosition(DirectX::SimpleMath::Vector2 const& pos);

};
