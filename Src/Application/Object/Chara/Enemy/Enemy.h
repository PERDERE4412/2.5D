#pragma once

#include "../../../Animation/EnemyAnimation.h"

#include "../BaseChara.h"

class Enemy :public BaseChara
{
public:

	Enemy() { Init(); }
	~Enemy()override {}

	void Update()override;
	void PostUpdate()override;

private:

	void Init()override;

	EnemyAnimation::EnemyState m_state;	// 状態
	EnemyAnimation::EnemyDir m_dir;		// 向き
};