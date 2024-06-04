#pragma once

#include "../../../Animation/EnemyAnimation.h"

#include "../BaseChara.h"

class Player;

class Enemy01 :public BaseChara
{
public:

	Enemy01() { Init(); }
	~Enemy01()override {}

	void Update()override;
	void PostUpdate()override;

	void SetPlayer(std::weak_ptr<Player> _player) { m_player = _player; }

private:

	void Init()override;

	void Move();
	void Attack();

	std::weak_ptr<Player> m_player;
	Math::Vector3 m_playerPos;

	EnemyAnimation::EnemyState m_state;	// 状態
	EnemyAnimation::EnemyDir m_dir;		// 向き

	int m_attackWait;					// 攻撃のクールタイム
};