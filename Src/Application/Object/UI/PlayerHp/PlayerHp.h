#pragma once

class Player;

class PlayerHp :public KdGameObject
{
public:

	PlayerHp() { Init(); }		// コンストラクタ
	~PlayerHp()override {}		// デストラクタ

	void Update()override;		// 更新
	void DrawSprite()override;	// 描画
	
	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }

private:

	void Init()override;		// 初期化

	std::weak_ptr<Player> m_player;

	// 画像の変数をまとめた構造体
	struct texData
	{
		KdTexture* pTex=nullptr;	// 画像データ
		Math::Vector2 pos;			// 座標
		Math::Rectangle rect;		// 切り取り範囲
	};

	texData m_frame;			// フレーム
	texData m_bar;				// バー

	int rectX;					// 切り取り範囲
};