#include "WarriorStatus.h"

#include "../EnemyStatusManager.h"

void WarriorStatus::Init()
{
	m_status = EnemyStatusManager::Instance().GetStatus("Warrior");
}
