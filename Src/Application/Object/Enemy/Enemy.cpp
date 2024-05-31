#include "Enemy.h"

#include "../../Lib/AssetManager/AssetManager.h"

void Enemy::Update()
{
}

void Enemy::PostUpdate()
{
}

void Enemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void Enemy::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("null");
}
