/*
FBX�}�l�[�W���[
�쐬�ҁF���R
�쐬���F2021/06/24
*/



//class FBXManager
//{
//private:
//
//	// FBXManager�쐬
//	FBXManager* fbx_manager = FBXManager::Create();
//	if (fbx_manager == nullptr)
//	{
//		// �쐬���s
//		return 0;
//	}
//
//
//
//public:
//
//	// FbxImporter�쐬
//	FbxImporter* fbx_importer = FbxImporter::Create(fbx_manager, "ImportTest");
//	if (fbx_importer == nullptr)
//	{
//		fbx_manager->Destroy();
//
//		// �쐬���s
//		return 0;
//	}
//
//
//	// FbxScene�쐬
//		FbxScene * fbx_scene = FbxScene::Create(fbx_manager, "SceneTest");
//	if (fbx_scene == nullptr)
//	{
//		fbx_importer->Destroy();
//		fbx_manager->Destroy();
//
//		// �쐬���s
//		return 0;
//	}
//
//
//
//	// �t�@�C��������������
//	if (fbx_importer->Initialize("Box.fbx") == false)
//	{
//		fbx_importer->Destroy();
//		fbx_scene->Destroy();
//		fbx_manager->Destroy();
//
//		// ���������s
//		return 0;
//	}
//
//
//	// �C���|�[�g
//	if (fbx_importer->Import(fbx_scene) == false)
//	{
//		fbx_importer->Destroy();
//		fbx_scene->Destroy();
//		fbx_manager->Destroy();
//
//		// �C���|�[�g���s
//		return 0;
//	}
//
//
//
//	if (fbx_importer != nullptr)
//	{
//		fbx_importer->Destroy();
//	}
//
//	if (fbx_scene != nullptr)
//	{
//		fbx_scene->Destroy();
//	}
//
//	if (fbx_manager != nullptr)
//	{
//		fbx_manager->Destroy();
//	}
//
//
//
//
//};