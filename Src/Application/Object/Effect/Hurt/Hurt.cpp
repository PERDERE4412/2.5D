#include "Hurt.h"

void Hurt::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("playerHurt");

	m_animeCnt = 0.0f;
	m_animeSpeed = 0.2f;
}
