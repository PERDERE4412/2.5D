#include "WarriorStatus.h"

#include "../EnemyStatusManager.h"

void WarriorStatus::Init()
{
	m_statusList = EnemyStatusManager::Instance().GetStatus("Warrior");
}
