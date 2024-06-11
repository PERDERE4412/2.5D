#pragma once

class PlayerStatus
{
public:

	// ゲッター
	int GetValue(std::string _name) { return m_statusList[_name]; }

	// 経験値取得
	void SetExp(int _point);

	// ダメージ
	void Damage(int _damage) { m_statusList["HP"] -= _damage; }

private:

	void Init();	// 初期化

	// ステータスリスト
	std::unordered_map<std::string, int> m_statusList;

private:

	PlayerStatus() { Init(); }	// コンストラクタ	
	~PlayerStatus() {}			// デストラクタ

public:

	static PlayerStatus& Instance()
	{
		static PlayerStatus instance;
		return instance;
	}
};