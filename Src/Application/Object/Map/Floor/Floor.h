#pragma once

class Floor :public KdGameObject
{
public:

	Floor() { Init(); }	// コンストラクタ
	~Floor()override {}	// デストラクタ

	void DrawLit()override;		// 描画

private:

	void Init()override;		// 初期化

	// モデルデータ
	KdModelData m_model;
};