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
	* @brief モデル読み込み@n
	* モデルデータを読み込む
	* @return 作成の成否 成功(true)
	* @param[in] device デバイス
	* @param[in] vertex_shader モデルと関連付けるVertexShader
	*/
	bool Load(const char* file_name, ID3D11Device* device, VertexShader* vertex_shader);

	/**
	* @brief モデル描画関数@n
	* 指定された情報でモデルを描画する
	* @return 作成の成否 成功(true)
	* @param[in] graphics 描画管理クラス
	* @param[in] pos 描画座標
	* @param[in] scale 拡縮率
	* @param[in] degree 角度
	*/
	void Render(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 degree);






private:
	struct MeshData
	{
		ID3D11Buffer* m_VertexBuffer;			//!< @brief 頂点バッファ(Shader送信用)
		ID3D11Buffer* m_IndexBuffer;			//!< @brief インデックスバッファ(Shader送信用)
		std::vector<CustomVertex> m_Vertices;
		std::vector<UINT> m_Indices;
	};

private:
	/**
	* @brief メッシュ生成@n
	* ファイルからメッシュを生成する
	* @return 作成の成否 成功(true)
	* @param[in] file_name ファイル名
	*/
	bool LoadFbxFile(std::vector<std::string>& out_material_list, const char* file_path, const char* file_name);

	/**
	* @brief VertexBuffer作成@n
	* VertexBufferを作成する
	* @return 作成の成否 成功(true)
	* @param[in] device DirectX11グラフィクスデバイス
	*/
	bool CreateVertexBuffer(ID3D11Device* device);

	/**
	* @brief IndexBuffer作成@n
	* IndexBufferを作成する
	* @return 作成の成否 成功(true)
	* @param[in] device DirectX11グラフィクスデバイス
	*/
	bool CreateIndexBuffer(ID3D11Device* device);

	/**
	* @brief InputLayout作成@n
	* InputLayoutを作成する
	* @return 作成の成否 成功(true)
	* @param[in] device DirectX11グラフィクスデバイス
	* @param[in] vertex_shader InputLayoutと関連付ける頂点シェーダ
	*/
	bool CreateInputLayout(ID3D11Device* device, VertexShader* vertex_shader);

	/**
	* @brief メッシュデータを作成する
	* @param[in] node_name ノードの名前
	* @param[in] mesh Meshを作るためのNodeのMeshデータ
	*/
	void CreateMesh(FbxMesh* mesh);


	/**
	* @brief 頂点インデックスバッファを読み込む
	* @param[out] mesh_data バッファ保存用
	* @param[in] mesh バッファ取得をするMeshデータ
	*/
	void LoadIndices(MeshData& mesh_data, FbxMesh* mesh);

	/**
	* @brief 頂点バッファを読み込む
	* @param[out] mesh_data バッファ保存用
	* @param[in] mesh バッファ取得をするMeshデータ
	*/
	void LoadVertices(MeshData& mesh_data, FbxMesh* mesh);

	/**
	* @brief 法線バッファを読み込む
	* @param[out] mesh_data バッファ保存用
	* @param[in] mesh バッファ取得をするMeshデータ
	*/
	void LoadNormals(MeshData& mesh_data, FbxMesh* mesh);

	/**
	* @brief 頂点カラーバッファを読み込む
	* @param[out] mesh_data バッファ保存用
	* @param[in] mesh バッファ取得をするMeshデータ
	*/
	void LoadColors(MeshData& mesh_data, FbxMesh* mesh);






private:
	std::vector<MeshData> m_MeshList;
	ID3D11InputLayout* m_InputLayout;									//!< @brief 入力レイアウト
	PixelShader* m_PixelShader;											//!< @brief PixelShader保持用
	VertexShader* m_VertexShader;										//!< @brief VertexShader保持用
	ID3D11RenderTargetView* m_RenderTargetView;							//!< @brief RenderTargetViewのInterface
	ID3D11DepthStencilView* m_DepthStencilView;							//!< @brief DepthStencilViewのInterface
	ConstantBuffer m_ConstantBufferData;								//!< @brief ConstantBufferデータ
	ID3D11Buffer* m_ConstantBuffer;										//!< @brief 定数バッファ




	IDXGISwapChain* m_SwapChain;										//!< @brief SwapChainのInterface




#endif
};