#include "MapManager.h"

#include "../Scene/SceneManager.h"

#include "../Object/Chara/Player/Player.h"
#include "../Object/UI/MiniMap/MiniMap.h"
#include "../Object/Map/Floor/Floor.h"
#include "../Object/Map/Door/Door.h"
#include "../Object/Map/Wall/Wall.h"
#include "../Object/Map/Wall/WallHit.h"
#include "../Object/Chara/Enemy/EnemyManager.h"
#include "../Movie/Movie.h"

void MapManager::ChangeMap(std::string _type)
{
	// リンク先のマップ番号取得
	int mapId = m_linkMapList[m_nowMapId][_type];

	// マップ生成
	if (m_nowMapId != mapId)
	{
		CreateMap(mapId);
	}
}

void MapManager::ChangeMap()
{
	//CreateMap(m_nowMapId);
	CreateMap(8);
}

void MapManager::SetPlayerPos(std::string _type)
{
	if (!m_player.expired())
	{
		Math::Vector3 pos;
		if (_type == "L")pos = m_playerPosList["R"];
		if (_type == "U")pos = m_playerPosList["D"];
		if (_type == "R")pos = m_playerPosList["L"];
		if (_type == "D")pos = m_playerPosList["U"];
		m_player.lock()->SetPos(pos);
	}
}

void MapManager::CreateMap(int _mapId)
{
	m_nowMapId = _mapId;

	// ボス部屋ならムービー起動
	if (m_mapList[_mapId].isBoss)Movie::Instance().BootMovie();

	// マップのオブジェクトをクリア
	if (!m_objList.empty())
	{
		for (std::shared_ptr<KdGameObject> obj : m_objList)
		{
			obj->Expired();
		}
	}

	// 壁生成
	std::shared_ptr<Wall> wall = std::make_shared<Wall>();;
	wall->SetWall(m_mapList[_mapId].wall);
	SceneManager::Instance().AddObject(wall);
	m_objList.push_back(wall);

	// 壁(当たり判定)
	std::shared_ptr<WallHit> wallHit = std::make_shared<WallHit>();
	SceneManager::Instance().AddObject(wallHit);
	m_objList.push_back(wallHit);

	// 床
	std::shared_ptr<Floor> floor = std::make_shared<Floor>();
	SceneManager::Instance().AddObject(floor);
	m_objList.push_back(floor);

	// ドア
	if (m_mapList[_mapId].door & DoorType::D_Left)
	{
		std::shared_ptr<Door> door = std::make_shared<Door>();
		door->SetPlayer(m_player);
		door->Set("L");
		SceneManager::Instance().AddObject(door);
		m_objList.push_back(door);
	}
	if (m_mapList[_mapId].door & DoorType::D_Up)
	{
		std::shared_ptr<Door> door = std::make_shared<Door>();
		door->SetPlayer(m_player);
		door->Set("U");
		SceneManager::Instance().AddObject(door);
		m_objList.push_back(door);
	}
	if (m_mapList[_mapId].door & DoorType::D_Right)
	{
		std::shared_ptr<Door> door = std::make_shared<Door>();
		door->SetPlayer(m_player);
		door->Set("R");
		SceneManager::Instance().AddObject(door);
		m_objList.push_back(door);
	}
	if (m_mapList[_mapId].door & DoorType::D_Down)
	{
		std::shared_ptr<Door> door = std::make_shared<Door>();
		door->SetPlayer(m_player);
		door->Set("D");
		SceneManager::Instance().AddObject(door);
		m_objList.push_back(door);
	}

	// 敵生成
	if (!Movie::Instance().GetMovie())
	{
		for (EnemyData enemy : m_enemyList[_mapId])
		{
			EnemyManager::Instance().Spawn(enemy.name, enemy.pos);
		}
	}

	// ミニマップ切り替え
	if (!m_miniMap.expired())
	{
		m_miniMap.lock()->Set(m_nowMapId);
	}
}

