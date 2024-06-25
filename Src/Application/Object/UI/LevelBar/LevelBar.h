#pragma once

class PlayerStatus;

class LevelBar :public KdGameObject
{
public:

	LevelBar() { Init(); }
	~LevelBar()override {}

	void Update()override;
	void DrawSprite()override;

	//void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }
	void SetStatus(std::shared_ptr<PlayerStatus> _status) { m_status = _status; }

private:

	void Init()override;

	//std::weak_ptr<Player> m_player;
	std::weak_ptr<PlayerStatus> m_status;

	struct  TexData
	{
		KdTexture* pTex = nullptr;	// 画像のポインタ
		Math::Vector2 pos;			// 座標
		Math::Rectangle rect;		// 切り取り範囲
	};

	TexData m_frame;				// 枠
	TexData m_bar;					// バー
	TexData m_level;				// レベル
	static const int NUM = 2;
	TexData m_value[NUM];			// 数値

	int rectX;					// 切り取り範囲
};