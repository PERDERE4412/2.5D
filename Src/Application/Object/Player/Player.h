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

	KdModelData m_player;
	Math::Vector3 m_pos;
	Math::Matrix m_scaleMat;
	Math::Matrix m_transMat;
	Math::Matrix m_mat;
};