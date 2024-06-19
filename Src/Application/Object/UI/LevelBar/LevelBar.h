#pragma once

class LevelBar :public KdGameObject
{
public:

	LevelBar() { Init(); }
	~LevelBar()override {}

	void Update()override;
	void DrawSprite()override;

private:

	void Init()override;

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