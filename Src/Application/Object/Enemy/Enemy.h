#pragma once

class Enemy :public KdGameObject
{
public:

	Enemy() { Init(); }
	~Enemy()override {}

	void Update()override;
	void PostUpdate()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

private:

	void Init();

	KdSquarePolygon m_polygon;
};