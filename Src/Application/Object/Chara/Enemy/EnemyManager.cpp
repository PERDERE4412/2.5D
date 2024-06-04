#include "EnemyManager.h"

#include "../../../Scene/SceneManager.h"
#include "Enemy01/Enemy01.h"

void EnemyManager::Spawn()
{
	std::shared_ptr<Enemy01> enemy01 = std::make_shared<Enemy01>();
	enemy01->SetPlayer(m_player);
	SceneManager::Instance().AddObject(enemy01);
}

void EnemyManager::Init()
{
	
}
