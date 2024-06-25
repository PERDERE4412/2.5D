#pragma once

#include "../BaseEffect.h"

class Player;

class Heal :public BaseEffect
{
public:

	Heal() { Init(); }
	~Heal()override {}

	void PostUpdate()override;
	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }

private:

	void Init()override;

	std::weak_ptr<Player> m_player;
};