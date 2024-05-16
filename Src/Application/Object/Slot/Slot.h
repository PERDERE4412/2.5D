#pragma once

class Slot :public KdGameObject
{
public:

	Slot() { Init(); }			// コンストラクタ
	~Slot() {}					// デストラクタ

	void Update()override;		// 更新
	void DrawSprite()override;	// 描画
	void Init()override;		// 初期化

private:

	KdTexture m_tex;
	Math::Vector3 m_pos;
	Math::Matrix m_mat;
	Math::Rectangle m_rect;
};