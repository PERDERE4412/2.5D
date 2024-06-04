#include "EnemyManager.h"

#include "../../../Scene/SceneManager.h"
#include "Enemy01.h"

void EnemyManager::Update()
{
	
}

void EnemyManager::Init()
{
	std::shared_ptr<Enemy01> enemy01 = std::make_shared<Enemy01>();
	SceneManager::Instance().AddObject(enemy01);
}
