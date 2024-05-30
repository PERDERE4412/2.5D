#include "Enemy.h"

void Enemy::Update()
{
}

void Enemy::PostUpdate()
{
}

void Enemy::GenerateDepthMapFromLight()
{
}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void Enemy::Init()
{
}
