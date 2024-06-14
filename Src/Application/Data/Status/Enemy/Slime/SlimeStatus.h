#pragma once

#include "../EnemyStatusManager.h"

class SlimeStatus
{
public:

	SlimeStatus() { Init(); }
	~SlimeStatus() {}

	void Damage(int _damage) { m_status.hp -= _damage; }

	int GetHp() { return m_status.hp; }
	int GetMaxHp() { return m_status.maxHp; }
	int GetAtk() { return m_status.atk; }
	int GetDef() { return m_status.def; }

private:

	void Init();

	EnemyStatusManager::Status m_status;
};