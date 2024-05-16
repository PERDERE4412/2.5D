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
};