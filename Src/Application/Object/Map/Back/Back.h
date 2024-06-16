#pragma once

class Back :public KdGameObject
{
public:

	Back() { Init(); }
	~Back()override {}

	void Update()override;
	void DrawUnLit()override;

private:

	void Init()override;

	KdSquarePolygon m_polygon;
};