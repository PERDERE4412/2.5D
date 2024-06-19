#pragma once

class PlayerSwordEffect1 :public KdGameObject
{
public:

	PlayerSwordEffect1() { Init(); }
	~PlayerSwordEffect1()override {}

	void Update()override;
	void PostUpdate()override;
	void DrawUnLit()override;
	void DrawBright()override;

	void SetPos(Math::Vector3 _pos,bool _right,int _atk);

private:

	void Init()override;

	KdSquarePolygon m_polygon;
	Math::Vector3 m_pos;
	Math::Color m_color;

	int m_atk;

	float m_animeCnt;
	float m_animeSpeed;
};