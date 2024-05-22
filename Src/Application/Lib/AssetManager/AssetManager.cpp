#include "AssetManager.h"

KdSquarePolygon AssetManager::GetMaterial(std::string name)
{
	if (m_materialList.find(name) != m_materialList.end())
	{
		return m_materialList.at(name);
	}
}

void AssetManager::Init()
{
	KdSquarePolygon::PivotType pivot = KdSquarePolygon::PivotType::Center_Bottom;
	LoadMaterial("playerIdol", "Asset/Textures/player/idol.png");
	SetMaterial("playerIdol", 2.0f,pivot, 4, 1);

	LoadMaterial("playerDash", "Asset/Textures/player/dash.png");
	SetMaterial("playerDash", 2.0f, pivot, 7, 1);
}

void AssetManager::SetMaterial(std::string _name, float _scale, KdSquarePolygon::PivotType _pivot, int _splitX, int _splitY)
{
	m_materialList[_name].SetScale(_scale);
	m_materialList[_name].SetPivot(_pivot);
	m_materialList[_name].SetSplit(_splitX, _splitY);
}