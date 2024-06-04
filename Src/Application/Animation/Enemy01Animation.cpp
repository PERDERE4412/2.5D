#include "Enemy01Animation.h"

#include "../Lib/AssetManager/AssetManager.h"

void Enemy01Animation::CreateAnime(Dir _dir, State _state, KdSquarePolygon* _polygon)
{
	// 現在の状態と異なっていたら
	if (m_state != _state)
	{
		m_state = _state;

		switch (m_state)
		{
		case State::Idle:
			*_polygon = AssetManager::Instance().GetMaterial("enemyIdle");
			m_cntSpeed = 0.05f;
			break;
		case State::Run:
			*_polygon = AssetManager::Instance().GetMaterial("enemyRun");
			m_cntSpeed = 0.2f;
			break;
		case State::Attack1:
			*_polygon = AssetManager::Instance().GetMaterial("enemyAttack1");
			m_cntSpeed = 0.5f;
			m_bAction = false;
			break;
		case State::Attack2:
			*_polygon = AssetManager::Instance().GetMaterial("enemyAttack2");
			m_cntSpeed = 0.5f;
			m_bAction = false;
			break;
		}

		if (_dir == Dir::Left)_polygon->TurnScale();

		m_maxAnime = _polygon->GetSplitX();
		m_cnt = 0.0f;
	}

	AnimeCnt();

	_polygon->SetUVRect((int)m_cnt);
}

void Enemy01Animation::AnimeCnt()
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
		if (m_state == State::Attack1)
		{
			m_bStiff = true;
			m_bAction = true;
			m_wait = 10;
		}
		else if (m_state == State::Attack2)
		{
			m_bStiff = true;
			m_bAction = true;
			m_wait = 10;
		}
		else m_cnt = 0.0f;
	}
}

void Enemy01Animation::Init()
{
	m_state = State::None;

	m_cnt = 0.0f;
	m_cntSpeed = 0.2f;
	m_maxAnime = 0;

	m_bAction = true;
	m_bStiff = false;
	m_wait = 0;
}