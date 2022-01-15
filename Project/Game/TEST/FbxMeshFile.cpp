#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <codecvt> 
#include <cstdio>
#include <sstream>
#include <string>
#include <stdio.h>
#include <iomanip>
#include "DirectGraphics.h"
#include "FbxMeshFile.h"
#include<SimpleMath.h>
#include <DeviceResources.h>
#include"DirectX11.h"


using namespace DirectX::SimpleMath;

bool FbxMeshFile::Load(const char* file_name, ID3D11Device *device, VertexShader* vertex_shader)
{

	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	// D3D�f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̎擾
	auto d3ddevice = pDR->GetD3DDevice();



	m_SwapChain = pDR->GetSwapChain();



	m_DepthStencilView = pDR->GetDepthStencilView();

	



	{
		/*
			Constant�o�b�t�@�[�쐬
				�R���X�^���g�o�b�t�@�[��CPU���̃f�[�^��
				�܂Ƃ߂�GPU���ɑ��M���邽�߂̃o�b�t�@�[

				�o�b�t�@�[�ɂ͍��W�ϊ��s��Ȃǂ�ݒ肷��
		*/
		D3D11_BUFFER_DESC buffer_desc;
		buffer_desc.ByteWidth = sizeof(ConstantBuffer);
		buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		buffer_desc.CPUAccessFlags = 0;
		buffer_desc.MiscFlags = 0;
		buffer_desc.StructureByteStride = 0;

		d3ddevice->CreateBuffer(&buffer_desc, nullptr, &m_ConstantBuffer);

	}
















	char file_path[256];
	std::vector<std::string> out_material_list;
	int len = (int)strlen(file_name);
	int path_tail_point = 0;

	for (int i = len - 1; i >= 0; i--)
	{
		if (file_name[i] == '/')
		{
			path_tail_point = i;
			break;
		}
	}


	{
		// RenderTargetView�̑ΏۂƂȂ�Buffer�̎擾
		ID3D11Texture2D* back_buffer = nullptr;
		if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer)))
		{
			return false;
		}

		// Buffer����RenderTargetView�̍쐬
		if (FAILED(d3ddevice->CreateRenderTargetView(back_buffer, NULL, &m_RenderTargetView)))
		{
			return false;
		}

		// Target�̎擾�I������̂�Buffer�����
		back_buffer->Release();

	}







	strncpy_s(file_path, file_name, path_tail_point + 1);

	if (LoadFbxFile(out_material_list, file_path, file_name) == false)
	{
		return false;
	}

	if (CreateVertexBuffer(device) == false)
	{
		return false;
	}

	if (CreateIndexBuffer(device) == false)
	{
		return false;
	}

	if (CreateInputLayout(device, vertex_shader) == false)
	{
		return false;
	}

	return true;
}

