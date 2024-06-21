#pragma once

#include "../BaseChara.h"
#include "../../../Animation/EnemyAnimation.h"
#include "../../../Data/Status/Enemy/EnemyStatus.h"

class Player;

class BaseEnemy :public BaseChara
{
public:

	BaseEnemy() { Init(); }
	~BaseEnemy() {}

	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;

	void SetPlayer(std::weak_ptr<Player> _player) { m_player = _player; }

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	void Hit(int _damage);

protected:

	void Init()override;

	virtual void Move() {}
	void Attack();

	std::string m_name;

	std::weak_ptr<Player> m_player;

	std::shared_ptr<EnemyAnimation> m_anim;

	std::shared_ptr<EnemyStatus> m_status;

	EnemyAnimation::State m_state;	// 状態

	Utility::CharaDir m_dir;

	int m_attackWait;					// 攻撃のクールタイム管理値
	int m_setAttackWait;				// 攻撃のクールタイムセット値

	int m_damageWait;					// 被弾時の光る時間管理値
	int m_setDamageWait;				// 被弾時の光る時間セット値

	int m_invWait;						// 無敵時間の管理値
	int m_setInvWait;					// 無敵時間のセット値
};