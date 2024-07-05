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

	LoadMaterial("playerHurt", "Asset/Textures/Player/hurt.png");
	SetMaterial("playerHurt", 5.0f, pivot, 4, 1);

	LoadMaterial("playerDeath", "Asset/Textures/Player/death.png");
	SetMaterial("playerDeath", 3.0f, pivot, 4, 1);

	// 敵
	// ウォリアー
	pivot = KdSquarePolygon::PivotType::Center_Bottom;
	LoadMaterial("WarriorIdle", "Asset/Textures/Enemy/Warrior/idle.png");
	SetMaterial("WarriorIdle", 10.0f, pivot, 8, 1);

	LoadMaterial("WarriorRun", "Asset/Textures/Enemy/Warrior/run.png");
	SetMaterial("WarriorRun", 10.0f, pivot, 8, 1);

	LoadMaterial("WarriorAttack", "Asset/Textures/Enemy/Warrior/attack1.png");
	SetMaterial("WarriorAttack", 10.0f, pivot, 13, 1);

	LoadMaterial("WarriorDeath", "Asset/Textures/Enemy/Warrior/death.png");
	SetMaterial("WarriorDeath", 10.0f, pivot, 16, 1);

	// ファイアウィスプ
	LoadMaterial("FireWispIdle", "Asset/Textures/Enemy/FireWisp/idle.png");
	SetMaterial("FireWispIdle", 7.0f, pivot, 4, 1);

	LoadMaterial("FireWispRun", "Asset/Textures/Enemy/FireWisp/run.png");
	SetMaterial("FireWispRun", 7.0f, pivot, 4, 1);

	LoadMaterial("FireWispAttack", "Asset/Textures/Enemy/FireWisp/attack.png");
	SetMaterial("FireWispAttack", 7.0f, pivot, 10, 1);

	LoadMaterial("FireWispDeath", "Asset/Textures/Enemy/FireWisp/death.png");
	SetMaterial("FireWispDeath", 7.0f, pivot, 7, 1);

	LoadMaterial("FireWispBullet", "Asset/Textures/Enemy/FireWisp/bullet.png");
	SetMaterial("FireWispBullet", 4.0f, pivot, 4, 1);

	// スライム
	LoadMaterial("SlimeIdle", "Asset/Textures/Enemy/Slime/idle.png");
	SetMaterial("SlimeIdle", 4.0f, pivot, 4, 1);

	LoadMaterial("SlimeRun", "Asset/Textures/Enemy/Slime/run.png");
	SetMaterial("SlimeRun", 4.0f, pivot, 4, 1);

	LoadMaterial("SlimeAttack", "Asset/Textures/Enemy/Slime/attack.png");
	SetMaterial("SlimeAttack", 4.0f, pivot, 5, 1);

	LoadMaterial("SlimeHurt", "Asset/Textures/Enemy/Slime/hurt.png");
	SetMaterial("SlimeHurt", 4.0f, pivot, 4, 1);

	LoadMaterial("SlimeDeath", "Asset/Textures/Enemy/Slime/death.png");
	SetMaterial("SlimeDeath", 4.0f, pivot, 4, 1);

	// リッチ(ボス)
	LoadMaterial("lichIdle", "Asset/Textures/Enemy/Lich/idle.png");
	SetMaterial("lichIdle", 24.0f, pivot, 16, 1);

	LoadMaterial("lichAttack1", "Asset/Textures/Enemy/Lich/attack1.png");
	SetMaterial("lichAttack1", 24.0f, pivot, 16, 1);

	LoadMaterial("lichAttack2", "Asset/Textures/Enemy/Lich/attack2.png");
	SetMaterial("lichAttack2", 24.0f, pivot, 16, 1);

	LoadMaterial("lichAttack3", "Asset/Textures/Enemy/Lich/attack3.png");
	SetMaterial("lichAttack3", 24.0f, pivot, 32, 1);

	LoadMaterial("lichDeath", "Asset/Textures/Enemy/Lich/death.png");
	SetMaterial("lichDeath", 24.0f, pivot, 12, 1);

	LoadMaterial("lichBullet", "Asset/Textures/Enemy/Lich/bullet.png");
	SetMaterial("lichBullet", 3.5f, pivot, 4, 1);

	LoadMaterial("lichBulletExp", "Asset/Textures/Enemy/Lich/bulletExp.png");
	SetMaterial("lichBulletExp", 4.0f, pivot, 4, 1);

	LoadMaterial("lichSpawn1", "Asset/Textures/Enemy/Lich/spawn1.png");
	SetMaterial("lichSpawn1", 24.0f, pivot, 11, 1);

	LoadMaterial("lichSpawn2", "Asset/Textures/Enemy/Lich/spawn2.png");
	SetMaterial("lichSpawn2", 32.0f, pivot, 16, 1);

	LoadMaterial("lichSpawn3", "Asset/Textures/Enemy/Lich/spawn3.png");
	SetMaterial("lichSpawn3", 5.0f, pivot, 3, 1);

	LoadMaterial("lichSpawn4", "Asset/Textures/Enemy/Lich/spawn4.png");
	SetMaterial("lichSpawn4", 8.0f, pivot, 4, 1);

	LoadMaterial("lichThunder", "Asset/Textures/Enemy/Lich/thunder.png");
	SetMaterial("lichThunder", 16.0f, pivot, 7, 1);

	pivot = KdSquarePolygon::PivotType::Center_Middle;
	LoadMaterial("lichThunderCircle", "Asset/Textures/Enemy/Lich/circle.png");
	SetMaterial("lichThunderCircle", 1.0f, pivot, 1, 1);

	// アイテム
	pivot = KdSquarePolygon::PivotType::Center_Bottom;
	LoadMaterial("drop", "Asset/Textures/drop.png");
	SetMaterial("drop", 2.0f, pivot, 1, 1);

	LoadMaterial("heal", "Asset/Textures/heal.png");
	SetMaterial("heal", 4.5f, pivot, 4, 1);

	// レベルアップ
	LoadMaterial("levelUp", "Asset/Textures/levelUp.png");
	SetMaterial("levelUp",2.5f, pivot, 1, 1);

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
	LoadTex("white", "Asset/Textures/white.png");
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
	LoadTex("bossHpFrame", "Asset/Textures/Enemy/Lich/hpFrame.png");
	LoadTex("bossHpBar", "Asset/Textures/Enemy/Lich/hpBar.png");
	LoadTex("potion", "Asset/Textures/potion.png");
	LoadTex("GetPotion", "Asset/Textures/getPotion.png");
	LoadTex("clear", "Asset/Textures/clear.png");
	LoadTex("book", "Asset/Textures/book.png");
	LoadTex("plus", "Asset/Textures/plus.png");
	LoadTex("minus", "Asset/Textures/minus.png");
	LoadTex("set", "Asset/Textures/set.png");
	LoadTex("ClickStart", "Asset/Textures/gameStart.png");
	LoadTex("title", "Asset/Textures/title.png");
	LoadTex("level", "Asset/Textures/level.png");
	LoadTex("hurt", "Asset/Textures/hurt.png");
}

void AssetManager::SetMaterial(std::string _name, float _scale, KdSquarePolygon::PivotType _pivot, int _splitX, int _splitY)
{
	m_materialList[_name].SetScale(_scale);
	m_materialList[_name].SetPivot(_pivot);
	m_materialList[_name].SetSplit(_splitX, _splitY);
}