#pragma once

class Player :public KdGameObject
{
public:

	Player() { Init(); }		// コンストラクタ
	~Player() {}				// デストラクタ

	void Update()override;		// 更新
	void DrawLit()override;		// 描画
	void Init()override;		// 初期化

private:

	KdModelData m_player;		// モデルデータ
	Math::Vector3 m_pos;		// 座標
	Math::Matrix m_scaleMat;	// 拡大行列
	Math::Matrix m_transMat;	// 移動行列

	const float MOVE_POW = 0.1f;
};