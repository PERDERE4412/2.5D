#pragma once

#include "../../../../Animation/Enemy01Animation.h"
#include "../../../../Data/Status/Enemy/Warrior/WarriorStatus.h"

#include "../../BaseChara.h"

class Player;

class Warrior :public BaseChara
{
public:

	Warrior() { Init(); }
	~Warrior()override {}

	void Update()override;
	void PostUpdate()override;

	void SetPlayer(std::weak_ptr<Player> _player) { m_player = _player; }

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

private:

	void Init()override;

	void Move();
	void Attack();

	std::weak_ptr<Player> m_player;
	Math::Vector3 m_playerPos;

	std::shared_ptr<Enemy01Animation> m_anim;

	std::shared_ptr<WarriorStatus> m_status;

	Enemy01Animation::State m_state;	// 状態
	Enemy01Animation::Dir m_dir;		// 向き

	int m_attackWait;					// 攻撃のクールタイム
};