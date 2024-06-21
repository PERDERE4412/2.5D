#include "Heal.h"

void Heal::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("heal");

	m_animeCnt = 0.0f;
	m_animeSpeed = 0.2f;
}
