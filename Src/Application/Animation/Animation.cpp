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
			m_cntSpeed = 0.05f;
			break;
		case Animation::PlayerState::Run:
			*_polygon = AssetManager::Instance().GetMaterial("playerRun");
			m_cntSpeed = 0.2f;
			break;
		case Animation::PlayerState::Roll:
			*_polygon = AssetManager::Instance().GetMaterial("playerRoll");
			m_cntSpeed = 0.5f;
			m_bAction = false;
			break;
		case Animation::PlayerState::Attack1:
			*_polygon = AssetManager::Instance().GetMaterial("playerAttack1");
			m_cntSpeed = 0.5f;
			m_bAction = false;
			break;
		case Animation::PlayerState::Attack2:
			*_polygon = AssetManager::Instance().GetMaterial("playerAttack2");
			m_cntSpeed = 0.5f;
			m_bAction = false;
			break;
		case Animation::PlayerState::Attack3:
			*_polygon = AssetManager::Instance().GetMaterial("playerAttack3");
			m_cntSpeed = 0.5f;
			m_bAction = false;
			break;
		}

		m_maxAnime = _polygon->GetSplitX();
		m_cnt = 0.0f;
	}

	AnimeCnt();

	_polygon->SetUVRect((int)m_cnt);
}

void Animation::AnimeCnt()
{
	if (m_bStiff)
	{
		m_wait--;
		if (m_wait <= 0)
		{
			m_bStiff = false;
		}
		return;
	}

	m_cnt += m_cntSpeed;		// カウントを進める

	if (m_cnt >= m_maxAnime)	// アニメーションが１週したら
	{
		m_cnt = 0.0f;

		if (m_state == PlayerState::Roll)
		{
			m_bStiff = true;
			m_bAction = true;
			m_wait = 20;
		}
	}
}

void Animation::Init()
{
	m_state = PlayerState::None;
	
	m_cnt = 0.0f;
	m_cntSpeed = 0.2f;
	m_maxAnime = 0;

	m_bAction = true;
	m_bStiff = false;
	m_wait = 0;
}