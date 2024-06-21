#pragma once

#include "EnemyStatusManager.h"

class EnemyStatus
{
public:

	EnemyStatus() {}
	~EnemyStatus() {}

	void Init(std::string _name);

	void Damage(int _damage) { m_status.hp -= _damage; }

	std::string GetName() { return m_status.name; }
	int GetHp() { return m_status.hp; }
	int GetMaxHp() { return m_status.maxHp; }
	int GetAtk() { return m_status.atk; }
	int GetDef() { return m_status.def; }
	int GetExp() { return m_status.exp; }

private:

	EnemyStatusManager::Status m_status;
};