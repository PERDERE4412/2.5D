#pragma once

class EnemyStatusManager
{
public:

	struct Status
	{
		std::string name;
		int hp = 0;
		int maxHp = 0;
		int atk = 0;
		int def = 0;
		int exp = 0;
	};

	// ゲッター
	Status GetStatus(std::string _name) { return m_statusList[_name]; }

private:

	void Init();	// 初期化

	// ステータスリスト
	std::unordered_map<std::string, Status> m_statusList;

private:

	EnemyStatusManager() { Init(); }	// コンストラクタ	
	~EnemyStatusManager() {}			// デストラクタ

public:

	// シングルトンパターン
	static EnemyStatusManager& Instance()
	{
		static EnemyStatusManager instance;
		return instance;
	}
};