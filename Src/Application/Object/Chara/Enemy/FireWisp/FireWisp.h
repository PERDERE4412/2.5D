#pragma once

#include "../../../../Animation/FireWispAnimation.h"
#include "../../../../Data/Status/Enemy/FireWisp/FireWispStatus.h"

#include "../../BaseChara.h"

class Player;

class FireWisp :public BaseChara
{
public:

	FireWisp() { Init(); }
	~FireWisp()override {}

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

	std::shared_ptr<FireWispAnimation> m_anim;

	std::shared_ptr<FireWispStatus> m_status;

	FireWispAnimation::State m_state;	// 状態
	FireWispAnimation::Dir m_dir;		// 向き

	int m_attackWait;					// 攻撃のクールタイム

	int m_invWait;						// 無敵時間
};