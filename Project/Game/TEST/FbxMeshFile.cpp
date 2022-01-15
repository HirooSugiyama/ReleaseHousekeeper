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

	// D3Dデバイスとデバイスコンテキストの取得
	auto d3ddevice = pDR->GetD3DDevice();



	m_SwapChain = pDR->GetSwapChain();



	m_DepthStencilView = pDR->GetDepthStencilView();

	



	{
		/*
			Constantバッファー作成
				コンスタントバッファーはCPU側のデータを
				まとめてGPU側に送信するためのバッファー

				バッファーには座標変換行列などを設定する
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
		// RenderTargetViewの対象となるBufferの取得
		ID3D11Texture2D* back_buffer = nullptr;
		if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer)))
		{
			return false;
		}

		// BufferからRenderTargetViewの作成
		if (FAILED(d3ddevice->CreateRenderTargetView(back_buffer, NULL, &m_RenderTargetView)))
		{
			return false;
		}

		// Targetの取得終わったのでBufferを解放
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
	// D3Dデバイスとデバイスコンテキストの取得
	auto device = pDR->GetD3DDevice();
	auto context = pDR->GetD3DDeviceContext();
	{
		// プリミティブの形状を指定
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// VerteXShader、PixelShaderを設定
		context->VSSetShader(
			m_VertexShader->GetShaderInterface(),	// 使用するVertexShder
			/*
				ClassInstanceのポインタを設定する
					これはShader作成時のID3D11ClassLinkageを使用した場合に
					用いる項目なので今回はnullptrを指定する
			*/
			nullptr,
			0);									// ClassInstanceの数
		context->PSSetShader(m_PixelShader->GetShaderInterface(), nullptr, 0);

		// (OutputManger)RnderTagetの指定
		context->OMSetRenderTargets(
			1,							// 使用するViewの数
			&m_RenderTargetView,		// 使用するRenderTargetView
			m_DepthStencilView);		// 使用するDepthStencilView
	}













	UINT strides = sizeof(CustomVertex);
	UINT offsets = 0;

	for (auto& mesh : m_MeshList)
	{
		// インデックスバッファの数 = マテリアルの数だけメッシュを描画する
		// IA(InputAssemblerStage)に入力レイアウトを設定する
		context->IASetInputLayout(m_InputLayout);
		// IAに設定する頂点バッファの指定
		context->IASetVertexBuffers(
				0,								// バッファ送信のスロット番号
				1,								// バッファの数
				&mesh.m_VertexBuffer,	// 頂点バッファ
				&strides,						// バッファに使用している構造体のサイズ
				&offsets);						// 開始オフセット

		context->IASetIndexBuffer(
				mesh.m_IndexBuffer,
				DXGI_FORMAT_R32_UINT,
				0);

			// ワールドマトリクス設定
			DirectX::XMMATRIX world_matrix;
			DirectX::XMMATRIX translate = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
			DirectX::XMMATRIX rotate_x = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(degree.x));
			DirectX::XMMATRIX rotate_y = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(degree.y));
			DirectX::XMMATRIX rotate_z = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(degree.z));
			DirectX::XMMATRIX scale_mat = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
			world_matrix = scale_mat * rotate_x * rotate_y * rotate_z * translate;

			// ワールドマトリクスをコンスタントバッファに設定
			XMStoreFloat4x4(&m_ConstantBufferData.World, XMMatrixTranspose(world_matrix));

			// コンスタントバッファ更新
			context->UpdateSubresource(m_ConstantBuffer, 0, NULL, &m_ConstantBufferData, 0, 0);

			ID3D11Buffer* constant_buffer = m_ConstantBuffer;
			// コンテキストにコンスタントバッファを設定
			context->VSSetConstantBuffers(0, 1, &constant_buffer);
			context->PSSetConstantBuffers(0, 1, &constant_buffer);

			// 描画
			context->DrawIndexed(
				(UINT)mesh.m_Indices.size(),	// 頂点数
				0,								// オフセット
				0);								// 開始頂点のインデックス
	}
}












void FbxMeshFile::LoadVertices(MeshData& mesh_data, FbxMesh* mesh)
{
	// 頂点バッファの取得
	FbxVector4* vertices = mesh->GetControlPoints();
	// インデックスバッファの取得
	int* indices = mesh->GetPolygonVertices();
	// 頂点座標の数の取得
	int polygon_vertex_count = mesh->GetPolygonVertexCount();
	// GetPolygonVertexCount => 頂点数
	for (int i = 0; i < polygon_vertex_count; i++)
	{
		CustomVertex vertex;
		// インデックスバッファから頂点番号を取得
		int index = indices[i];

		// 頂点座標リストから座標を取得する
		vertex.Position.x = (float)-vertices[index][0];
		vertex.Position.y = (float)vertices[index][1];
		vertex.Position.z = (float)vertices[index][2];

		// 追加
		mesh_data.m_Vertices.push_back(vertex);
	}
}

