#include "Gold.h"

#include "../../../Lib/AssetManager/AssetManager.h"
#include "../../../Data/Item/Item.h"

void Gold::Update()
{
	// 数字(仮 後に変更)
	int digit[NUM] = { 0,0,0 };
	if (m_currentGold >= 100)
	{
		digit[0] = m_currentGold / 100;
		digit[1] = (m_currentGold / 10) % 10;
		digit[2] = m_currentGold % 10;
	}
	else if (m_currentGold >= 10)
	{
		digit[1] = m_currentGold / 10;
		digit[2] = m_currentGold % 10;
	}
	else
	{
		digit[2] = m_currentGold;
	}
	for (int i = 0; i < NUM; i++)m_number[i].rect.x = 8 * digit[i];

	// 数字の増減アニメーション
	if (m_currentGold > Item::Instance().GetGold())m_currentGold--;
	else if (m_currentGold < Item::Instance().GetGold())m_currentGold++;
}

void Gold::DrawSprite()
{
	// ゴールド
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_gold.pTex, m_gold.pos.x, m_gold.pos.y, m_gold.pTex->GetWidth(), m_gold.pTex->GetHeight(), &m_gold.rect);

	// 数字
	for (int i = 0; i < NUM; i++)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_number[i].pTex, m_number[i].pos.x, m_number[i].pos.y, m_number[i].pTex->GetWidth() / 10, m_number[i].pTex->GetHeight(), &m_number[i].rect);
	}
}

void Gold::Init()
{
	// ゴールド
	m_gold.pTex = AssetManager::Instance().GetTex("gold");
	m_gold.pos = { -550.0f,-250.0f };
	m_gold.rect = { 0,0,(int)m_gold.pTex->GetWidth(),(int)m_gold.pTex->GetHeight() };

	// 数字
	for (int i = 0; i < NUM; i++)
	{
		m_number[i].pTex = AssetManager::Instance().GetTex("number");
		m_number[i].pos = { -530.0f + 10.0f * i,-250.0f,0.0f };
		m_number[i].rect = { 0,0,(int)m_number[i].pTex->GetWidth() / 10,(int)m_number[i].pTex->GetHeight() };
	}

	m_currentGold = 0;
}
