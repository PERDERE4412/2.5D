#include "EnemyManager.h"

#include "../../../Scene/SceneManager.h"
#include "../../../Map/MapManager.h"
#include "Warrior/Warrior.h"

void EnemyManager::Spawn(std::string _name, Math::Vector3 _pos)
{
	if (_name == "Warrior")
	{
		std::shared_ptr<Warrior> warrior = std::make_shared<Warrior>();
		warrior->SetPos(_pos);
		warrior->SetPlayer(m_player);
		SceneManager::Instance().AddObject(warrior);
		MapManager::Instance().AddObject(warrior);
	}
}

void EnemyManager::Init()
{
	
}