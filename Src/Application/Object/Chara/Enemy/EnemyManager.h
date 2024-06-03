#pragma once

class Player;

class EnemyManager
{
public:

	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }

private:

	void Init();

	std::weak_ptr<Player> m_player;

private:

	EnemyManager() { Init(); }
	~EnemyManager() {}

public:

	static EnemyManager& Instance()
	{
		static EnemyManager instance;
		return instance;
	}
};