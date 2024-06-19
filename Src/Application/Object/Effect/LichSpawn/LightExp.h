#pragma once

class LightExp :public KdGameObject
{
public:

	LightExp() { Init(); }
	~LightExp()override {}

	void Update()override;
	void DrawLit()override;
	void DrawBright()override;

private:

	void Init()override;

	KdSquarePolygon m_polygon;

	float m_animeCnt;
	float m_animeSpeed;
};