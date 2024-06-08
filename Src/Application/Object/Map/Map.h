#pragma once

class Map :public KdGameObject
{
public:

	Map() { Init(); }	// コンストラクタ
	~Map()override {}	// デストラクタ

	void DrawLit()override;		// 描画
	
private:

	void Init()override;		// 初期化

	// モデルデータ
	KdModelData m_model;
};