#pragma once

class Wall :public KdGameObject
{
public:

	Wall() { Init(); }
	~Wall()override {}

	void DrawLit()override;

private:

	void Init();

	KdModelData m_model;
};