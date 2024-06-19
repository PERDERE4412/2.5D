#pragma once

#include "../BaseEffect.h"

class LichSpawn4 :public BaseEffect
{
public:

	LichSpawn4() { Init(); }
	~LichSpawn4()override {}

private:

	void Init()override;
};