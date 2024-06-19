#pragma once

#include "../BaseEffect.h"

class LichSpawn2 : public BaseEffect
{
public:

	LichSpawn2() { Init(); }
	~LichSpawn2()override {}

private:

	void Init()override;
};