void FbxMeshFile::Render(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 degree)
{

	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	// D3D�f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̎擾
	auto device = pDR->GetD3DDevice();
	auto context = pDR->GetD3DDeviceContext();
	{
		// �v���~�e�B�u�̌`����w��
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// VerteXShader�APixelShader��ݒ�
		context->VSSetShader(
			m_VertexShader->GetShaderInterface(),	// �g�p����VertexShder
			/*
				ClassInstance�̃|�C���^��ݒ肷��
					�����Shader�쐬����ID3D11ClassLinkage���g�p�����ꍇ��
					�p���鍀�ڂȂ̂ō����nullptr���w�肷��
			*/
			nullptr,
			0);									// ClassInstance�̐�
		context->PSSetShader(m_PixelShader->GetShaderInterface(), nullptr, 0);

		// (OutputManger)RnderTaget�̎w��
		context->OMSetRenderTargets(
			1,							// �g�p����View�̐�
			&m_RenderTargetView,		// �g�p����RenderTargetView
			m_DepthStencilView);		// �g�p����DepthStencilView
	}













	UINT strides = sizeof(CustomVertex);
	UINT offsets = 0;

	for (auto& mesh : m_MeshList)
	{
		// �C���f�b�N�X�o�b�t�@�̐� = �}�e���A���̐��������b�V����`�悷��
		// IA(InputAssemblerStage)�ɓ��̓��C�A�E�g��ݒ肷��
		context->IASetInputLayout(m_InputLayout);
		// IA�ɐݒ肷�钸�_�o�b�t�@�̎w��
		context->IASetVertexBuffers(
				0,								// �o�b�t�@���M�̃X���b�g�ԍ�
				1,								// �o�b�t�@�̐�
				&mesh.m_VertexBuffer,	// ���_�o�b�t�@
				&strides,						// �o�b�t�@�Ɏg�p���Ă���\���̂̃T�C�Y
				&offsets);						// �J�n�I�t�Z�b�g

		context->IASetIndexBuffer(
				mesh.m_IndexBuffer,
				DXGI_FORMAT_R32_UINT,
				0);

			// ���[���h�}�g���N�X�ݒ�
			DirectX::XMMATRIX world_matrix;
			DirectX::XMMATRIX translate = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
			DirectX::XMMATRIX rotate_x = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(degree.x));
			DirectX::XMMATRIX rotate_y = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(degree.y));
			DirectX::XMMATRIX rotate_z = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(degree.z));
			DirectX::XMMATRIX scale_mat = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
			world_matrix = scale_mat * rotate_x * rotate_y * rotate_z * translate;

			// ���[���h�}�g���N�X���R���X�^���g�o�b�t�@�ɐݒ�
			XMStoreFloat4x4(&m_ConstantBufferData.World, XMMatrixTranspose(world_matrix));

			// �R���X�^���g�o�b�t�@�X�V
			context->UpdateSubresource(m_ConstantBuffer, 0, NULL, &m_ConstantBufferData, 0, 0);

			ID3D11Buffer* constant_buffer = m_ConstantBuffer;
			// �R���e�L�X�g�ɃR���X�^���g�o�b�t�@��ݒ�
			context->VSSetConstantBuffers(0, 1, &constant_buffer);
			context->PSSetConstantBuffers(0, 1, &constant_buffer);

			// �`��
			context->DrawIndexed(
				(UINT)mesh.m_Indices.size(),	// ���_��
				0,								// �I�t�Z�b�g
				0);								// �J�n���_�̃C���f�b�N�X
	}
}












void FbxMeshFile::LoadVertices(MeshData& mesh_data, FbxMesh* mesh)
{
	// ���_�o�b�t�@�̎擾
	FbxVector4* vertices = mesh->GetControlPoints();
	// �C���f�b�N�X�o�b�t�@�̎擾
	int* indices = mesh->GetPolygonVertices();
	// ���_���W�̐��̎擾
	int polygon_vertex_count = mesh->GetPolygonVertexCount();
	// GetPolygonVertexCount => ���_��
	for (int i = 0; i < polygon_vertex_count; i++)
	{
		CustomVertex vertex;
		// �C���f�b�N�X�o�b�t�@���璸�_�ԍ����擾
		int index = indices[i];

		// ���_���W���X�g������W���擾����
		vertex.Position.x = (float)-vertices[index][0];
		vertex.Position.y = (float)vertices[index][1];
		vertex.Position.z = (float)vertices[index][2];

		// �ǉ�
		mesh_data.m_Vertices.push_back(vertex);
	}
}

void FbxMeshFile::LoadIndices(MeshData& mesh_data, FbxMesh* mesh)
{
	// �|���S�����̎擾
	int polygon_count = mesh->GetPolygonCount();

	// �|���S���̐������A�ԂƂ��ĕۑ�����
	for (int i = 0; i < polygon_count; i++)
	{
		mesh_data.m_Indices.push_back(i * 3 + 2);
		mesh_data.m_Indices.push_back(i * 3 + 1);
		mesh_data.m_Indices.push_back(i * 3);
	}
}

void FbxMeshFile::LoadNormals(MeshData& mesh_data, FbxMesh* mesh)
{
	FbxArray<FbxVector4> normals;
	// �@�����X�g�̎擾
	mesh->GetPolygonVertexNormals(normals);

	// �@���ݒ�
	for (int i = 0; i < normals.Size(); i++)
	{
		mesh_data.m_Vertices[i].Normal.x = (float)-normals[i][0];
		mesh_data.m_Vertices[i].Normal.y = (float)normals[i][1];
		mesh_data.m_Vertices[i].Normal.z = (float)normals[i][2];
	}
}

