#pragma once

#include "../../Animation/Animation.h"

class Player :public KdGameObject
{
public:

	Player() { Init(); }		// コンストラクタ
	~Player()override {}		// デストラクタ

	void Update()override;		// 更新
	void PostUpdate()override;
	void GenerateDepthMapFromLight()override;	// 描画
	void DrawLit()override;		// 描画
	void Init()override;		// 初期化

private:

	void Action();				// 操作
	void Move();				// 移動系
	void Attack();				// 攻撃系

	KdSquarePolygon m_polygon;		// 板ポリゴン
	Math::Vector3 m_pos;			// 座標
	Math::Vector3 m_vec;			// 方向ベクトル

	Animation::PlayerState m_state;	// 状態
	Animation::PlayerDir m_dir;		// 向き

	enum class Combo
	{
		None,
		One,
		Two
	};
	int m_comboTime;				// コンボ時間
	Combo m_combo;					// 現在のコンボ

	float m_movePow;				// 移動量
};