#include "Enemy01Status.h"

#include "../EnemyStatusManager.h"

void Enemy01Status::Init()
{
	m_statusList = EnemyStatusManager::Instance().GetStatus("Enemy01");
}
