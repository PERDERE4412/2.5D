#include "Gold.h"

#include "../../Lib/AssetManager/AssetManager.h"

void Gold::Update()
{
}

void Gold::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_world);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, 0, 0, m_pTex->GetWidth(), m_pTex->GetHeight(), &m_rect);
}

void Gold::Init()
{
	m_objType = ObjType::none;

	m_pTex = AssetManager::Instance().GetTex("gold");
	m_pos = { 0.0f,0.0f,0.0f };
	m_world = Math::Matrix::CreateTranslation(m_pos);
	m_rect = { 0,0,(int)m_pTex->GetWidth(),(int)m_pTex->GetHeight() };
}
