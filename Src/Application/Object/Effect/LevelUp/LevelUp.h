#pragma once

#include "../BaseEffect.h"

class Player;

class LevelUp :public BaseEffect
{
public:

	LevelUp() { Init(); }
	~LevelUp() {}

	void PostUpdate()override;
	void DrawBright()override {}
	void DrawUnLit()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }

private:

	void Init()override;

	std::weak_ptr<Player> m_player;

	Math::Vector3 m_pos;
	Math::Color m_color;
	float m_alpha;
	float m_addAlpha;

	Math::Vector3 m_adjustPos;
	float m_addAdjust;
};