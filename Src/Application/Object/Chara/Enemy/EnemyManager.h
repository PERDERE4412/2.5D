#pragma once

class Player;

class EnemyManager
{
public:

	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }
	
	void Spawn(std::string _name,Math::Vector3 _pos);

private:

	void Init();

	std::weak_ptr<Player> m_player;

	std::vector<std::shared_ptr<KdGameObject>> m_enemyList;

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