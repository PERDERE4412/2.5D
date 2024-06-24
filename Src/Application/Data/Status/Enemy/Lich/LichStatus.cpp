#include "LichStatus.h"

#include "../EnemyStatusManager.h"

void LichStatus::Damage(int _damage)
{
	m_status.hp -= _damage;
	if (m_status.hp <= 0)m_status.hp = 0;
}

void LichStatus::Init()
{
	m_status = EnemyStatusManager::Instance().GetStatus("Lich");
}