/*
3D���W��2D�摜��`�悷��ėp�N���X
(�g�p��F�G�t�F�N�g�Ȃ�)
�쐬���F2021/09/02
*/
#include "pch.h"
#include "Effect.h"

const float EffectSpriteTexture::UV_POSITION_MAX = 1.f;

/*=========================================================================
�R���X�g���N�^
�����Flinenum(�c��ő吔)�Apos(�`����W)�Ascale(�g�嗦)
=========================================================================*/
EffectSpriteTexture::EffectSpriteTexture(int linenum,
	DirectX::SimpleMath::Vector3 pos,
	DirectX::SimpleMath::Vector2 scale)
	:
	mPosition(pos),
	mScale(scale),
	mpSpriteBatch(),
	mSpriteTimer(),
	mConstTimer(0),
	mSpriteFlag(false),
	mLineMaxNum(linenum),
	mLineNum(0),
	mHorizontalCutNum(0),
	mWidthNum(0),
	mWidthIncreaseNum(0.f),
	mHeightIncreaseNum(0.f),
	mSpriteSrc(),
	mTexture(nullptr),
	mInputLayout(nullptr),
	mpPrimitiveBatch(nullptr),
	mpBasicEffect(nullptr),

	mWorld(),
	mCamera(),
	mLoopFlag(true),
	mAlpha(1.f)
{
}

/*=========================
�f�X�g���N�^
=========================*/
EffectSpriteTexture::~EffectSpriteTexture()
{

}

/*=========================
�摜�̎w��
�����F�摜�p�X
=========================*/
void EffectSpriteTexture::SetFileName(const wchar_t* filepath)
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();


	// D3D�f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̎擾
	auto device = pDR->GetD3DDevice();



	// �e�N�X�`���̓ǂݍ���
	DirectX::CreateWICTextureFromFile(device, filepath, nullptr,
		mTexture.ReleaseAndGetAddressOf());
}

/*=========================
�摜�̎w��
�����F�摜���
=========================*/
void EffectSpriteTexture::SetTexture(ID3D11ShaderResourceView* texture)
{
	mTexture = texture;
}

/*=====================================
������
�����F�`��ɕK�v�ȃo�b�`�̃|�C���^
===================================*/
void EffectSpriteTexture::Initialize()
{
	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	//�|�C���^�̕ۑ�
	mpSpriteBatch = pDxIF.GetSpriteBatch();

	// �v���~�e�B�u�o�b�`�̍쐬 
	mpPrimitiveBatch =
		std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(pDR->GetD3DDeviceContext());


	//�x�[�V�b�N�G�t�F�N�g�̍쐬
	mpBasicEffect = std::make_unique<DirectX::BasicEffect>(pDR->GetD3DDevice());

	//���̓��C�A�E�g���쐬���邽�߂ɕK�v�ȏ��
	const void* shaderByteCode;
	size_t byteCodeLength;

	//���_�������肷�邽�߂ɕK�v�ȏ��
	mpBasicEffect->SetLightingEnabled(false);		//���C�gOFF
	mpBasicEffect->SetTextureEnabled(true);			//�e�N�X�`��ON
	mpBasicEffect->SetVertexColorEnabled(false);	//���_�J���[OFF

	//�g�p���钸�_�V�F�[�_�[���̎擾
	mpBasicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	//���̓��C�A�E�g�̍쐬
	pDR->GetD3DDevice()->CreateInputLayout(
		DirectX::VertexPositionTexture::InputElements,
		DirectX::VertexPositionTexture::InputElementCount,
		shaderByteCode,
		byteCodeLength,
		mInputLayout.GetAddressOf()
	);

	//�v���~�e�B�u�o�b�`�̍쐬
	mpPrimitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>
		(pDR->GetD3DDeviceContext());

	//�P/�������ő����ʂ����߂���
	mWidthIncreaseNum = UV_POSITION_MAX / static_cast<float>(mHorizontalCutNum);
	mHeightIncreaseNum = UV_POSITION_MAX / static_cast<float>(mLineMaxNum);
}



