#include "Enemy.h"

#include "../../../Lib/AssetManager/AssetManager.h"
#include "../../../Animation/EnemyAnimation.h"

void Enemy::Update()
{
	EnemyAnimation::Instance().CreateAnime(m_dir, m_state, &m_polygon);
}

void Enemy::PostUpdate()
{
	Math::Matrix rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(45));
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * rotY * Math::Matrix::CreateTranslation(m_pos);
}

void Enemy::Init()
{
	m_state = EnemyAnimation::EnemyState::Idle;

	m_dir = EnemyAnimation::EnemyDir::Right;

	m_polygon = AssetManager::Instance().GetMaterial("enemyIdle");
}