void FbxMeshFile::LoadColors(MeshData& mesh_data, FbxMesh* mesh)
{
	// ���_�J���[�f�[�^�̐����m�F
	int color_count = mesh->GetElementVertexColorCount();
	if (color_count == 0)
	{
		return;
	}
	
	// ���_�J���[�f�[�^�̎擾
	FbxGeometryElementVertexColor* vertex_colors = mesh->GetElementVertexColor(0);

	if (vertex_colors == nullptr)
	{
		return;
	}

	FbxLayerElement::EMappingMode mapping_mode = vertex_colors->GetMappingMode();
	FbxLayerElement::EReferenceMode reference_mode = vertex_colors->GetReferenceMode();

	if (mapping_mode == FbxLayerElement::eByPolygonVertex)
	{
		if (reference_mode == FbxLayerElement::eIndexToDirect)
		{
			// ���_�J���[�o�b�t�@�擾
			FbxLayerElementArrayTemplate<FbxColor>& colors = vertex_colors->GetDirectArray();
			// ���_�J���[�C���f�b�N�X�o�b�t�@�擾
			FbxLayerElementArrayTemplate<int>& indeces = vertex_colors->GetIndexArray();
			for (int i = 0; i < indeces.GetCount(); i++)
			{
				int id = indeces.GetAt(i);
				FbxColor color = colors.GetAt(id);
				mesh_data.m_Vertices[i].Color.R((float)color.mRed);
				mesh_data.m_Vertices[i].Color.G((float)color.mGreen);
				mesh_data.m_Vertices[i].Color.B((float)color.mBlue);
				mesh_data.m_Vertices[i].Color.A((float)color.mAlpha);
			}
		}
	}
}

void FbxMeshFile::CreateMesh(FbxMesh* mesh)
{
	MeshData mesh_data;
	LoadIndices(mesh_data, mesh);
	LoadVertices(mesh_data, mesh);
	LoadNormals(mesh_data, mesh);
	LoadColors(mesh_data, mesh);

	m_MeshList.push_back(mesh_data);
}

bool FbxMeshFile::LoadFbxFile(std::vector<std::string>& out_material_list, const char* file_path, const char* file_name)
{
	// FbxManager�쐬
	FbxManager* fbx_manager = fbxsdk::FbxManager::Create();
	if (fbx_manager == nullptr)
	{
		return false;
	}
	
	// FbxImporter�쐬
	FbxImporter* fbx_importer = FbxImporter::Create(fbx_manager, "");
	if (fbx_importer == nullptr)
	{
		fbx_manager->Destroy();
		return false;
	}
	
	// FbxScene�쐬
	FbxScene* fbx_scene = FbxScene::Create(fbx_manager, "");
	if (fbx_scene == nullptr)
	{
		fbx_importer->Destroy();
		fbx_manager->Destroy();
		return false;
	}

	// File��������
	fbx_importer->Initialize(file_name);
	// scene�ɃC���|�[�g
	fbx_importer->Import(fbx_scene);

	FbxGeometryConverter converter(fbx_manager);
	// �|���S�����O�p�`�ɂ���
	converter.Triangulate(fbx_scene, true);

	// FbxMesh�̐����擾
	int mesh_num = fbx_scene->GetSrcObjectCount<FbxMesh>();

	for (int i = 0; i < mesh_num; i++)
	{
		// Mesh�쐬
		CreateMesh(fbx_scene->GetSrcObject<FbxMesh>(i));
	}

	fbx_importer->Destroy();
	fbx_scene->Destroy();
	fbx_manager->Destroy();

	return true;
}

