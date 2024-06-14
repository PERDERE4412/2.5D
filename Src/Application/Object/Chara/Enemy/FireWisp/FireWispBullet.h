#pragma once

class FireWispBullet :public KdGameObject
{
public:

	FireWispBullet() { Init(); }
	~FireWispBullet() {}

	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;

	void Set(Math::Vector3 _pos, Math::Vector3 _dir,int _atk);
	
private:

	void Init()override;

	KdSquarePolygon m_polygon;

	Math::Vector3 m_pos;
	Math::Vector3 m_move;

	int m_atk;

	float m_speed;
};