﻿#pragma once

class BaseChara :public KdGameObject
{
public:

	BaseChara() {}
	~BaseChara()override {}

	void GenerateDepthMapFromLight()override;	// 描画
	void DrawLit()override;						// 描画

	void Init()override;

private:

	KdSquarePolygon m_polygon;		// 板ポリゴン
	Math::Vector3 m_pos;			// 座標
	Math::Vector3 m_vec;			// 方向ベクトル

	float m_movePow;				// 移動量
};