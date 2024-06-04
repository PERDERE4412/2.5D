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

private:

	void Init()override;

	void Move();
	void Attack();

	std::weak_ptr<Player> m_player;

	EnemyAnimation::EnemyState m_state;	// 状態
	EnemyAnimation::EnemyDir m_dir;		// 向き


};