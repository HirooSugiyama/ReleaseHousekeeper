/*
���U���g�ŕ`�悷�镶���̒萔�Q
�쐬���F2021/10/22
*/
#pragma once




struct ResultDrawStringConstant
{
	//�e�����̍��W
	static const DirectX::SimpleMath::Vector2 STRING_RESULT_POSITION;
	static const DirectX::SimpleMath::Vector2 STRING_CLEARBONUS_POSITION;
	static const DirectX::SimpleMath::Vector2 STRING_MONEYBONUS_POSITION;
	static const DirectX::SimpleMath::Vector2 STRING_DEFEATBONUS_POSITION;
	static const DirectX::SimpleMath::Vector2 STRING_SCORE_POSITION;
	static const DirectX::SimpleMath::Vector2 STRING_SCORERANKING_POSITION;
	//�e�핶���̈ړ����W
	static const float STRING_DISTANCE;
	//�ړ����x
	static const float STRING_VELOCITY;

	//�X�R�A�����L���O�̋L���̈�
	static const int SCORE_RANKING_STORAGE = 5;

	//�n�C�X�R�A�`��ʒu
	static const DirectX::SimpleMath::Vector2 SCORE_RANKING_STRING_POSITION;
	static const DirectX::SimpleMath::Vector2 SCORE_RANKING_NUM_POSITION;
	//�ړ���
	static const float SCORE_RANKING_SHIFT;

	//��������l�ւ̈ړ����W
	static const DirectX::SimpleMath::Vector2 STRING_NUM_SHIFT;
};