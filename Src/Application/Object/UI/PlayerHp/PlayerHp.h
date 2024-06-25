#pragma once

class PlayerStatus;

class PlayerHp :public KdGameObject
{
public:

	PlayerHp() { Init(); }		// コンストラクタ
	~PlayerHp()override {}		// デストラクタ

	void Update()override;		// 更新
	void DrawSprite()override;	// 描画
	
	void SetStatus(std::shared_ptr<PlayerStatus> _status) { m_status = _status; }

private:

	void Init()override;		// 初期化

	std::weak_ptr<PlayerStatus> m_status;

	// 画像の変数をまとめた構造体
	struct texData
	{
		KdTexture* pTex=nullptr;	// 画像データ
		Math::Vector2 pos;			// 座標
		Math::Rectangle rect;		// 切り取り範囲
	};

	texData m_frame;			// 枠
	texData m_bar;				// バー
	texData m_hurt;				// ハート

	int rectX;					// 切り取り範囲
};