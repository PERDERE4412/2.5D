#pragma once

#include"../BaseScene/BaseScene.h"

class Player;
class PlayerStatus;

class GameScene : public BaseScene
{
public:

	GameScene() { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init() override;

	void UpdateCamera();

	Math::Vector3 m_pos = {};
	std::weak_ptr<Player> m_player;
	std::shared_ptr<PlayerStatus> m_status;

	bool m_bCreateMap;
};
