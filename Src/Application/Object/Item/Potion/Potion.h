#pragma once

#include "../BaseItem.h"

class Player;

class Potion :public BaseItem
{
public:

	Potion() { Init(); }
	~Potion()override {}

	void Use()override;

private:

	void Init()override;
};