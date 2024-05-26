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

	KdTexture* m_pTex;			// 画像データ
	Math::Vector3 m_pos;		// 座標
	Math::Rectangle m_rect;		// 切り取り範囲
};