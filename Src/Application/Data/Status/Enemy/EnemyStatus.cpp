#include "EnemyStatus.h"

void EnemyStatus::Init(std::string _name)
{
	m_status = EnemyStatusManager::Instance().GetStatus(_name);
}
