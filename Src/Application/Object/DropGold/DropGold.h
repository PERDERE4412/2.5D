#pragma once

class Player;

class DropGold :public KdGameObject
{
public:

	DropGold() { Init(); }
	~DropGold()override {}

	void Update()override;
	void PostUpdate()override;

	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	void DrawBright()override;

	void Set(Math::Vector3 _pos, int _gold);

private:

	void Init()override;

	KdSquarePolygon m_polygon;

	Math::Vector3 m_pos;

	std::weak_ptr<Player> m_player;

	int m_gold;
};