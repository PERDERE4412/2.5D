#include "Map.h"

void Map::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model);
}

void Map::Init()
{
	m_objType = ObjType::none;

	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Data/LessonData/Terrain/Terrain.gltf");
}
