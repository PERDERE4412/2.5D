#pragma once

#include "../BaseEnemy.h"

class Slime :public BaseEnemy
{
public:

	Slime() { Init(); }
	~Slime()override {}

	void Update()override;
	void PostUpdate()override;

private:

	void Init()override;

	void Move();
};