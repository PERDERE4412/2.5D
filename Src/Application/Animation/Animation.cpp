#include "Animation.h"

#include "../Lib/AssetManager/AssetManager.h"

void Animation::CreateAnime(PlayerState _state, KdSquarePolygon* _polygon)
{
	// 現在の状態と異なっていたら
	if (m_state != _state)
	{
		m_state = _state;

		switch (m_state)
		{
		case Animation::PlayerState::Idol:
			*_polygon = AssetManager::Instance().GetMaterial("playerIdol");
			break;
		case Animation::PlayerState::Walk:
			*_polygon = AssetManager::Instance().GetMaterial("playerDash");
			break;
		}

		m_maxAnime = _polygon->GetSplitX();
		m_cnt = 0.0f;
	}

	m_cnt += m_cntSpeed;
	if (m_cnt >= m_maxAnime)m_cnt = 0.0f;

	_polygon->SetUVRect((int)m_cnt);
}

void Animation::Init()
{
	m_state = PlayerState::None;
	m_cnt = 0.0f;
	m_cntSpeed = 0.2f;
	m_maxAnime = 0;
}