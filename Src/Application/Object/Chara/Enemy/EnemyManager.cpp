#include "EnemyManager.h"

#include "../../../Scene/SceneManager.h"
#include "../../../Map/MapManager.h"
#include "Warrior/Warrior.h"
#include "FireWisp/FireWisp.h"
#include "Slime/Slime.h"
#include "Lich/Lich.h"

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

	if (_name == "Slime")
	{
		std::shared_ptr<Slime> slime = std::make_shared<Slime>();
		slime->SetPos(_pos);
		slime->SetPlayer(m_player);
		SceneManager::Instance().AddObject(slime);
		MapManager::Instance().AddObject(slime);
	}

	if (_name == "Lich")
	{
		std::shared_ptr<Lich> lich = std::make_shared<Lich>();
		lich->SetPos(_pos);
		lich->SetPlayer(m_player);
		SceneManager::Instance().AddObject(lich);
		MapManager::Instance().AddObject(lich);
	}
}

void EnemyManager::Init()
{
	
}