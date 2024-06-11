#include "FireWispStatus.h"

#include "../EnemyStatusManager.h"

void FireWispStatus::Init()
{
	m_status = EnemyStatusManager::Instance().GetStatus("FireWisp");
}
