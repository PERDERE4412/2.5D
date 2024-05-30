#include "Map.h"

#include "../../Lib/AssetManager/AssetManager.h"

void Map::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model);
}

void Map::Init()
{
	m_model = AssetManager::Instance().GetModel("map");
}
