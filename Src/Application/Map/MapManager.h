#pragma once

class Player;

class MapManager
{
public:

	void ChangeMap(std::string _type);	// マップ変更
	void ChangeMap();

	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }

	void SetPlayerPos(std::string _type);

	void AddObject(std::shared_ptr<KdGameObject> _obj) { m_objList.push_back(_obj); }

	enum WallType
	{
		W_None = 1 << 0,
		W_Left = 1 << 1,
		W_Up = 1 << 2
	};

private:

	void Init();					// 初期化

	void CreateMap(int _mapId);		// マップ生成

	std::weak_ptr<Player> m_player;	// プレイヤーのWeakポインタ

	std::vector<std::shared_ptr<KdGameObject>> m_objList;	// マップのオブジェクト一覧

	int m_nowMapId;					// 現在のマップ番号					

	// マップデータの構造体
	enum DoorType
	{
		D_Left = 1 << 0,
		D_Up = 1 << 1,
		D_Right = 1 << 2,
		D_Down = 1 << 3
	};

	struct MapData
	{
		UINT door;		// ドアタイプ
		UINT wall;		// 壁タイプ
	};
	
	std::unordered_map<int, MapData> m_mapList;				// マップリスト

	std::unordered_map<int, std::unordered_map<std::string, int>> m_linkMapList;		// 接続先リスト

	// プレイヤーの移動座標
	std::unordered_map<std::string, Math::Vector3> m_playerPosList;

	// エネミー
	struct EnemyData
	{
		std::string name;
		Math::Vector3 pos;
	};

	std::unordered_map<int, std::vector<EnemyData>> m_enemyList;

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