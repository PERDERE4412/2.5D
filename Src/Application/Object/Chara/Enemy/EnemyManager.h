#pragma once

class Player;

class EnemyManager
{
public:

	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }
	//std::weak_ptr<Player> GetPlayer() { return m_player; }

	void Spawn();

private:

	void Init();

	std::weak_ptr<Player> m_player;

	std::vector<std::shared_ptr<KdGameObject>> m_enemyList;

private:

	EnemyManager() { /*Init();*/ }
	~EnemyManager() {}

public:

	static EnemyManager& Instance()
	{
		static EnemyManager instance;
		return instance;
	}
};