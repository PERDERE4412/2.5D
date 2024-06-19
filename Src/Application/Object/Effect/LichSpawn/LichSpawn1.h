#pragma once

#include "../BaseEffect.h"

class LichSpawn1 :public BaseEffect
{
public:

	LichSpawn1() { Init(); }
	~LichSpawn1()override {}

private:

	void Init()override;
};