#include "Wall.h"

#include "../../Lib/AssetManager/AssetManager.h"

void Wall::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model);
}

void Wall::Init()
{
	m_model=AssetManager::Instance().GetModel("wall");
}
