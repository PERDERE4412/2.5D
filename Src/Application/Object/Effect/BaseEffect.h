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

	float m_animeCnt;
	float m_animeSpeed;
};