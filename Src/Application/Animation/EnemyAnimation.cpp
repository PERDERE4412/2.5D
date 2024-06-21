#include "EnemyAnimation.h"

void EnemyAnimation::CreateAnime(std::string _name,Utility::CharaDir _dir, State _state, KdSquarePolygon* _polygon)
{
	// 現在の状態と異なっていたら
	if (m_state != _state)
	{
		m_state = _state;

		switch (m_state)
		{
		case State::Idle:
			_name += "Idle";
			*_polygon = AssetManager::Instance().GetMaterial(_name);
			m_cntSpeed = 0.05f;
			break;
		case State::Run:
			_name += "Run";
			*_polygon = AssetManager::Instance().GetMaterial(_name);
			m_cntSpeed = 0.2f;
			break;
		case State::Attack:
			_name += "Attack";
			*_polygon = AssetManager::Instance().GetMaterial(_name);
			m_cntSpeed = 0.2f;
			m_bAction = false;
			break;
		case State::Death:
			_name += "Death";
			*_polygon = AssetManager::Instance().GetMaterial(_name);
			m_cntSpeed = 0.2f;
			m_bAction = false;
			break;
		}

		if (_dir == Utility::CharaDir::Left)_polygon->TurnScale();

		m_maxAnime = _polygon->GetSplitX();
		m_cnt = 0.0f;
	}

	AnimeCnt();

	_polygon->SetUVRect((int)m_cnt);
}

void EnemyAnimation::AnimeCnt()
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
		if (m_state == State::Attack)
		{
			m_bStiff = true;
			m_bAction = true;
			m_wait = 10;
		}
		else if (m_state == State::Death)
		{
			m_bKill = true;
		}
		else m_cnt = 0.0f;
	}
}

void EnemyAnimation::Init()
{
	m_state = State::Idle;

	m_cnt = 0.0f;
	m_cntSpeed = 0.2f;
	m_maxAnime = 0;

	m_bAction = true;
	m_bStiff = false;
	m_wait = 0;

	m_bKill = false;
}