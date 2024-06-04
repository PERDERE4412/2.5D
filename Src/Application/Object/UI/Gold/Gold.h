#pragma once

class Gold :public KdGameObject
{
public:

	Gold() { Init(); }
	~Gold()override {}

	void Update()override;		// 更新
	void DrawSprite()override;	// 描画

private:

	void Init()override;		// 初期化

	struct TexData
	{
		KdTexture* pTex = nullptr;
		Math::Vector3 pos;
		Math::Matrix mat;
		Math::Rectangle rect;
	};

	TexData m_gold;
	static const int NUM = 3;
	TexData m_number[NUM];

	int m_currentGold;
};