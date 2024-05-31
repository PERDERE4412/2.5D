#pragma once

#include "../../../Animation/Animation.h"

#include "../BaseChara.h"

class Player :public BaseChara
{
public:

	Player() { Init(); }		// コンストラクタ
	~Player()override {}		// デストラクタ

	void Update()override;		// 更新
	void PostUpdate()override;
	
private:

	void Init()override;		// 初期化

	void Action();				// 操作
	void Move();				// 移動系
	void Attack();				// 攻撃系

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
};