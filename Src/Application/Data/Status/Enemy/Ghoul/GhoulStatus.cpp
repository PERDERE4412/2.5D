#include "GhoulStatus.h"

#include "../EnemyStatusManager.h"

void GhoulStatus::Init()
{
	m_status = EnemyStatusManager::Instance().GetStatus("Ghoul");
}
