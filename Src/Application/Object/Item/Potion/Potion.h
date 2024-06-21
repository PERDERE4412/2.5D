#pragma once

#include "../BaseItem.h"

class Potion :public BaseItem
{
public:

	Potion() { Init(); }
	~Potion()override {}

	void Use()override;

private:

	void Init()override;
};