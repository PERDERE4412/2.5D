#pragma once

class WallHit :public KdGameObject
{
public:

	WallHit() { Init(); }
	~WallHit()override {}

	void DrawLit()override;

private:

	void Init();

	std::shared_ptr<KdModelData> m_model;
};