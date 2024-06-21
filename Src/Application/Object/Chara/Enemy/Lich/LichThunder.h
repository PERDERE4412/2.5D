#pragma once

#include "../../../Effect/BaseEffect.h"

class LichThunder :public BaseEffect
{
public:

	LichThunder() { Init(); }
	~LichThunder()override {}

	void PostUpdate()override;

	void Set(Math::Vector3 _pos, int _atk);

private:

	void Init();

	int m_atk;
};