/*=========================
�X�V����
=========================*/
void EffectSpriteTexture::Update()
{
	if (mSpriteFlag)
	{
		//�X�v���C�g�^�C�}�[����
		mSpriteTimer++;
		//�����X�v���C�g���񂷃^�C�~���O��������
		if (mConstTimer == mSpriteTimer)
		{
			//�^�C�}�[�͏���������
			mSpriteTimer = 0;

			//���ɃX�v���C�g������炷
			mWidthNum++;

		}
		//�����摜�E�[�ɂ��E�ɍs������
		if (mWidthNum > mHorizontalCutNum)
		{
			//�s��������炷
			mLineNum++;

			//������ʉE�[�̍ŏI�s�ɍs������
			if (mLineMaxNum <= mLineNum)
			{
				
				//����̃X�v���C�g���ŏ��̈ʒu�ɖ߂�
				mWidthNum = 0;
				//�s���Ȃǂ��ׂă��Z�b�g
				mLineNum = 0;			
				//�������[�v���I�t�Ȃ�
				if (mLoopFlag == false)
				{
					//�X�v���C�g���I������
					mSpriteFlag = false;

					return;
				}
			}
			//����ȊO(�摜�E�[�����ǁA�ŏI�s����Ȃ��ꍇ)
			else
			{
				//����̃X�v���C�g���ŏ��̈ʒu�ɖ߂�
				mWidthNum = 0;
			}
			//�^�C�}�[������
			mSpriteTimer = 0;
		}
	}
}
/*=======================
�`�揈��
=========================*/
void EffectSpriteTexture::ExtendDraw()
{
	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();
	CameraInfoIF& pCiIF = CameraInfoIF::GetCameraInfoIFInstance();
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	//�f�o�C�X�R���e�L�X�g�̎擾
	auto* context = pDR->GetD3DDeviceContext();


	DirectX::SimpleMath::Matrix reverseView = pCiIF.GetView()->Invert();

	//�ړ��s��𖳌���
	reverseView._41 = 0.f;
	reverseView._42 = 0.f;
	reverseView._43 = 0.f;

	DirectX::SimpleMath::Vector3 pos = mPosition;

	mWorld = reverseView * DirectX::SimpleMath::Matrix::CreateTranslation(pos);



	pos.x = mWorld._31;
	pos.y = mWorld._32;
	pos.z = mWorld._33;



	//�؂�����W�̎w��p�ϐ��̐錾
	float right, left, top, bottom;

	left = mWidthIncreaseNum * mWidthNum;
	right = mWidthIncreaseNum * (mWidthNum + 1);


	top = mHeightIncreaseNum * mLineNum;
	bottom = mHeightIncreaseNum * (mLineNum + 1);

	//�����W�̎w��p�ϐ��̐錾
	float polyRight(0.f), polyLeft(0.f), polyTop(0.f), polyBottom(0.f);


	polyRight = pos.x + mScale.x;
	polyLeft = pos.x - mScale.x;
	polyTop = pos.y + mScale.y;
	polyBottom = pos.y - mScale.y;

	//�G�t�F�N�g�Ɋe��ϊ��s��̎w��i���[���h�s��ȊO�j
	mpBasicEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
	mpBasicEffect->SetWorld(mWorld);
	mpBasicEffect->SetView(*pCiIF.GetView());				//�r���[�s��̐ݒ�
	mpBasicEffect->SetProjection(*pCiIF.GetProjection());	//�ˉe�s��̐ݒ�
	mpBasicEffect->SetTexture(mTexture.Get());
	mpBasicEffect->Apply(context);
	//���̓A�Z���u���X�e�[�W�ɓ��̓��C�A�E�g��ݒ�
	context->IASetInputLayout(mInputLayout.Get());
	//�����������̐ݒ�:NonPremultiplied->�摜���X�g���[�g�E���`�����l���̏ꍇ
	context->OMSetBlendState(pDxIF.GetCommonStates()->NonPremultiplied(), nullptr,
		0xFFFFFFFF);


	//�s�N�Z���V�F�[�_�ɃT���v���i�e�N�X�`���̈������j���w�肷��
	auto sampler = pDxIF.GetCommonStates()->LinearWrap();
	context->PSSetSamplers(0, 1, &sampler);

	//���X�^���C�U�X�e�[�g�̐ݒ�F�w�ʉ������O(�A�ʏ���)���Ȃ�->�|���S���̗��ʂ��\��
	//context->RSSetState(pDxIF.GetCommonStates()->CullNone());

	//// ���_���i�|���S���̒��_�j 
	DirectX::VertexPositionTexture vertex[4] =
	{
		//����
		DirectX::VertexPositionTexture
		(
			DirectX::SimpleMath::Vector3(polyLeft, polyTop, pos.z),
			DirectX::SimpleMath::Vector2(left, top)
		),

		//�E��
		DirectX::VertexPositionTexture
		(
			DirectX::SimpleMath::Vector3(polyRight, polyTop, pos.z),
			DirectX::SimpleMath::Vector2(right, top)
		),

		//����
		DirectX::VertexPositionTexture
		(
			DirectX::SimpleMath::Vector3(polyLeft, polyBottom, pos.z),
			DirectX::SimpleMath::Vector2(left,bottom)
		),

		//�E��
		DirectX::VertexPositionTexture
		(
			DirectX::SimpleMath::Vector3(polyRight,polyBottom, pos.z),
			DirectX::SimpleMath::Vector2(right, bottom)
		)
	};

	static const uint16_t indices[] = 
	{
		0,1,2,		//1���ڂ̎O�p�`
		1,3,2		//2���ڂ̎O�p�`
	};
	//�v���~�e�B�u�o�b�`�̍쐬
	mpPrimitiveBatch->Begin();

	//���_�C���f�b�N�X���g�����`��
	mpPrimitiveBatch->DrawIndexed(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		indices,
		(sizeof(indices) / sizeof(indices[0])),
		vertex,
		(sizeof(vertex) / sizeof(vertex[0]))
	);

	//�v���~�e�B�u�o�b�`�̏I��
	mpPrimitiveBatch->End();
}


/*=========================
�I������
=========================*/
void EffectSpriteTexture::Finalize()
{
}
