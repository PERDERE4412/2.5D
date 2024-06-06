#pragma once

class PlayerHp :public KdGameObject
{
public:

	PlayerHp() { Init(); }		// コンストラクタ
	~PlayerHp()override {}		// デストラクタ

	void Update()override;		// 更新
	void DrawSprite()override;	// 描画
	void Init()override;		// 初期化

private:

	// 画像の変数をまとめた構造体
	struct texData
	{
		KdTexture* pTex;		// 画像データ
		Math::Vector2 pos;		// 座標
		Math::Rectangle rect;	// 切り取り範囲
	};

	texData m_frame;			// フレーム
	texData m_bar;				// バー

	int rectX;					// 切り取り範囲
};