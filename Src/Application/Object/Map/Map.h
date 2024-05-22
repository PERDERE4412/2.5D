#pragma once

class Map :public KdGameObject
{
public:

	Map() { Init(); }	// コンストラクタ
	~Map()override {}	// デストラクタ

	void DrawLit();		// 描画
	void Init();		// 初期化

private:

	// モデルデータ
	KdModelData m_model;
};