#pragma once

#include "../../../Animation/Animation.h"

#include "../BaseChara.h"

class PlayerStatus;

class Player :public BaseChara
{
public:

	Player() { Init(); }		// コンストラクタ
	~Player()override {}		// デストラクタ

	void PreUpdate()override;
	void Update()override;		// 更新
	void PostUpdate()override;
	
	void Hit(int _damage)override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	std::shared_ptr<PlayerStatus> GetStatus() { return m_status; }

private:

	void Init()override;		// 初期化

	void Action();				// 操作
	void Move();				// 移動系
	void Attack();				// 攻撃系

	Animation::PlayerState m_state;	// 状態
	Animation::PlayerDir m_dir;		// 向き

	std::shared_ptr<PlayerStatus> m_status;

	int m_invWait;					// 無敵時間
	int m_damageWait;				// 被弾時の光る時間

	enum class Combo
	{
		None,
		One,
		Two
	};
	int m_comboTime;				// コンボ時間
	Combo m_combo;					// 現在のコンボ

	bool m_bUse;

	int m_walkSoundWait;			// 足音を発生させる間隔
};