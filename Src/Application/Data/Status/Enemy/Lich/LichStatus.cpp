#include "LichStatus.h"

#include "../EnemyStatusManager.h"

void LichStatus::Init()
{
	m_status = EnemyStatusManager::Instance().GetStatus("Lich");
}