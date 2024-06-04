#include "Enemy01.h"

#include "../../../../Lib/AssetManager/AssetManager.h"
#include "../../../../Animation/Enemy01Animation.h"
#include "../../Player/Player.h"
#include "../../../../Scene/GameScene/GameScene.h"

void Enemy01::Update()
{
	// デバッグ用
	if (GetAsyncKeyState('P') & 0x8000)m_status->Damage(5);

	if (m_status->GetValue("HP") <= 0)m_state = Enemy01Animation::State::Death;

	if (!m_player.expired())m_playerPos = m_player.lock()->GetPos();
	else return;

	// デバッグ用
	if (m_state != Enemy01Animation::State::Death)
	{
		if (m_anim->GetAction())Move();
	}

	m_anim->CreateAnime(m_dir, m_state, &m_polygon);

	if (m_anim->GetKill())m_isExpired = true;
}

void Enemy01::PostUpdate()
{
	Math::Matrix rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(45));
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * rotY * Math::Matrix::CreateTranslation(m_pos);
}

void Enemy01::Init()
{
	m_anim = std::make_shared<Enemy01Animation>();

	m_state = Enemy01Animation::State::Idle;

	m_dir = Enemy01Animation::Dir::Right;

	m_status = std::make_shared<Enemy01Status>();

	m_polygon = AssetManager::Instance().GetMaterial("enemyIdle");
	m_polygon.SetUVRect(0);

	m_movePow = 0.15f;

	m_attackWait = 0;
}

void Enemy01::Move()
{
	m_state = Enemy01Animation::State::Idle;

	m_movePow = 0.15f;

	// 方向ベクトル初期化
	m_vec = Math::Vector3::Zero;

	float dist = Math::Vector3::Distance(m_playerPos, m_pos);
	if (dist < 15.0f && dist > 5.0f)
	{
		m_vec = m_playerPos - m_pos;

		m_vec.Normalize();
		m_vec *= m_movePow;
		m_pos += m_vec;

		if (m_vec.x > 0.0f&& m_vec.z < 0.0f)
		{
			if (m_dir == Enemy01Animation::Dir::Left)
			{
				m_dir = Enemy01Animation::Dir::Right;
				m_polygon.TurnScale();
			}
		}
		else if (m_vec.x < 0.0f&& m_vec.z > 0.0f)
		{
			if (m_dir == Enemy01Animation::Dir::Right)
			{
				m_dir = Enemy01Animation::Dir::Left;
				m_polygon.TurnScale();
			}
		}
	}
	else if (dist <= 5.0f)
	{
		Attack();
	}

	if (m_attackWait > 0)m_attackWait--;

	if (m_vec != Math::Vector3::Zero && m_state != Enemy01Animation::State::Attack1)
	{
		m_state = Enemy01Animation::State::Run;
	}
}

void Enemy01::Attack()
{
	m_movePow = 0.0f;

	if (m_attackWait <= 0)
	{
		m_state = Enemy01Animation::State::Attack1;
		m_attackWait = 120;
	}
}
