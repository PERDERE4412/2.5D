#pragma once

class Slot :public KdGameObject
{
public:

	Slot() { Init(); }			// コンストラクタ
	~Slot()override {}			// デストラクタ

	void Update()override;		// 更新
	void DrawSprite()override;	// 描画
	void Init()override;		// 初期化

private:

	KdTexture m_tex;			// 画像データ
	Math::Vector3 m_pos;		// 座標
	Math::Rectangle m_rect;		// 切り取り範囲
};