#include "ClickStart.h"

void ClickStart::Update()
{
	m_alpha += m_addAlpha;
	if (m_alpha > 1.0f)
	{
		m_alpha = 1.0f;
		m_addAlpha *= -1;
	}
	if (m_alpha < 0.3f)
	{
		m_alpha = 0.3f;
		m_addAlpha *= -1;
	}

	m_color.w = m_alpha;
}

void ClickStart::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, 230,-180, nullptr, &m_color);
}

void ClickStart::Init()
{
	m_pTex = AssetManager::Instance().GetTex("ClickStart");

	m_alpha = 1.0f;
	m_addAlpha = -0.008f;

	m_color = { 1,1,1,m_alpha };
}
