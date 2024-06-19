#include "BaseEffect.h"

void BaseEffect::PostUpdate()
{
	m_animeCnt += m_animeSpeed;

	if ((int)m_animeCnt > (int)(m_polygon.GetSplitX() - 1))
	{
		m_isExpired = true;
	}

	m_polygon.SetUVRect((int)m_animeCnt);
}

void BaseEffect::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void BaseEffect::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}
