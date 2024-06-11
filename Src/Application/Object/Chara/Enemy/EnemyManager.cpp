#include "EnemyManager.h"

#include "../../../Scene/SceneManager.h"
#include "../../../Map/MapManager.h"
#include "Warrior/Warrior.h"
#include "FireWisp/FireWisp.h"
#include "Ghoul/Ghoul.h"

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

	if (_name == "FireWisp")
	{
		std::shared_ptr<FireWisp> fireWisp = std::make_shared<FireWisp>();
		fireWisp->SetPos(_pos);
		fireWisp->SetPlayer(m_player);
		SceneManager::Instance().AddObject(fireWisp);
		MapManager::Instance().AddObject(fireWisp);
	}

	if (_name == "Ghoul")
	{
		std::shared_ptr<Ghoul> ghoul = std::make_shared<Ghoul>();
		ghoul->SetPos(_pos);
		ghoul->SetPlayer(m_player);
		SceneManager::Instance().AddObject(ghoul);
		MapManager::Instance().AddObject(ghoul);
	}
}

void EnemyManager::Init()
{
	
}