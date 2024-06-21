#pragma once

#include "../../BaseChara.h"

#include "../../../../Animation/LichAnimation.h"
#include "../../../../Data/Status/Enemy/Lich/LichStatus.h"

class Player;
class BossHp;

class Lich :public BaseChara
{
public:

	Lich() { Init(); }
	~Lich() {}

	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

	void SetPlayer(std::weak_ptr<Player> _player) { m_player = _player; }

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	void Hit(int _damage)override;

private:

	void Init();

	enum class AtkType
	{
		FireBall,
		Thunder,
		summon
	};

	std::weak_ptr<Player> m_player;
	Math::Vector3 m_playerPos;

	void Move();
	void Attack();

	std::shared_ptr<LichAnimation> m_anim;

	std::shared_ptr<LichStatus> m_status;

	std::shared_ptr<BossHp> m_hpBar;

	LichAnimation::State m_state;	// 状態
	LichAnimation::Dir m_dir;		// 向き

	int m_attackWait;					// 攻撃のクールタイム
	bool m_bBullet;						// 弾生成したか
	bool m_bThunder;					// 雷生成したか

	int m_damageWait;					// 被弾時の光る時間

	int m_invWait;						// 無敵時間
};