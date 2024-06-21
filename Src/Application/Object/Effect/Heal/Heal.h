#pragma once

#include "../BaseEffect.h"

class Heal :public BaseEffect
{
public:

	Heal() { Init(); }
	~Heal()override {}

private:

	void Init()override;
};