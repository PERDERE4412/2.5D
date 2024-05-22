#pragma once

#include "../../Animation/Animation.h"

class Player :public KdGameObject
{
public:

	Player() { Init(); }		// コンストラクタ
	~Player()override {}		// デストラクタ

	void Update()override;		// 更新
	void DrawLit()override;		// 描画
	void Init()override;		// 初期化

private:

	KdSquarePolygon m_polygon;		// 板ポリゴン
	Math::Vector3 m_pos;			// 座標

	Animation::PlayerState m_state;	// プレイヤーの状態

	const float MOVE_POW = 0.2f;	// 移動量
};