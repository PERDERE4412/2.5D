#pragma once

class EnemyStatusManager
{
public:

	// ゲッター
	std::unordered_map<std::string, int> GetStatus(std::string _name) { return m_statusList[_name]; }

private:

	void Init();	// 初期化

	// ステータスリスト
	std::unordered_map<std::string,std::unordered_map<std::string, int >> m_statusList;

private:

	EnemyStatusManager() { Init(); }	// コンストラクタ	
	~EnemyStatusManager() {}			// デストラクタ

public:

	static EnemyStatusManager& Instance()
	{
		static EnemyStatusManager instance;
		return instance;
	}
};