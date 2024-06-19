#include "LichSpawn4.h"

#include "../../../Lib/AssetManager/AssetManager.h"

void LichSpawn4::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("lichSpawn4");

	m_animeCnt = 0.0f;
	m_animeSpeed = 0.2f;
}
