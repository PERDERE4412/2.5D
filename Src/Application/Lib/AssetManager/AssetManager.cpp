#include "AssetManager.h"

KdSquarePolygon* AssetManager::GetMaterial(std::string name)
{
	if (m_materialList.find(name) != m_materialList.end())
	{
		return &m_materialList.at(name);
	}

	return nullptr;
}

void AssetManager::Init()
{

}
