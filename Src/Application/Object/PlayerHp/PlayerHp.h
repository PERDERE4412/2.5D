#pragma once

class PlayerHp :public KdGameObject
{
public:

	PlayerHp() { Init(); }		// コンストラクタ
	~PlayerHp() {}				// デストラクタ

	void Update()override;		// 更新
	void DrawSprite()override;	// 描画
	void Init()override;		// 初期化

private:

	struct texData
	{
		KdTexture tex;
		Math::Matrix mat;
		Math::Rectangle rect;
	};

	texData m_frame;
	texData m_bar;
};