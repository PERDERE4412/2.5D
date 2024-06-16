#pragma once

class Player;

class LichBullet :public KdGameObject
{
public:

	LichBullet() { Init(); }
	~LichBullet() {}

	void Update()override;
	void PostUpdate()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	void DrawBright()override;

	void Set(Math::Vector3 _pos, Math::Vector3 _dir, int _atk);

	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }

private:

	void Init()override;

	void Hit();

	std::weak_ptr<Player> m_player;

	KdSquarePolygon m_polygon;

	Math::Vector3 m_pos;
	Math::Vector3 m_move;

	int m_atk;

	float m_speed;

	float m_animeCnt;
	float m_animeSpeed;
};