#include "Map.h"

void Map::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model);
}

void Map::Init()
{
	m_objType = ObjType::Map;
	
	m_model.Load("Asset/Models/floor.gltf");
}
