#include "Lightning.h"

#include "../../../Lib/AssetManager/AssetManager.h"
#include "../../../Scene/SceneManager.h"
#include "../../Chara/Enemy/Lich/Lich.h"

void Lightning::Update()
{
	m_animeCnt += m_animeSpeed;

	if ((int)m_animeCnt > (int)(m_polygon.GetSplitX() - 1))
	{
		m_isExpired = true;
	}

	m_polygon.SetUVRect((int)m_animeCnt);
}

void Lightning::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void Lightning::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void Lightning::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("lightning");

	m_animeCnt = 0.0f;
	m_animeSpeed = 0.15f;
}