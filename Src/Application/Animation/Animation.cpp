#include "Animation.h"

#include "../Lib/AssetManager/AssetManager.h"

void Animation::CreateAnime(KdSquarePolygon* _polygon)
{
	switch (m_state)
	{
	case Animation::PlayerState::Idol:
		*_polygon = AssetManager::Instance().GetMaterial("playerIdol");
		break;
	case Animation::PlayerState::Walk:
		*_polygon = AssetManager::Instance().GetMaterial("playerDash");
		break;
	}
}

void Animation::Init()
{
	
}
