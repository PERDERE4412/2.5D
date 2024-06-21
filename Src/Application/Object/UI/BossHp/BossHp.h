#pragma once

#include "../../../Data/Status/Enemy/Lich/LichStatus.h"

class BossHp :public KdGameObject
{
public:

	BossHp() { Init(); }
	~BossHp()override{}

	void Update()override;		// 更新
	void DrawSprite()override;	// 描画

	void SetStatus(std::shared_ptr<LichStatus> _status) { m_status = _status; }

private:

	void Init()override;

	std::weak_ptr<LichStatus> m_status;

	// 画像の変数をまとめた構造体
	struct texData
	{
		KdTexture* pTex = nullptr;	// 画像データ
		Math::Vector2 pos;			// 座標
		Math::Rectangle rect;		// 切り取り範囲
	};

	texData m_frame;			// フレーム
	texData m_bar;				// バー

	int rectX;					// 切り取り範囲
};