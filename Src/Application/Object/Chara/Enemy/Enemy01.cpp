#include "Enemy01.h"

#include "../../../Lib/AssetManager/AssetManager.h"
#include "../../../Animation/EnemyAnimation.h"
#include "../Player/Player.h"
#include "EnemyManager.h"

void Enemy01::Update()
{
	Move();

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

	m_movePow = 0.2f;
}

void Enemy01::Move()
{
	m_player = EnemyManager::Instance().GetPlayer();
	Math::Vector3 playerPos = Math::Vector3::Zero;
	if (!m_player.expired())
	{
		playerPos = m_player.lock()->GetPos();
	}

	// 方向ベクトル初期化
	m_vec = Math::Vector3::Zero;
	m_vec = playerPos - m_pos;

	m_vec.Normalize();
	m_vec *= m_movePow;
	m_pos += m_vec;

	/*if (m_dir == EnemyAnimation::EnemyDir::Right)
	{
		m_dir = EnemyAnimation::EnemyDir::Left;
		m_polygon.TurnScale();
	}

	if (m_dir == EnemyAnimation::EnemyDir::Left)
	{
		m_dir = EnemyAnimation::EnemyDir::Right;
		m_polygon.TurnScale();
	}*/

	//if (m_vec != Math::Vector3::Zero)m_state = EnemyAnimation::EnemyState::Run;
}

void Enemy01::Attack()
{

}
