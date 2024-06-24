#pragma once

#include "../BaseEffect.h"

class Hurt :public BaseEffect
{
public:

	Hurt() { Init(); }
	~Hurt()override {}

private:

	void Init()override;
};