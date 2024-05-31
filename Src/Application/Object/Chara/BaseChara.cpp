#include "BaseChara.h"

void BaseChara::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void BaseChara::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void BaseChara::Init()
{
	m_movePow = 0.0f;
}
