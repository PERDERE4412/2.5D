#pragma once

class TitlePlayer :public KdGameObject
{
public:

	TitlePlayer() { Init(); }
	~TitlePlayer()override {}

	void PostUpdate()override;
	void DrawLit()override;

private:

	void Init()override;

	KdSquarePolygon m_polygon;
};