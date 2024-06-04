#pragma once

#include"../BaseScene/BaseScene.h"

class Player;

class GameScene : public BaseScene
{
public:

	GameScene() { Init(); }
	~GameScene() {}

	std::weak_ptr<Player> GetPlayer() { return m_player; }

private:

	void Event() override;
	void Init() override;

	void UpdateCamera();

	Math::Vector3 m_pos = {};
	std::weak_ptr<Player> m_player;
};
