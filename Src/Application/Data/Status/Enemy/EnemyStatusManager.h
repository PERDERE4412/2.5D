#pragma once

class EnemyStatusManager
{
public:

	struct Status
	{
		int hp;
		int maxHp;
		int atk;
		int def;
	};

	// ゲッター
	Status GetStatus(std::string _name) { return m_statusList[_name]; }

private:

	void Init();	// 初期化

	// ステータスリスト
	std::unordered_map<std::string,Status> m_statusList;

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