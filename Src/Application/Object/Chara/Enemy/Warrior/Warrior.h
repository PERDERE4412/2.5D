#pragma once

#include "../BaseEnemy.h"

class Warrior :public BaseEnemy
{
public:

	Warrior() { Init(); }
	~Warrior()override {}

	void Update()override;
	void PostUpdate()override;

private:

	void Init()override;

	void Move()override;
};