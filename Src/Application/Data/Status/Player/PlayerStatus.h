#pragma once

class Player;

class PlayerStatus
{
public:

	PlayerStatus() { Init(); }
	~PlayerStatus() {};

	// ゲッター
	int GetValue(std::string _name) { return m_statusList[_name]; }

	std::unordered_map<std::string, int> GetStatus() { return m_statusList; }

	// セッター
	void SetValue(std::string _name, int _value) { m_statusList[_name] = _value; }

	// 経験値取得
	void SetExp(int _point);

	// ダメージ
	void Damage(int _damage);

	// 回復
	void Heal(int _heal);

	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }

private:

	void Init();	// 初期化

	std::weak_ptr<Player> m_player;

	// ステータスリスト
	std::unordered_map<std::string, int> m_statusList;
};