#pragma once

class Player;

class WarriorAttack :public KdGameObject
{
public:

	WarriorAttack() { Init(); }
	~WarriorAttack()override {}

	void PostUpdate()override;
	
	void Hit();

	void Set(Math::Vector3 _pos, Math::Vector3 _dir, int _atk);

	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }

private:

	void Init()override;

	std::weak_ptr<Player> m_player;

	Math::Vector3 m_pos;

	int m_atk;

	int m_time;
};