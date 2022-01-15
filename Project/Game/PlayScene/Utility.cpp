/*
�ėp�������܂Ƃ߂��t�@�C��
�쐬���F2021/08/31
*/
#include"pch.h"
#include"Utility.h"

//�����t�H���g�T�C�Y
//��
const float Utility::STRING_SIZE_BIG = 3.5f;
//��
const float Utility::STRING_SIZE_MEDIUM = 3.f;
//��
const float Utility::STRING_SIZE_SMALL = 2.f;
//�ɏ�
const float Utility::STRING_SIZE_MINIMUM = 1.f;


//�����o�b�t�@�[�T�C�Y
const size_t Utility::BUFFER_SIZE = 32;


//��O����
const int Utility::EXCEPTION_NUM = -1;

//�g�嗦�𔼕��ɂ���
const int Utility::SCALE_HALF = 2;


/*==============================
�������`�悷�鋤�ʊ֐�
�����F�`�悷�鐔��
		���W
		�F
		�����T�C�Y
==============================*/
void Utility::DrawString(int const& drawNum,
						DirectX::SimpleMath::Vector2 const& stringPosition,
						DirectX::FXMVECTOR const& stringColor,
						float const& stringSize,
						int const& secondNum)
{
	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();
	wchar_t buf[32];

	swprintf_s(buf, Utility::BUFFER_SIZE, L" %d", drawNum);
	if (secondNum != EXCEPTION_NUM)
	{
		swprintf_s(buf, Utility::BUFFER_SIZE, L" %d:%d", drawNum, secondNum);
	}

	pDxIF.GetSpriteFont()->DrawString
	(
		pDxIF.GetSpriteBatch(),
		buf,
		stringPosition,
		stringColor,
		0,
		DirectX::SimpleMath::Vector2::Zero, 
		stringSize
	);
}

/*==============================
�������`�悷�鋤�ʊ֐�
�����F�`�悷�镶����
		���W
		�F
		�����T�C�Y
==============================*/
void Utility::DrawString(wchar_t const* string,
	DirectX::SimpleMath::Vector2 const& stringPosition,
	DirectX::FXMVECTOR const& stringColor,
	float const& stringSize)
{
	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();

	pDxIF.GetSpriteFont()->DrawString
	(
		pDxIF.GetSpriteBatch(),
		string,
		stringPosition,
		stringColor,
		0,
		DirectX::SimpleMath::Vector2::Zero,
		stringSize
	);
}
