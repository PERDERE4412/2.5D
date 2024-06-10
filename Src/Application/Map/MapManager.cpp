#include "MapManager.h"

#include "../Scene/SceneManager.h"

#include "../Object/Chara/Player/Player.h"
#include "../Object/Floor/Floor.h"
#include "../Object/Door/Door.h"
#include "../Object/Wall/Wall.h"
#include "../Object/Wall/WallHit.h"

void MapManager::ChangeMap(int _doorId)
{
	// 変更先のマップ番号を取得
	int mapId = m_linkList[_doorId].linkMap;

	// マップ生成
	CreateMap(mapId);
}

void MapManager::CreateMap(int _mapId)
{
	// 壁生成
	std::shared_ptr<Wall> wall = std::make_shared<Wall>();;
	wall->SetWall(m_mapList[_mapId].wall);
	SceneManager::Instance().AddObject(wall);

	// 壁(当たり判定)
	std::shared_ptr<WallHit> wallHit = std::make_shared<WallHit>();
	SceneManager::Instance().AddObject(wallHit);

	// 床
	std::shared_ptr<Floor> floor = std::make_shared<Floor>();
	SceneManager::Instance().AddObject(floor);

	// ドア
	if (m_mapList[_mapId].door & DoorType::D_Left)
	{
		std::shared_ptr<Door> door = std::make_shared<Door>();
		door->SetPlayer(m_player);
		door->Set(m_linkList[_mapId].dorrType["L"], m_doorList["L"].pos, m_doorList["L"].deg);
		SceneManager::Instance().AddObject(door);
	}
	if (m_mapList[_mapId].door & DoorType::D_Up)
	{
		std::shared_ptr<Door> door = std::make_shared<Door>();
		door->SetPlayer(m_player);
		door->Set(m_linkList[_mapId].dorrType["U"],m_doorList["U"].pos, m_doorList["U"].deg);
		SceneManager::Instance().AddObject(door);
	}
	if (m_mapList[_mapId].door & DoorType::D_Right)
	{
		std::shared_ptr<Door> door = std::make_shared<Door>();
		door->SetPlayer(m_player);
		door->Set(m_linkList[_mapId].dorrType["R"],m_doorList["R"].pos, m_doorList["R"].deg);
		SceneManager::Instance().AddObject(door);
	}
	if (m_mapList[_mapId].door & DoorType::D_Down)
	{
		std::shared_ptr<Door> door = std::make_shared<Door>();
		door->SetPlayer(m_player);
		door->Set(m_linkList[_mapId].dorrType["D"],m_doorList["D"].pos, m_doorList["D"].deg);
		SceneManager::Instance().AddObject(door);
	}
}

void MapManager::Init()
{
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
			std::string dorrType;				// ドアタイプ
			std::string doorId;					// ドア番号
			std::string linkId;					// 接続先

			std::getline(iss, mapId, ',');
			std::getline(iss, dorrType, ',');
			std::getline(iss, doorId, ',');
			std::getline(iss, linkId, ',');

			m_linkList[stoi(mapId)][dorrType] = ;
			m_linkList[stoi()]
			m_linkList[stoi(doorId)].linkMap = stoi(linkId);
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
			std::string mapId;					// マップ番号を格納
			std::string wallType;				// 壁タイプを格納
			std::string doorType;				// ドアタイプを格納

			std::getline(iss, mapId, ',');
			std::getline(iss, wallType, ',');
			std::getline(iss, doorType, ',');

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
		}

		ifs.close();
	}

	// ドアデータの読みこみ==================================================
	{
		std::ifstream ifs("Asset/Data/Map/Door.csv"); //ファイル操作用の変数

		std::string lineString; //ファイルから1文字列読み取る変数

		std::getline(ifs, lineString);	// 1行目を飛ばす

		//①ファイルが終わるまでファイルから1文字列ずつ読み取る
		while (std::getline(ifs, lineString))
		{
			std::istringstream iss(lineString); // 文字列を操作する変数にファイルから読み取った文字列を格納
			std::string doorType;				// ドアタイプを格納
			std::string doorPos;				// ドア座標を格納
			std::string doorDeg;				// ドア角度を格納

			std::getline(iss, doorType, ',');
			std::getline(iss, doorPos, ',');
			std::getline(iss, doorDeg, ',');

			// ドア座標
			std::istringstream iss2(doorPos);

			std::string pos;

			std::getline(iss2, pos, '/');
			m_doorList[doorType].pos.x = atof(pos.c_str());
			std::getline(iss2, pos, '/');
			m_doorList[doorType].pos.y = atof(pos.c_str());
			std::getline(iss2, pos, '/');
			m_doorList[doorType].pos.z = atof(pos.c_str());

			// ドア角度
			m_doorList[doorType].deg = stoi(doorDeg);
		}

		ifs.close();
	}
}