void MapManager::Init()
{
	m_nowMapId = 1;

	// 接続先データの読み込み==================================================
	{
		std::ifstream ifs("Asset/Data/Map/Link.csv"); //ファイル操作用の変数

		std::string lineString; //ファイルから1文字列読み取る変数

		std::getline(ifs, lineString);	// 1行目を飛ばす

		//①ファイルが終わるまでファイルから1文字列ずつ読み取る
		while (std::getline(ifs, lineString))
		{
			std::istringstream iss(lineString); // 文字列を操作する変数にファイルから読み取った文字列を格納
			std::string mapId;					// マップ番号
			std::string doorType;				// ドアタイプ
			std::string linkId;					// 接続先

			std::getline(iss, mapId, ',');
			std::getline(iss, doorType, ',');
			std::getline(iss, linkId, ',');

			m_linkMapList[stoi(mapId)][doorType] = stoi(linkId);
		}

		ifs.close();
	}

	// マップデータの読みこみ==================================================
	{
		std::ifstream ifs("Asset/Data/Map/Map.csv"); //ファイル操作用の変数

		std::string lineString; //ファイルから1文字列読み取る変数

		std::getline(ifs, lineString);	// 1行目を飛ばす

		//①ファイルが終わるまでファイルから1文字列ずつ読み取る
		while (std::getline(ifs, lineString))
		{
			std::istringstream iss(lineString); // 文字列を操作する変数にファイルから読み取った文字列を格納
			std::string mapId;					// マップ番号
			std::string wallType;				// 壁タイプ
			std::string doorType;				// ドアタイプ
			std::string isBoss;					// ボス部屋フラグ

			std::getline(iss, mapId, ',');
			std::getline(iss, wallType, ',');
			std::getline(iss, doorType, ',');
			std::getline(iss, isBoss, ',');

			// 壁タイプ設定
			if (wallType == "None")m_mapList[stoi(mapId)].wall |= WallType::W_None;
			if (wallType == "L")m_mapList[stoi(mapId)].wall |= WallType::W_Left;
			if (wallType == "R")m_mapList[stoi(mapId)].wall |= WallType::W_Up;
			if (wallType == "LR")m_mapList[stoi(mapId)].wall |= (WallType::W_Left | WallType::W_Up);

			// ドアタイプ設定
			std::string type;
			std::istringstream iss2(doorType);

			while (std::getline(iss2, type, '/'))
			{
				if (type == "L")m_mapList[stoi(mapId)].door |= DoorType::D_Left;
				if (type == "U")m_mapList[stoi(mapId)].door |= DoorType::D_Up;
				if (type == "R")m_mapList[stoi(mapId)].door |= DoorType::D_Right;
				if (type == "D")m_mapList[stoi(mapId)].door |= DoorType::D_Down;
			}

			// ボス部屋設定
			if (isBoss == "TRUE")m_mapList[stoi(mapId)].isBoss = true;
			if (isBoss == "FALSE")m_mapList[stoi(mapId)].isBoss = false;
		}

		ifs.close();
	}

	// エネミーデータの読みこみ==================================================
	{
		std::ifstream ifs("Asset/Data/Map/Enemy.csv"); //ファイル操作用の変数

		std::string lineString; //ファイルから1文字列読み取る変数

		std::getline(ifs, lineString);	// 1行目を飛ばす

		//①ファイルが終わるまでファイルから1文字列ずつ読み取る
		while (std::getline(ifs, lineString))
		{
			std::istringstream iss(lineString); // 文字列を操作する変数にファイルから読み取った文字列を格納
			std::string mapId;					// マップ番号を格納
			std::string enemyName;				// 名前を格納
			std::string enemyPos;				// ドアタイプを格納

			std::getline(iss, mapId, ',');
			std::getline(iss, enemyName, ',');
			std::getline(iss, enemyPos, ',');

			EnemyData enemy;

			// 名前設定
			enemy.name = enemyName;

			// 座標設定
			std::string pos;
			std::istringstream iss2(enemyPos);

			std::getline(iss2, pos, '/');
			enemy.pos.x = (float)atof(pos.c_str());
			std::getline(iss2, pos, '/');
			enemy.pos.y = (float)atof(pos.c_str());
			std::getline(iss2, pos, '/');
			enemy.pos.z = (float)atof(pos.c_str());

			m_enemyList[stoi(mapId)].push_back(enemy);
		}

		ifs.close();
	}

	// プレイヤーの座標リスト
	m_playerPosList["L"] = { -17,0,53 };
	m_playerPosList["U"] = { 17,0,53 };
	m_playerPosList["R"] = { 17,0,20 };
	m_playerPosList["D"] = { -17,0,20 };
}