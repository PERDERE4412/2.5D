#include "Slot.h"

void Slot::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, (int)m_pos.x, (int)m_pos.y, m_pTex->GetWidth(), m_pTex->GetHeight(), &m_rect);
}

void Slot::Init()
{
	m_pTex = AssetManager::Instance().GetTex("slot");
	m_pos = { -250.0f,-300.0f };
	m_rect = { 0,0,(int)m_pTex->GetWidth(),(int)m_pTex->GetHeight() };
}
