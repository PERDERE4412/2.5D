#include "GetPotion.h"

void GetPotion::Update()
{
	if (m_bMove)
	{
		m_pos.x -= 5.0f;
		if (m_pos.x < 490.0f)
		{
			m_pos.x = 490.0f;
			m_bMove = false;
		}
	}
	else
	{
		m_alpha += m_addAlpha;
		if (m_alpha <= 0.0f)
		{
			m_isExpired = true;
		}

		m_color.w = m_alpha;
	}
}

void GetPotion::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, m_pos.x,m_pos.y,nullptr,&m_color);
}

void GetPotion::Init()
{
	m_pTex = AssetManager::Instance().GetTex("GetPotion");

	m_pos = { 790.0f,0.0f };

	m_color = { 1,1,1,1 };

	m_alpha = 1.0f;
	m_addAlpha = -0.008f;

	m_bMove = true;
}
