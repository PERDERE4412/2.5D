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
		KdTexture* pTex;		// 画像のポインタ
		Math::Vector3 pos;		// 座標
		Math::Vector3 size;		// サイズ
		Math::Matrix mat;		// 行列	
		Math::Rectangle rect;	// 切り取り範囲
		int width;				// 横サイズ
		int height;				// 縦サイズ
		void Set();				// セット関数
	};

	TexData m_frame;
	TexData m_bar;
	static const int NUM = 2;
	TexData m_level[NUM];
};