bool FbxMeshFile::CreateVertexBuffer(ID3D11Device* device)
{
	for (auto& mesh : m_MeshList)
	{
		//���_�o�b�t�@�쐬
		D3D11_BUFFER_DESC buffer_desc;
		buffer_desc.ByteWidth = sizeof(CustomVertex) * (UINT)mesh.m_Vertices.size();	// �o�b�t�@�̃T�C�Y
		buffer_desc.Usage = D3D11_USAGE_DEFAULT;			// �g�p���@
		buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// BIND�ݒ�
		buffer_desc.CPUAccessFlags = 0;						// ���\�[�X�ւ�CPU�̃A�N�Z�X�����ɂ��Ă̐ݒ�
		buffer_desc.MiscFlags = 0;							// ���\�[�X�I�v�V�����̃t���O
		buffer_desc.StructureByteStride = 0;				// �\���̂̃T�C�Y

		D3D11_SUBRESOURCE_DATA sub_resource;
		sub_resource.pSysMem = &mesh.m_Vertices[0];	// �o�b�t�@�̒��g�̐ݒ�
		sub_resource.SysMemPitch = 0;				// texture�f�[�^���g�p����ۂɎg�p���郁���o
		sub_resource.SysMemSlicePitch = 0;			// texture�f�[�^���g�p����ۂɎg�p���郁���o

		// �o�b�t�@�쐬
		if (FAILED(device->CreateBuffer(
			&buffer_desc,								// �o�b�t�@���
			&sub_resource,								// ���\�[�X���
			&mesh.m_VertexBuffer)))	// �쐬���ꂽ�o�b�t�@�̊i�[��
		{
			return false;
		}
	}

	return true;
}

bool FbxMeshFile::CreateIndexBuffer(ID3D11Device* device)
{
	for (auto& mesh : m_MeshList)
	{
		//���_�o�b�t�@�쐬
		D3D11_BUFFER_DESC buffer_desc;
		buffer_desc.ByteWidth = sizeof(UINT) * (UINT)mesh.m_Indices.size();	// �o�b�t�@�̃T�C�Y
		buffer_desc.Usage = D3D11_USAGE_DEFAULT;							// �g�p���@
		buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;					// BIND�ݒ�
		buffer_desc.CPUAccessFlags = 0;										// ���\�[�X�ւ�CPU�̃A�N�Z�X�����ɂ��Ă̐ݒ�
		buffer_desc.MiscFlags = 0;											// ���\�[�X�I�v�V�����̃t���O
		buffer_desc.StructureByteStride = 0;								// �\���̂̃T�C�Y

		D3D11_SUBRESOURCE_DATA sub_resource;
		sub_resource.pSysMem = &mesh.m_Indices[0];							// �o�b�t�@�̒��g�̐ݒ�
		sub_resource.SysMemPitch = 0;										// texture�f�[�^���g�p����ۂɎg�p���郁���o
		sub_resource.SysMemSlicePitch = 0;									// texture�f�[�^���g�p����ۂɎg�p���郁���o

		// �o�b�t�@�쐬
		if (FAILED(device->CreateBuffer(
			&buffer_desc,						// �o�b�t�@���
			&sub_resource,						// ���\�[�X���
			&mesh.m_IndexBuffer)))		// �쐬���ꂽ�o�b�t�@�̊i�[��
		{
			return false;
		}
	}

	return true;
}

bool FbxMeshFile::CreateInputLayout(ID3D11Device* device, VertexShader* vertex_shader)
{
	D3D11_INPUT_ELEMENT_DESC vertex_desc[]{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXTURE",	0, DXGI_FORMAT_R32G32_FLOAT,		0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	//���_���C�A�E�g�쐬
	if (FAILED(device->CreateInputLayout(
		vertex_desc,				// ���C�A�E�g�ݒ�
		ARRAYSIZE(vertex_desc),		// �z��T�C�Y
		vertex_shader->GetData(),	// ���C�A�E�g�Ɗ֘A�t���钸�_�V�F�[�_�̃f�[�^
		vertex_shader->GetSize(),	// ���C�A�E�g�Ɗ֘A�t���钸�_�V�F�[�_�̃T�C�Y
		&m_InputLayout)))			// �쐬���ꂽ���_���C�A�E�g�̊i�[��
	{
		return false;
	}

	return true;
}

