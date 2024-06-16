#pragma once

class LichBulletExp :public KdGameObject
{
public:

	LichBulletExp() { Init(); }
	~LichBulletExp() {}

	void Update()override;
	void DrawUnLit()override;
	void DrawBright()override;

	void SetPos(Math::Vector3 _pos);

private:

	void Init()override;

	KdSquarePolygon m_polygon;

	float m_animeCnt;
	float m_animeSpeed;
};