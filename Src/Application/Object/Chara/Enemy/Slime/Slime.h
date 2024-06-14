#pragma once

#include "../../../../Animation/SlimeAnimation.h"
#include "../../../../Data/Status/Enemy/Slime/SlimeStatus.h"

#include "../../BaseChara.h"

class Player;

class Slime :public BaseChara
{
public:

	Slime() { Init(); }
	~Slime()override {}

	void PreUpdate()override;
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

	std::shared_ptr<SlimeAnimation> m_anim;

	std::shared_ptr<SlimeStatus> m_status;

	SlimeAnimation::State m_state;	// 状態
	SlimeAnimation::Dir m_dir;		// 向き

	int m_attackWait;					// 攻撃のクールタイム

	int m_damageWait;					// 被弾時の光る時間

	int m_invWait;						// 無敵時間
};