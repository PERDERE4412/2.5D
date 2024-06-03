#include "Animation.h"

#include "../Lib/AssetManager/AssetManager.h"

void Animation::CreateAnime(PlayerDir _dir,PlayerState _state, KdSquarePolygon* _polygon)
{
	// 現在の状態と異なっていたら
	if (m_state != _state)
	{
		m_state = _state;

		switch (m_state)
		{
		case PlayerState::Idle:
			*_polygon = AssetManager::Instance().GetMaterial("playerIdle");
			m_cntSpeed = 0.05f;
			break;
		case PlayerState::Run:
			*_polygon = AssetManager::Instance().GetMaterial("playerRun");
			m_cntSpeed = 0.2f;
			break;
		case PlayerState::Roll:
			*_polygon = AssetManager::Instance().GetMaterial("playerRoll");
			m_cntSpeed = 0.5f;
			m_bAction = false;
			break;
		case PlayerState::Attack1:
			*_polygon = AssetManager::Instance().GetMaterial("playerAttack1");
			m_cntSpeed = 0.5f;
			m_bAction = false;
			break;
		case PlayerState::Attack2:
			*_polygon = AssetManager::Instance().GetMaterial("playerAttack2");
			m_cntSpeed = 0.5f;
			m_bAction = false;
			break;
		case PlayerState::Attack3:
			*_polygon = AssetManager::Instance().GetMaterial("playerAttack3");
			m_cntSpeed = 0.5f;
			m_bAction = false;
			break;
		}

		if (_dir == PlayerDir::Left)_polygon->TurnScale();

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
		if (m_state == PlayerState::Attack1)
		{
			m_bStiff = true;
			m_bAction = true;
			m_wait = 10;
		}
		if (m_state == PlayerState::Attack2)
		{
			m_bStiff = true;
			m_bAction = true;
			m_wait = 10;
		}
		if (m_state == PlayerState::Attack3)
		{
			m_bStiff = true;
			m_bAction = true;
			m_wait = 10;
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