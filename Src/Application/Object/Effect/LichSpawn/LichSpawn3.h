#pragma once

#include "../BaseEffect.h"

class LichSpawn3 :public BaseEffect
{
public:

	LichSpawn3() { Init(); }
	~LichSpawn3()override {}

private:

	void Init()override;
};