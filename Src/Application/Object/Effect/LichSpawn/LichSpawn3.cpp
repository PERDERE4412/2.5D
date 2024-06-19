#include "LichSpawn3.h"

#include "../../../Lib/AssetManager/AssetManager.h"

void LichSpawn3::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("lichSpawn3");

	m_animeCnt = 0.0f;
	m_animeSpeed = 0.2f;
}
