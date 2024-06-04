#include "Enemy01.h"

#include "../../../Lib/AssetManager/AssetManager.h"
#include "../../../Animation/EnemyAnimation.h"
#include "../Player/Player.h"
#include "../../../Scene/GameScene/GameScene.h"

void Enemy01::Update()
{
	if (!m_player.expired())m_playerPos = m_player.lock()->GetPos();
	else return;

	if (EnemyAnimation::Instance().GetAction())Move();

	EnemyAnimation::Instance().CreateAnime(m_dir, m_state, &m_polygon);
}

void Enemy01::PostUpdate()
{
	Math::Matrix rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(45));
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * rotY * Math::Matrix::CreateTranslation(m_pos);
}

void Enemy01::Init()
{
	m_state = EnemyAnimation::EnemyState::Idle;

	m_dir = EnemyAnimation::EnemyDir::Right;

	m_polygon = AssetManager::Instance().GetMaterial("enemyIdle");

	m_movePow = 0.15f;

	m_attackWait = 0;
}

void Enemy01::Move()
{
	m_state = EnemyAnimation::EnemyState::Idle;

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
	}
	else if (dist <= 5.0f)
	{
		Attack();
	}

	if (m_attackWait > 0)m_attackWait--;

	if (m_dir == EnemyAnimation::EnemyDir::Right)
	{
		m_dir = EnemyAnimation::EnemyDir::Left;
		m_polygon.TurnScale();
	}
	if (m_dir == EnemyAnimation::EnemyDir::Left)
	{
		m_dir = EnemyAnimation::EnemyDir::Right;
		m_polygon.TurnScale();
	}

	if (m_vec != Math::Vector3::Zero && m_state != EnemyAnimation::EnemyState::Attack1)
	{
		m_state = EnemyAnimation::EnemyState::Run;
	}
}

void Enemy01::Attack()
{
	m_movePow = 0.0f;

	if (m_attackWait <= 0)
	{
		m_state = EnemyAnimation::EnemyState::Attack1;
		m_attackWait = 120;
	}
}
