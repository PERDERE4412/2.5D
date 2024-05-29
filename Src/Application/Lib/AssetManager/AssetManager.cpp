#include "AssetManager.h"

KdSquarePolygon AssetManager::GetMaterial(std::string _name)
{
	if (m_materialList.find(_name) != m_materialList.end())
	{
		return m_materialList.at(_name);
	}
}

KdModelData AssetManager::GetModel(std::string _name)
{
	if (m_modelList.find(_name) != m_modelList.end())
	{
		return m_modelList.at(_name);
	}
}

KdTexture* AssetManager::GetTex(std::string _name)
{
	if (m_texList.find(_name) != m_texList.end())
	{
		return &m_texList.at(_name);
	}
}

void AssetManager::Init()
{
	// ポリゴン
	// 主人公
	KdSquarePolygon::PivotType pivot = KdSquarePolygon::PivotType::Center_Bottom;
	LoadMaterial("playerIdol", "Asset/Textures/Player/idle.png");
	SetMaterial("playerIdol", 2.8f, pivot, 3, 1);

	LoadMaterial("playerRun", "Asset/Textures/Player/run.png");
	SetMaterial("playerRun", 2.8f, pivot, 10, 1);

	LoadMaterial("playerRoll", "Asset/Textures/Player/roll.png");
	SetMaterial("playerRoll", 3.0f, pivot, 11, 1);

	LoadMaterial("playerAttack1", "Asset/Textures/Player/attack1.png");
	SetMaterial("playerAttack1", 4.0f, pivot, 10, 1);

	LoadMaterial("playerAttack2", "Asset/Textures/Player/attack2.png");
	SetMaterial("playerAttack2", 4.0f, pivot, 10, 1);

	LoadMaterial("playerAttack3", "Asset/Textures/Player/attack3.png");
	SetMaterial("playerAttack3", 4.0f, pivot, 11, 1);

	pivot = KdSquarePolygon::PivotType::Center_Middle;
	LoadMaterial("back", "Asset/Textures/back.png");
	SetMaterial("back", 1.0f, pivot, 1, 1);

	// モデル
	LoadModel("map", "Asset/Models/floor.gltf");
	LoadModel("wall", "Asset/Models/wall.gltf");

	// テクスチャ
	LoadTex("gold", "Asset/Textures/gold.png");
	LoadTex("number", "Asset/Textures/number.png");
	LoadTex("levelFrame", "Asset/Textures/levelFrame.png");
	LoadTex("levelBar", "Asset/Textures/levelBar.png");
}

void AssetManager::SetMaterial(std::string _name, float _scale, KdSquarePolygon::PivotType _pivot, int _splitX, int _splitY)
{
	m_materialList[_name].SetScale(_scale);
	m_materialList[_name].SetPivot(_pivot);
	m_materialList[_name].SetSplit(_splitX, _splitY);
}