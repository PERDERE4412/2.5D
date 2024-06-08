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
	LoadMaterial("playerIdle", "Asset/Textures/Player/idle.png");
	SetMaterial("playerIdle", 2.8f, pivot, 3, 1);

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

	// 敵
	LoadMaterial("enemyIdle", "Asset/Textures/Enemy/idle.png");
	SetMaterial("enemyIdle", 10.0f, pivot, 8, 1);

	LoadMaterial("enemyRun", "Asset/Textures/Enemy/run.png");
	SetMaterial("enemyRun", 10.0f, pivot, 8, 1);

	LoadMaterial("enemyAttack1", "Asset/Textures/Enemy/attack1.png");
	SetMaterial("enemyAttack1", 10.0f, pivot, 13, 1);

	LoadMaterial("enemyDeath", "Asset/Textures/Enemy/death.png");
	SetMaterial("enemyDeath", 10.0f, pivot, 16, 1);
	
	// アイテム
	LoadMaterial("drop", "Asset/Textures/drop.png");
	SetMaterial("drop", 2.0f, pivot, 1, 1);

	// 背景
	pivot = KdSquarePolygon::PivotType::Center_Middle;
	LoadMaterial("back", "Asset/Textures/back.png");
	SetMaterial("back", 1.0f, pivot, 1, 1);
	
	// モデル
	LoadModel("map", "Asset/Models/floor.gltf");
	LoadModel("wall", "Asset/Models/wall.gltf");
	LoadModel("door", "Asset/Models/door.gltf");

	// テクスチャ
	LoadTex("gold", "Asset/Textures/gold.png");
	LoadTex("number", "Asset/Textures/number.png");
	LoadTex("levelFrame", "Asset/Textures/levelFrame.png");
	LoadTex("levelBar", "Asset/Textures/levelBar.png");
	LoadTex("hpBar", "Asset/Textures/hpBar.png");
	LoadTex("hpFrame", "Asset/Textures/hpFrame.png");
	LoadTex("slot", "Asset/Textures/slot.png");
	LoadTex("get", "Asset/Textures/get.png");
	LoadTex("enter", "Asset/Textures/enter.png");
}

void AssetManager::SetMaterial(std::string _name, float _scale, KdSquarePolygon::PivotType _pivot, int _splitX, int _splitY)
{
	m_materialList[_name].SetScale(_scale);
	m_materialList[_name].SetPivot(_pivot);
	m_materialList[_name].SetSplit(_splitX, _splitY);
}