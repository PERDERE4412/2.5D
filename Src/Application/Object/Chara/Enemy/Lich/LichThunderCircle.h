#pragma once

#include "../../../Effect/BaseEffect.h"

class LichThunderCircle :public BaseEffect
{
public:

	LichThunderCircle() { Init(); }
	~LichThunderCircle()override {}

	void PostUpdate()override;

	void Set(Math::Vector3 _pos, int _atk);

private:

	void Init()override;

	Math::Vector3 m_pos;

	int m_atk;

	float m_size;
	float m_sizeSpeed;
};