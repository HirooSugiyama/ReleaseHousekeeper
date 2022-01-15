#ifndef FBX_MESH_FILE_H_
#define FBX_MESH_FILE_H_

#include <fbxsdk.h>
#include <vector>
#include <map>
#include <d3d11.h>
#include "DirectGraphics.h"
#include "VertexShader.h"
#include "GraphicsUtility.h"
#include<SimpleMath.h>

class FbxMeshFile
{
public:
	/** Constructor */
	FbxMeshFile() 
		:m_InputLayout(nullptr)
		,m_PixelShader(nullptr)
		,m_VertexShader(nullptr)
		,m_RenderTargetView(nullptr)
		,m_DepthStencilView(nullptr)
		,m_ConstantBuffer(nullptr)
	{
		m_MeshList.clear();

		m_VertexShader = new VertexShader();
		m_PixelShader = new PixelShader();
	}

	VertexShader* GetVertexShader() { return m_VertexShader; }
	PixelShader* GetPixelShader() { return m_PixelShader; }


	/** Destructor */
	~FbxMeshFile()
	{

		for (auto mesh : m_MeshList)
		{
			if (mesh.m_VertexBuffer != nullptr)
			{
				mesh.m_VertexBuffer->Release();
			}

			if (mesh.m_IndexBuffer != nullptr)
			{
				mesh.m_IndexBuffer->Release();
			}
			mesh.m_Indices.clear();
			mesh.m_Vertices.clear();
		}

		if (m_InputLayout != nullptr)
		{
			m_InputLayout->Release();
			m_InputLayout = nullptr;
		}
		
		if (m_VertexShader != nullptr)
		{
			delete m_VertexShader;
			m_VertexShader = nullptr;
		}
		if (m_PixelShader != nullptr)
		{
			delete m_PixelShader;
			m_PixelShader = nullptr;
		}
	}

	/**
	* @brief ���f���ǂݍ���@n
	* ���f���f�[�^��ǂݍ���
	* @return �쐬�̐��� ����(true)
	* @param[in] device �f�o�C�X
	* @param[in] vertex_shader ���f���Ɗ֘A�t����VertexShader
	*/
	bool Load(const char* file_name, ID3D11Device* device, VertexShader* vertex_shader);

	/**
	* @brief ���f���`��֐�@n
	* �w�肳�ꂽ���Ń��f����`�悷��
	* @return �쐬�̐��� ����(true)
	* @param[in] graphics �`��Ǘ��N���X
	* @param[in] pos �`����W
	* @param[in] scale �g�k��
	* @param[in] degree �p�x
	*/
	void Render(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 degree);






private:
	struct MeshData
	{
		ID3D11Buffer* m_VertexBuffer;			//!< @brief ���_�o�b�t�@(Shader���M�p)
		ID3D11Buffer* m_IndexBuffer;			//!< @brief �C���f�b�N�X�o�b�t�@(Shader���M�p)
		std::vector<CustomVertex> m_Vertices;
		std::vector<UINT> m_Indices;
	};

private:
	/**
	* @brief ���b�V������@n
	* �t�@�C�����烁�b�V���𐶐�����
	* @return �쐬�̐��� ����(true)
	* @param[in] file_name �t�@�C����
	*/
	bool LoadFbxFile(std::vector<std::string>& out_material_list, const char* file_path, const char* file_name);

	/**
	* @brief VertexBuffer�쐬@n
	* VertexBuffer���쐬����
	* @return �쐬�̐��� ����(true)
	* @param[in] device DirectX11�O���t�B�N�X�f�o�C�X
	*/
	bool CreateVertexBuffer(ID3D11Device* device);

	/**
	* @brief IndexBuffer�쐬@n
	* IndexBuffer���쐬����
	* @return �쐬�̐��� ����(true)
	* @param[in] device DirectX11�O���t�B�N�X�f�o�C�X
	*/
	bool CreateIndexBuffer(ID3D11Device* device);

	/**
	* @brief InputLayout�쐬@n
	* InputLayout���쐬����
	* @return �쐬�̐��� ����(true)
	* @param[in] device DirectX11�O���t�B�N�X�f�o�C�X
	* @param[in] vertex_shader InputLayout�Ɗ֘A�t���钸�_�V�F�[�_
	*/
	bool CreateInputLayout(ID3D11Device* device, VertexShader* vertex_shader);

	/**
	* @brief ���b�V���f�[�^���쐬����
	* @param[in] node_name �m�[�h�̖��O
	* @param[in] mesh Mesh����邽�߂�Node��Mesh�f�[�^
	*/
	void CreateMesh(FbxMesh* mesh);


	/**
	* @brief ���_�C���f�b�N�X�o�b�t�@��ǂݍ���
	* @param[out] mesh_data �o�b�t�@�ۑ��p
	* @param[in] mesh �o�b�t�@�擾������Mesh�f�[�^
	*/
	void LoadIndices(MeshData& mesh_data, FbxMesh* mesh);

	/**
	* @brief ���_�o�b�t�@��ǂݍ���
	* @param[out] mesh_data �o�b�t�@�ۑ��p
	* @param[in] mesh �o�b�t�@�擾������Mesh�f�[�^
	*/
	void LoadVertices(MeshData& mesh_data, FbxMesh* mesh);

	/**
	* @brief �@���o�b�t�@��ǂݍ���
	* @param[out] mesh_data �o�b�t�@�ۑ��p
	* @param[in] mesh �o�b�t�@�擾������Mesh�f�[�^
	*/
	void LoadNormals(MeshData& mesh_data, FbxMesh* mesh);

	/**
	* @brief ���_�J���[�o�b�t�@��ǂݍ���
	* @param[out] mesh_data �o�b�t�@�ۑ��p
	* @param[in] mesh �o�b�t�@�擾������Mesh�f�[�^
	*/
	void LoadColors(MeshData& mesh_data, FbxMesh* mesh);






private:
	std::vector<MeshData> m_MeshList;
	ID3D11InputLayout* m_InputLayout;									//!< @brief ���̓��C�A�E�g
	PixelShader* m_PixelShader;											//!< @brief PixelShader�ێ��p
	VertexShader* m_VertexShader;										//!< @brief VertexShader�ێ��p
	ID3D11RenderTargetView* m_RenderTargetView;							//!< @brief RenderTargetView��Interface
	ID3D11DepthStencilView* m_DepthStencilView;							//!< @brief DepthStencilView��Interface
	ConstantBuffer m_ConstantBufferData;								//!< @brief ConstantBuffer�f�[�^
	ID3D11Buffer* m_ConstantBuffer;										//!< @brief �萔�o�b�t�@




	IDXGISwapChain* m_SwapChain;										//!< @brief SwapChain��Interface




#endif
};