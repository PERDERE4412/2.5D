#include "Slot.h"

void Slot::Update()
{
}

void Slot::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_world);
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, m_tex.GetWidth(), m_tex.GetHeight(), &m_rect);
}

void Slot::Init()
{
	m_objType = ObjType::none;

	m_tex.Load("Asset/Textures/slot.png");
	m_pos = { -250.0f,-300.0f,0.0f };
	m_world = Math::Matrix::CreateTranslation(m_pos);
	m_rect = { 0,0,(int)m_tex.GetWidth(),(int)m_tex.GetHeight() };
}
