#include "LightExp.h"

#include "../../../Lib/AssetManager/AssetManager.h"

void LightExp::Update()
{
	m_animeCnt += m_animeSpeed;

	if ((int)m_animeCnt > (int)(m_polygon.GetSplitX() - 1))
	{
		m_isExpired = true;
	}

	m_polygon.SetUVRect((int)m_animeCnt);
}

void LightExp::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void LightExp::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void LightExp::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("lightExp");

	m_animeCnt = 0.0f;
	m_animeSpeed = 0.15f;
}