void FbxMeshFile::LoadIndices(MeshData& mesh_data, FbxMesh* mesh)
{
	// ポリゴン数の取得
	int polygon_count = mesh->GetPolygonCount();

	// ポリゴンの数だけ連番として保存する
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
	// 法線リストの取得
	mesh->GetPolygonVertexNormals(normals);

	// 法線設定
	for (int i = 0; i < normals.Size(); i++)
	{
		mesh_data.m_Vertices[i].Normal.x = (float)-normals[i][0];
		mesh_data.m_Vertices[i].Normal.y = (float)normals[i][1];
		mesh_data.m_Vertices[i].Normal.z = (float)normals[i][2];
	}
}

void FbxMeshFile::LoadColors(MeshData& mesh_data, FbxMesh* mesh)
{
	// 頂点カラーデータの数を確認
	int color_count = mesh->GetElementVertexColorCount();
	if (color_count == 0)
	{
		return;
	}
	
	// 頂点カラーデータの取得
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
			// 頂点カラーバッファ取得
			FbxLayerElementArrayTemplate<FbxColor>& colors = vertex_colors->GetDirectArray();
			// 頂点カラーインデックスバッファ取得
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
	// FbxManager作成
	FbxManager* fbx_manager = fbxsdk::FbxManager::Create();
	if (fbx_manager == nullptr)
	{
		return false;
	}
	
	// FbxImporter作成
	FbxImporter* fbx_importer = FbxImporter::Create(fbx_manager, "");
	if (fbx_importer == nullptr)
	{
		fbx_manager->Destroy();
		return false;
	}
	
	// FbxScene作成
	FbxScene* fbx_scene = FbxScene::Create(fbx_manager, "");
	if (fbx_scene == nullptr)
	{
		fbx_importer->Destroy();
		fbx_manager->Destroy();
		return false;
	}

	// Fileを初期化
	fbx_importer->Initialize(file_name);
	// sceneにインポート
	fbx_importer->Import(fbx_scene);

	FbxGeometryConverter converter(fbx_manager);
	// ポリゴンを三角形にする
	converter.Triangulate(fbx_scene, true);

	// FbxMeshの数を取得
	int mesh_num = fbx_scene->GetSrcObjectCount<FbxMesh>();

	for (int i = 0; i < mesh_num; i++)
	{
		// Mesh作成
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
		//頂点バッファ作成
		D3D11_BUFFER_DESC buffer_desc;
		buffer_desc.ByteWidth = sizeof(CustomVertex) * (UINT)mesh.m_Vertices.size();	// バッファのサイズ
		buffer_desc.Usage = D3D11_USAGE_DEFAULT;			// 使用方法
		buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// BIND設定
		buffer_desc.CPUAccessFlags = 0;						// リソースへのCPUのアクセス権限についての設定
		buffer_desc.MiscFlags = 0;							// リソースオプションのフラグ
		buffer_desc.StructureByteStride = 0;				// 構造体のサイズ

		D3D11_SUBRESOURCE_DATA sub_resource;
		sub_resource.pSysMem = &mesh.m_Vertices[0];	// バッファの中身の設定
		sub_resource.SysMemPitch = 0;				// textureデータを使用する際に使用するメンバ
		sub_resource.SysMemSlicePitch = 0;			// textureデータを使用する際に使用するメンバ

		// バッファ作成
		if (FAILED(device->CreateBuffer(
			&buffer_desc,								// バッファ情報
			&sub_resource,								// リソース情報
			&mesh.m_VertexBuffer)))	// 作成されたバッファの格納先
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
		//頂点バッファ作成
		D3D11_BUFFER_DESC buffer_desc;
		buffer_desc.ByteWidth = sizeof(UINT) * (UINT)mesh.m_Indices.size();	// バッファのサイズ
		buffer_desc.Usage = D3D11_USAGE_DEFAULT;							// 使用方法
		buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;					// BIND設定
		buffer_desc.CPUAccessFlags = 0;										// リソースへのCPUのアクセス権限についての設定
		buffer_desc.MiscFlags = 0;											// リソースオプションのフラグ
		buffer_desc.StructureByteStride = 0;								// 構造体のサイズ

		D3D11_SUBRESOURCE_DATA sub_resource;
		sub_resource.pSysMem = &mesh.m_Indices[0];							// バッファの中身の設定
		sub_resource.SysMemPitch = 0;										// textureデータを使用する際に使用するメンバ
		sub_resource.SysMemSlicePitch = 0;									// textureデータを使用する際に使用するメンバ

		// バッファ作成
		if (FAILED(device->CreateBuffer(
			&buffer_desc,						// バッファ情報
			&sub_resource,						// リソース情報
			&mesh.m_IndexBuffer)))		// 作成されたバッファの格納先
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

	//頂点レイアウト作成
	if (FAILED(device->CreateInputLayout(
		vertex_desc,				// レイアウト設定
		ARRAYSIZE(vertex_desc),		// 配列サイズ
		vertex_shader->GetData(),	// レイアウトと関連付ける頂点シェーダのデータ
		vertex_shader->GetSize(),	// レイアウトと関連付ける頂点シェーダのサイズ
		&m_InputLayout)))			// 作成された頂点レイアウトの格納先
	{
		return false;
	}

	return true;
}

