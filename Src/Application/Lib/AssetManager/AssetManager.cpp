#include "AssetManager.h"

KdSquarePolygon AssetManager::GetMaterial(std::string _name)
{
	return m_materialList.at(_name);
}

KdModelData AssetManager::GetModel(std::string _name)
{
	return m_modelList.at(_name);
}

KdTexture* AssetManager::GetTex(std::string _name)
{
	return &m_texList.at(_name);
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

	LoadMaterial("playerSwordEffect1", "Asset/Textures/Player/swordEffect1.png");
	SetMaterial("playerSwordEffect1", 7.0f, pivot, 6, 1);

	LoadMaterial("playerSwordEffect2", "Asset/Textures/Player/swordEffect2.png");
	SetMaterial("playerSwordEffect2", 6.0f, pivot, 6, 1);

	LoadMaterial("playerSwordEffect3", "Asset/Textures/Player/swordEffect3.png");
	SetMaterial("playerSwordEffect3", 6.0f, pivot, 3, 1);

	// 敵
	// ウォリアー
	pivot = KdSquarePolygon::PivotType::Center_Bottom;
	LoadMaterial("warriorIdle", "Asset/Textures/Enemy/Warrior/idle.png");
	SetMaterial("warriorIdle", 10.0f, pivot, 8, 1);

	LoadMaterial("warriorRun", "Asset/Textures/Enemy/Warrior/run.png");
	SetMaterial("warriorRun", 10.0f, pivot, 8, 1);

	LoadMaterial("warriorAttack1", "Asset/Textures/Enemy/Warrior/attack1.png");
	SetMaterial("warriorAttack1", 10.0f, pivot, 13, 1);

	LoadMaterial("warriorDeath", "Asset/Textures/Enemy/Warrior/death.png");
	SetMaterial("warriorDeath", 10.0f, pivot, 16, 1);

	// ファイアウィスプ
	LoadMaterial("fireWispIdle", "Asset/Textures/Enemy/FireWisp/idle.png");
	SetMaterial("fireWispIdle", 7.0f, pivot, 4, 1);

	LoadMaterial("fireWispRun", "Asset/Textures/Enemy/FireWisp/run.png");
	SetMaterial("fireWispRun", 7.0f, pivot, 4, 1);

	LoadMaterial("fireWispAttack", "Asset/Textures/Enemy/FireWisp/attack.png");
	SetMaterial("fireWispAttack", 7.0f, pivot, 10, 1);

	LoadMaterial("fireWispDeath", "Asset/Textures/Enemy/FireWisp/death.png");
	SetMaterial("fireWispDeath", 7.0f, pivot, 7, 1);

	LoadMaterial("fireWispBullet", "Asset/Textures/Enemy/FireWisp/bullet.png");
	SetMaterial("fireWispBullet", 4.0f, pivot, 4, 1);

	// スライム
	LoadMaterial("slimeIdle", "Asset/Textures/Enemy/Slime/idle.png");
	SetMaterial("slimeIdle", 4.0f, pivot, 4, 1);

	LoadMaterial("slimeRun", "Asset/Textures/Enemy/Slime/run.png");
	SetMaterial("slimeRun", 4.0f, pivot, 4, 1);

	LoadMaterial("slimeAttack", "Asset/Textures/Enemy/Slime/attack.png");
	SetMaterial("slimeAttack", 4.0f, pivot, 5, 1);

	LoadMaterial("slimeHurt", "Asset/Textures/Enemy/Slime/hurt.png");
	SetMaterial("slimeHurt", 4.0f, pivot, 4, 1);

	LoadMaterial("slimeDeath", "Asset/Textures/Enemy/Slime/death.png");
	SetMaterial("slimeDeath", 4.0f, pivot, 4, 1);

	// リッチ(ボス)
	LoadMaterial("lichIdle", "Asset/Textures/Enemy/Lich/idle.png");
	SetMaterial("lichIdle", 12.0f, pivot, 16, 1);

	LoadMaterial("lichAttack1", "Asset/Textures/Enemy/Lich/attack1.png");
	SetMaterial("lichAttack1", 12.0f, pivot, 16, 1);

	LoadMaterial("lichAttack2", "Asset/Textures/Enemy/Lich/attack2.png");
	SetMaterial("lichAttack2", 12.0f, pivot, 16, 1);

	LoadMaterial("lichAttack3", "Asset/Textures/Enemy/Lich/attack3.png");
	SetMaterial("lichAttack3", 12.0f, pivot, 32, 1);

	LoadMaterial("lichDeath", "Asset/Textures/Enemy/Lich/death.png");
	SetMaterial("lichDeath", 12.0f, pivot, 12, 1);

	LoadMaterial("lichBullet", "Asset/Textures/Enemy/Lich/bullet.png");
	SetMaterial("lichBullet", 3.5f, pivot, 4, 1);

	LoadMaterial("lichBulletExp", "Asset/Textures/Enemy/Lich/bulletExp.png");
	SetMaterial("lichBulletExp", 4.0f, pivot, 4, 1);

	LoadMaterial("lightning", "Asset/Textures/Enemy/Lich/lightning.png");
	SetMaterial("lightning", 12.0f, pivot, 11, 1);

	LoadMaterial("lightExp", "Asset/Textures/Enemy/Lich/lightExp.png");
	SetMaterial("lightExp", 16.0f, pivot, 16, 1);

	// アイテム
	LoadMaterial("drop", "Asset/Textures/drop.png");
	SetMaterial("drop", 2.0f, pivot, 1, 1);

	// 背景
	pivot = KdSquarePolygon::PivotType::Center_Middle;
	LoadMaterial("back", "Asset/Textures/black.png");
	SetMaterial("back", 1.0f, pivot, 1, 1);

	// モデル
	LoadModel("floor", "Asset/Models/floor.gltf");
	LoadModel("wall1", "Asset/Models/wall1.gltf");
	LoadModel("wall2", "Asset/Models/wall2.gltf");
	LoadModel("wall3", "Asset/Models/wall3.gltf");
	LoadModel("wall4", "Asset/Models/wall4.gltf");
	LoadModel("door", "Asset/Models/door.gltf");

	// テクスチャ
	LoadTex("black", "Asset/Textures/black.png");
	LoadTex("gold", "Asset/Textures/gold.png");
	LoadTex("number", "Asset/Textures/number.png");
	LoadTex("levelFrame", "Asset/Textures/levelFrame.png");
	LoadTex("levelBar", "Asset/Textures/levelBar.png");
	LoadTex("hpBar", "Asset/Textures/hpBar.png");
	LoadTex("hpFrame", "Asset/Textures/hpFrame.png");
	LoadTex("slot", "Asset/Textures/slot.png");
	LoadTex("get", "Asset/Textures/get.png");
	LoadTex("enter", "Asset/Textures/enter.png");
	LoadTex("miniMapFrame", "Asset/Textures/miniMapFrame.png");
	LoadTex("miniMap", "Asset/Textures/miniMap.png");
	LoadTex("mapPlayer", "Asset/Textures/mapPlayer.png");
}

void AssetManager::SetMaterial(std::string _name, float _scale, KdSquarePolygon::PivotType _pivot, int _splitX, int _splitY)
{
	m_materialList[_name].SetScale(_scale);
	m_materialList[_name].SetPivot(_pivot);
	m_materialList[_name].SetSplit(_splitX, _splitY);
}