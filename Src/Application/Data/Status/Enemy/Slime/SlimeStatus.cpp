#include "SlimeStatus.h"

#include "../EnemyStatusManager.h"

void SlimeStatus::Init()
{
	m_status = EnemyStatusManager::Instance().GetStatus("Slime");
}
