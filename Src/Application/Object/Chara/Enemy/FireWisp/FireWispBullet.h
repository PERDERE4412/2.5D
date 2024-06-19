#pragma once

class Player;

class FireWispBullet :public KdGameObject
{
public:

	FireWispBullet() { Init(); }
	~FireWispBullet() {}

	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void DrawBright()override;

	void Hit();

	void Set(Math::Vector3 _pos, Math::Vector3 _dir,int _atk);
	
	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }

private:

	void Init()override;

	std::weak_ptr<Player> m_player;

	KdSquarePolygon m_polygon;

	Math::Vector3 m_pos;
	Math::Vector3 m_move;

	int m_atk;

	float m_speed;

	float m_animeCnt;
	float m_animeSpeed;
};