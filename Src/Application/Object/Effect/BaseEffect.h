#pragma once

class BaseEffect :public KdGameObject
{
public:

	BaseEffect() {}
	~BaseEffect()override {}

	void PostUpdate()override;
	void DrawUnLit()override;
	void DrawBright()override;

protected:

	KdSquarePolygon m_polygon;

	float m_animeCnt = 0.0f;
	float m_animeSpeed = 0.0f;
};