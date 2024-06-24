#pragma once

class Player;

class LevelBar :public KdGameObject
{
public:

	LevelBar() { Init(); }
	~LevelBar()override {}

	void Update()override;
	void DrawSprite()override;

	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }

private:

	void Init()override;

	std::weak_ptr<Player> m_player;

	struct  TexData
	{
		KdTexture* pTex = nullptr;	// 画像のポインタ
		Math::Vector2 pos;			// 座標
		Math::Rectangle rect;		// 切り取り範囲
	};

	TexData m_frame;
	TexData m_bar;
	static const int NUM = 2;
	TexData m_level[NUM];

	int rectX;					// 切り取り範囲
};