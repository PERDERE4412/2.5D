#pragma once

#include "../../../../Animation/GhoulAnimation.h"
#include "../../../../Data/Status/Enemy/Ghoul/GhoulStatus.h"

#include "../../BaseChara.h"

class Player;

class Ghoul :public BaseChara
{
public:

	Ghoul() { Init(); }
	~Ghoul()override {}

	void Update()override;
	void PostUpdate()override;

	void SetPlayer(std::weak_ptr<Player> _player) { m_player = _player; }

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	void Hit(int _damage)override;

private:

	void Init()override;

	void Move();
	void Attack();

	std::weak_ptr<Player> m_player;
	Math::Vector3 m_playerPos;

	std::shared_ptr<GhoulAnimation> m_anim;

	std::shared_ptr<GhoulStatus> m_status;

	GhoulAnimation::State m_state;	// 状態
	GhoulAnimation::Dir m_dir;		// 向き

	int m_attackWait;					// 攻撃のクールタイム

	int m_invWait;						// 無敵時間
};