#include "LichSpawn2.h"

void LichSpawn2::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("lichSpawn2");

	m_animeCnt = 0.0f;
	m_animeSpeed = 0.3f;
}