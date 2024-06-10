#pragma once

class Wall :public KdGameObject
{
public:

	Wall() { Init(); }
	~Wall()override {}

	void DrawLit()override;

	void SetWall(int _type);

private:

	void Init();

	KdModelData m_model;
};