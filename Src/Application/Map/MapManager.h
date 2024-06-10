#pragma once

class Player;

class MapManager
{
public:

	void ChangeMap(int _doorId);	// マップ変更

	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }

	enum WallType
	{
		W_None		= 1 << 0,
		W_Left		= 1 << 1,
		W_Up		= 1 << 2
	};

private:

	void Init();				// 初期化

	void CreateMap(int _mapId);	// マップ生成

	std::weak_ptr<Player> m_player;

	// マップデータの構造体
	enum DoorType
	{
		D_Left =	1 << 0,
		D_Up =		1 << 1,
		D_Right =	1 << 2,
		D_Down =	1 << 3
	};

	struct DoorData
	{
		Math::Vector3 pos;	// ドア座標
		int deg;			// 角度
	};

	struct MapData
	{
		UINT door;			// ドア
		UINT wall;			// 壁
	};

	std::unordered_map<std::string, DoorData> m_doorList;	// ドアデータリスト
	std::unordered_map<int, MapData> m_mapList;				// マップリスト

	// 接続先データの構造体
	struct LinkData
	{
		std::unordered_map<std::string,UINT> dorrType;
		int linkMap;	// 接続先のマップ番号
	};

	std::unordered_map<int,std::unordered_map<std::string,int>> m_linkList;		// 接続先リスト

private:

	MapManager() { Init(); }	// コンストラクタ
	~MapManager() {}			// デストラクタ

public:

	// シングルトンパターン
	static MapManager& Instance()
	{
		static MapManager instance;
		return instance;
	}
};