#include "Slot.h"

#include "../../../Lib/AssetManager/AssetManager.h"

void Slot::Update()
{
}

void Slot::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, m_pos.x, m_pos.y, m_pTex->GetWidth(), m_pTex->GetHeight(), &m_rect);
}

void Slot::Init()
{
	m_pTex = AssetManager::Instance().GetTex("slot");
	m_pos = { -250.0f,-300.0f };
	m_rect = { 0,0,(int)m_pTex->GetWidth(),(int)m_pTex->GetHeight() };
}
