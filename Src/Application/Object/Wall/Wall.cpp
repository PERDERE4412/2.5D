#include "Wall.h"

#include "../../Lib/AssetManager/AssetManager.h"
#include "../../Map/MapManager.h"

void Wall::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model);
}

void Wall::SetWall(int _type)
{
	switch (_type)
	{
	case MapManager::WallType::W_None:
		m_model = AssetManager::Instance().GetModel("wall1");
		break;
	case MapManager::WallType::W_Left:
		m_model = AssetManager::Instance().GetModel("wall2");
		break;
	case MapManager::WallType::W_Up:
		m_model = AssetManager::Instance().GetModel("wall3");
		break;
	case MapManager::WallType::W_Left | MapManager::WallType::W_Up:
		m_model = AssetManager::Instance().GetModel("wall4");
		break;
	}
}

void Wall::Init()
{
}
