#include "LichSpawn1.h"

void LichSpawn1::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("lichSpawn1");

	m_animeCnt = 0.0f;
	m_animeSpeed = 0.15f;
}
