#include "BaseItem.h"

#include "../Chara/Player/Player.h"

void BaseItem::Update()
{
	m_numRect.x= 8 * m_data.num;
}

void BaseItem::DrawSprite()
{
	if (m_data.num <= 0)return;

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pItemTex, -250.0f, -300.0f);

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pNumTex, -220.0f, -320.0f,m_numRect.width*2,m_numRect.height*2, &m_numRect);
}

void BaseItem::Init()
{
	m_pNumTex = AssetManager::Instance().GetTex("number");
	m_numRect = { 0,0,8,8 };
}
